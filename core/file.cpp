/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2017, WWIV Software Services            */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/*                                                                        */
/**************************************************************************/
#include "core/file.h"
#ifdef _WIN32
// Always declare wwiv_windows.h first to avoid collisions on defines.
#include "core/wwiv_windows.h"

#include "Shlwapi.h"
#endif  // _WIN32

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <share.h>
#include "sys/utime.h"
#endif  // _WIN32
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include "core/log.h"

#ifndef _WIN32
#include <sys/file.h>
#include <unistd.h>
#include <utime.h>
#endif  // _WIN32

#include "core/os.h"
#include "core/wfndfile.h"
#include "core/wwivassert.h"

#if !defined( O_BINARY )
#define O_BINARY 0
#endif
#if !defined( O_TEXT )
#define O_TEXT 0
#endif

#ifdef _WIN32

// Needed for PathIsRelative
#pragma comment(lib, "Shlwapi.lib")

#if !defined(ftruncate)
#define ftruncate chsize
#endif  // ftruncate
#define flock(h, m) { (h), (m); }
static constexpr int LOCK_SH = 1;
static constexpr int LOCK_EX = 2;
static constexpr int LOCK_NB = 4;
static constexpr int LOCK_UN = 8;
static constexpr int F_OK = 0;

#else 
#define _sopen(n, f, s, p) open(n, f, 0644)
#endif  // _WIN32


using std::string;
using std::chrono::milliseconds;
using namespace wwiv::os;

/////////////////////////////////////////////////////////////////////////////
// Constants

const int File::modeDefault = (O_RDWR | O_BINARY);
const int File::modeAppend         = O_APPEND;
const int File::modeBinary         = O_BINARY;
const int File::modeCreateFile     = O_CREAT;
const int File::modeReadOnly       = O_RDONLY;
const int File::modeReadWrite      = O_RDWR;
const int File::modeText           = O_TEXT;
const int File::modeWriteOnly      = O_WRONLY;
const int File::modeTruncate       = O_TRUNC;
const int File::modeExclusive      = O_EXCL;

const int File::modeUnknown        = -1;
const int File::shareUnknown       = -1;

const int File::invalid_handle     = -1;

static constexpr int WAIT_TIME_MILLIS = 10;
static constexpr int TRIES = 100;

namespace wwiv {
namespace core {

string FilePath(const string& dirname, const string& filename) {

  if (dirname.empty()) {
    return filename;
  }

  string result = dirname;
  File::EnsureTrailingSlash(&result);
  result.append(filename);
  return result;
}

}  // namespace core
}  // namespace wwiv

/////////////////////////////////////////////////////////////////////////////
// Constructors/Destructors

File::File() : handle_(File::invalid_handle) {}

File::File(const string& full_file_name) : File() {
  this->set_name(full_file_name);
}

File::File(const string& dir, const string& filename) : File() {
  this->set_name(dir, filename);
}

File::~File() {
  if (this->IsOpen()) {
    this->Close();
  }
}

bool File::Open(int file_mode, int share_mode) {
  DCHECK_EQ(this->IsOpen(), false) << "File " << full_path_name_ << " is already open.";

  // Set default share mode
  if (share_mode == File::shareUnknown) {
    share_mode = shareDenyWrite;
    if ((file_mode & File::modeReadWrite) ||
        (file_mode & File::modeWriteOnly)) {
      share_mode = File::shareDenyReadWrite;
    }
  }

  CHECK_NE(share_mode, File::shareUnknown);
  CHECK_NE(file_mode, File::modeUnknown);

  VLOG(3) << "SH_OPEN " << full_path_name_ << ", access=" << file_mode;

  handle_ = _sopen(full_path_name_.c_str(), file_mode, share_mode, _S_IREAD | _S_IWRITE);
  if (handle_ < 0) {
    VLOG(3) << "1st _sopen: handle: " << handle_ << "; error: " << strerror(errno);
    int count = 1;
    if (access(full_path_name_.c_str(), 0) != -1) {
      sleep_for(milliseconds(WAIT_TIME_MILLIS));
      handle_ = _sopen(full_path_name_.c_str(), file_mode, share_mode, _S_IREAD | _S_IWRITE);
      while ((handle_ < 0 && errno == EACCES) && count < TRIES) {
        sleep_for(milliseconds((count % 2) ? WAIT_TIME_MILLIS : 0));
        VLOG(3) << "Waiting to access " << full_path_name_ << "  " << TRIES - count;
        count++;
        handle_ = _sopen(full_path_name_.c_str(), file_mode, share_mode, _S_IREAD | _S_IWRITE);
      }

      if (handle_ < 0) {
        VLOG(3) << "The file " << full_path_name_ << " is busy.  Try again later.";
      }
    }
  }

  VLOG(3) << "SH_OPEN " << full_path_name_ << ", access=" << file_mode << ", handle=" << handle_;

  if (File::IsFileHandleValid(handle_)) {
    flock(handle_, (share_mode == shareDenyReadWrite || share_mode == shareDenyWrite) ? LOCK_EX : LOCK_SH);
  }

  if (handle_ == File::invalid_handle) {
    this->error_text_ = strerror(errno);
  }

  return File::IsFileHandleValid(handle_);
}

