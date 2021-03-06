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
#include "core/semaphore_file.h"

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
#include "core/wwivassert.h"

using std::string;
using std::chrono::milliseconds;
using namespace wwiv::os;

namespace wwiv {
namespace core {

#ifndef _WIN32
#ifndef O_TEMPORARY
#define O_TEMPORARY 0
#endif  // O_TEMPORARY
#endif  // _WIN32

// static 
SemaphoreFile SemaphoreFile::try_acquire(const std::string& filepath, std::chrono::duration<double> timeout) {
  int mode = O_CREAT | O_EXCL | O_TEMPORARY | O_RDWR;
  int pmode = S_IREAD | S_IWRITE;
  auto step = timeout / 10;
  if (step > std::chrono::seconds(1)) {
    step = std::chrono::seconds(1);
  }
  auto start = std::chrono::steady_clock::now();
  auto end = start + timeout;
  while (true) {
    int fd = open(filepath.c_str(), mode, pmode);
    if (fd >= 0) { 
      return { filepath, fd };
    }
    if (std::chrono::steady_clock::now() > end) {
      throw semaphore_not_acquired(filepath);
    }
    sleep_for(step);
  }
}

// static 
SemaphoreFile SemaphoreFile::acquire(const std::string& filepath) {
  return try_acquire(filepath, std::chrono::duration<double>::max());
}

SemaphoreFile::SemaphoreFile(const std::string& filepath, int fd) 
  : filename_(filepath), fd_(fd) {}

SemaphoreFile::~SemaphoreFile() {
  LOG(ERROR) << "~SemaphoreFile(): " << filename_ << "; fd: " << fd_;
  if (fd_ >= 0) {
    if (close(fd_) == -1) {
      LOG(ERROR) << "Failed to close file: " << filename_ << "; error: " << errno;
    }
#ifndef _WIN32
    // Since we don't have O_TEMPORARY on POSIX, we unlink the file
    // which will delete it once the last file handle is closed.
    ::unlink(filename_.c_str());
#endif  // _WIN32

  } else {
    LOG(ERROR) << "Skipping closing since file already closed: " << filename_;
  }
  fd_ = -1;
}


}  // namespace core
}  // namespace wwiv