void File::Close() {
  VLOG(3) << "CLOSE " << full_path_name_ << ", handle=" << handle_;
  if (File::IsFileHandleValid(handle_)) {
    flock(handle_, LOCK_UN);
    close(handle_);
    handle_ = File::invalid_handle;
  }
}

/////////////////////////////////////////////////////////////////////////////
// Member functions

bool File::set_name(const string& filename) {
  full_path_name_ = filename;
  return true;
}

bool File::set_name(const string& dirname, const string& filename) {
  std::stringstream full_path_name;
  full_path_name << dirname;
  if (!dirname.empty() && dirname[dirname.length() - 1] == pathSeparatorChar) {
    full_path_name << filename;
  } else {
    full_path_name << pathSeparatorChar << filename;
  }
  return set_name(full_path_name.str());
}

ssize_t File::Read(void* buffer, size_t size) {
  ssize_t ret = read(handle_, buffer, size);
  if (ret == -1) {
    LOG(ERROR) << "[DEBUG: Read errno: " << errno
      << " filename: " << full_path_name_ << " size: " << size;
    LOG(ERROR) << " -- Please screen capture this and attach to a bug here: " << std::endl;
    LOG(ERROR) << "https://github.com/wwivbbs/wwiv/issues" << std::endl;
  }
  return ret;
}

ssize_t File::Write(const void* buffer, size_t size) {
  ssize_t nRet = write(handle_, buffer, size);
  if (nRet == -1) {
    LOG(ERROR) << "[DEBUG: Write errno: " << errno
      << " filename: " << full_path_name_ << " size: " << size;
    LOG(ERROR) << " -- Please screen capture this and attach to a bug here: " << std::endl;
    LOG(ERROR) << "https://github.com/wwivbbs/wwiv/issues" << std::endl;
  }
  return nRet;
}

off_t File::Seek(off_t offset, Whence whence) {
  CHECK(whence == File::Whence::begin || whence == File::Whence::current || whence == File::Whence::end);
  CHECK(File::IsFileHandleValid(handle_));

  return lseek(handle_, offset, static_cast<int>(whence));
}

off_t File::current_position() const {
  return lseek(handle_, 0, SEEK_CUR);
}

bool File::Exists() const {
  return File::Exists(full_path_name_);
}

bool File::Delete() {
  if (this->IsOpen()) {
    this->Close();
  }
  return unlink(full_path_name_.c_str()) == 0;
}

void File::set_length(off_t lNewLength) {
  WWIV_ASSERT(File::IsFileHandleValid(handle_));
  ftruncate(handle_, lNewLength);
}

bool File::IsFile() const {
  return !this->IsDirectory();
}

bool File::SetFilePermissions(int perm) {
  return chmod(full_path_name_.c_str(), perm) == 0;
}

/////////////////////////////////////////////////////////////////////////////
// Static functions

bool File::Rename(const string& orig_fn, const string& new_fn) {
  return rename(orig_fn.c_str(), new_fn.c_str()) == 0;
}

bool File::Remove(const string& filename) {
  return (unlink(filename.c_str()) ? false : true);
}

bool File::Remove(const string& dir, const string& file) {
  return File::Remove(wwiv::core::FilePath(dir, file));
}

bool File::Exists(const string& original_pathname) {
  if (original_pathname.empty()) {
    // An empty filename can not exist.
    // The question is should we assert here?
    return false;
  }

  string fn(original_pathname);
  if (fn.back() == pathSeparatorChar) {
    // If the pathname ends in / or \, then remove the last character.
    fn.pop_back();
  }
  auto ret = access(fn.c_str(), F_OK);
  return ret == 0;
}

bool File::Exists(const string& dir, const string& file) {
  return Exists(wwiv::core::FilePath(dir, file));
}

bool File::ExistsWildcard(const string& wildcard) {
  WFindFile fnd;
  return fnd.open(wildcard.c_str(), WFindFileTypeMask::WFINDFILE_ANY);
}

bool File::SetFilePermissions(const string& filename, int perm) {
  CHECK(!filename.empty());
  return chmod(filename.c_str(), perm) == 0;
}

bool File::IsFileHandleValid(int handle) {
  return handle != File::invalid_handle;
}

// static
void File::EnsureTrailingSlash(string* path) {
  if (path->empty()) {
    return;
  }
  auto last_char = path->back();
  if (last_char != File::pathSeparatorChar) {
    path->push_back(File::pathSeparatorChar);
  }
}

// static 
string File::current_directory() {
  char s[MAX_PATH];
  getcwd(s, MAX_PATH);
  return string(s);
}

// static
bool File::set_current_directory(const string& dir) {
  return chdir(dir.c_str()) == 0;
}

// static 
void File::FixPathSeparators(std::string* name) {
#ifdef _WIN32
  std::replace(std::begin(*name), std::end(*name), '/', File::pathSeparatorChar);
#else
  std::replace(std::begin(*name), std::end(*name), '\\', File::pathSeparatorChar);
#endif  // _WIN32
}

// static 
std::string File::FixPathSeparators(const std::string& path) {
  auto s = path;
  FixPathSeparators(&s);
  return s;
}

// static
void File::absolute(const string& base, string* relative) {
  if (!File::is_absolute(*relative)) {
    File dir(base, *relative);
    relative->assign(dir.full_pathname());
  }
}

// static 
string File::absolute(const std::string& base, const std::string& relative) {
  if (File::is_absolute(relative)) {
    return relative;
  }
  File dir(base, relative);
  return dir.full_pathname();
}

// static
bool File::is_absolute(const string& path) {
  if (path.empty()) {
    return false;
  }
#ifdef _WIN32
  return ::PathIsRelative(path.c_str()) ? false : true;
#else
  return path.front() == File::pathSeparatorChar;
#endif  // _WIN32
}

#ifdef _WIN32
#define MKDIR(x) ::mkdir(x)
#else
#define MKDIR(x) ::mkdir(x, S_IRWXU | S_IRWXG)
#endif

// static
bool File::mkdir(const string& path) {
  auto result = MKDIR(path.c_str());
  if (result != -1) {
    return true;
  }
  if (errno == EEXIST) {
    // still return true if the directory already existed.
    return true;
  }
  return false;
}

// static
// based loosely on http://stackoverflow.com/questions/675039/how-can-i-create-directory-tree-in-c-linux
bool File::mkdirs(const string& path) {
  auto result = MKDIR(path.c_str());
  if (result != -1) {
    return true;
  }
  if (errno == ENOENT) {
	  string::size_type pos = path.find_last_of(File::pathSeparatorChar);
	  if (pos == string::npos) {
		  return false;
	  }
	  string s = path.substr(0, pos);
    if (!mkdirs(s)) {
      return false;  // failed to create the parent, stop here.
    }
    return File::mkdir(path.c_str());
  } else if (errno == EEXIST) {
    return true;  // the path already existed.
  }
  return false;  // unknown error.
}

std::ostream& operator<<(std::ostream& os, const File& file) {
  os << file.full_pathname();
  return os;
}

bool File::set_last_write_time(time_t last_write_time) {
  struct utimbuf ut;
  ut.actime = ut.modtime = last_write_time;
  return utime(full_path_name_.c_str(), &ut) != -1;
}

std::unique_ptr<wwiv::core::FileLock> File::lock(wwiv::core::FileLockType lock_type) {
#ifdef _WIN32
  HANDLE h = reinterpret_cast<HANDLE>(_get_osfhandle(handle_));
  OVERLAPPED overlapped = { 0 };
  DWORD dwLockType = 0;
  if (lock_type == wwiv::core::FileLockType::write_lock) {
    dwLockType = LOCKFILE_EXCLUSIVE_LOCK;
  }
  if (!::LockFileEx(h, dwLockType, 0, MAXDWORD, MAXDWORD, &overlapped)) {
    LOG(ERROR) << "Error Locking file: " << full_path_name_;
  }
#else

  // TODO: unlock here

#endif  // _WIN32
  return std::make_unique<wwiv::core::FileLock>(handle_, full_path_name_, lock_type);
}
