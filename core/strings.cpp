/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2017, WWIV Software Services             */
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
#include "core/strings.h"

#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "core/log.h"
#include "core/wwivassert.h"
#include "core/wwivport.h"

#ifdef _WIN32
#define NOMINMAX
#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")
#undef StrCat
#endif  // _WIN32


using std::numeric_limits;
using std::stoi;
using std::string;
using std::out_of_range;

unsigned char *translate_letters[] = {
  (unsigned char *)"abcdefghijklmnopqrstuvwxyz�������",
  (unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ�������",
  nullptr,
};
const char *DELIMS_WHITE = " \t\r\n";
const char *DELIMS_CRLF = "\r\n";

using std::ostringstream;
using std::string;
using std::stringstream;
using std::vector;

namespace wwiv {
namespace strings {

/**
 * sprintf type function for STL string classes.
 * @param formatted_text The format specifier
 * @param ... Variable arguments
 */
string StringPrintf(const char *formatted_text, ...) {
  char buffer[1024];

  va_list ap;
  va_start(ap, formatted_text);
  vsnprintf(buffer, sizeof(buffer), formatted_text, ap);
  va_end(ap);
  return string(buffer);
}

/**
 * Gets the length of the C style string.  This function returns an int
 * instead of a size_t, so using this function can avoid warnings of
 * signed vs. unsigned comparasons.
 *
 * @param str the C style string
 * @return The length as an integer
 */
int GetStringLength(const char* str) {
  CHECK(str != nullptr) << "called GetStringLength on a nullptr";
  return static_cast<int>(strlen(str));
}

/**
 * Compares the strings
 * @param str1 string to compare
 * @param str1 other string to compare
 * @return true of the strings contain the same contents
 */
bool IsEquals(const char* str1, const char* str2) {
  CHECK(str1 != nullptr);
  CHECK(str2 != nullptr);

  return (strcmp(str1, str2) == 0) ? true : false;
}

/**
 * Compares the strings, ignoring case
 * @param str1 string to compare
 * @param str1 other string to compare
 * @return true of the strings contain the same contents ignoring case
 */
bool IsEqualsIgnoreCase(const char *str1, const char *str2) {
  return iequals(str1, str2);
}

bool iequals(const char *str1, const char *str2) {
  CHECK(str1 != nullptr);
  CHECK(str2 != nullptr);

  return (StringCompareIgnoreCase(str1, str2) == 0) ? true : false;
}

bool iequals(const std::string& s1, const std::string& s2) {
  return s1.size() == s2.size() &&
    std::equal(s1.begin(), s1.end(), s2.begin(),
    [](const char& c1, const char& c2) {
    return (std::tolower(c1) == std::tolower(c2));
  });
}

int StringCompareIgnoreCase(const char *str1, const char *str2) {
  CHECK(str1 != nullptr);
  CHECK(str2 != nullptr);

  return strcasecmp(str1, str2);
}

int StringCompare(const char *str1, const char *str2) {
  CHECK(str1 != nullptr);
  CHECK(str2 != nullptr);

  return strcmp(str1, str2);
}

template <typename T, typename R>
static T StringToT(std::function<R(const string&)> f, const string& s) {
  try {
    R ret = f(s);
    if (ret > numeric_limits<T>::max()) {
      return numeric_limits<T>::max();
    }
    if (ret < numeric_limits<T>::min()) {
      return numeric_limits<T>::min();
    }
    return static_cast<T>(ret);
  }
  catch (const std::logic_error&) {
    // Handle invalid_argument and out_of_range.
    return 0;
  }
}

int16_t StringToShort(const string& s) {
  return StringToT<int16_t, int>(
      [](const string& s) { return std::stoi(s); }, s);
}

uint16_t StringToUnsignedShort(const string& s) {
  return StringToT<uint16_t, unsigned long>(
      [](const string& s) { return std::stoul(s); }, s);
}

int8_t StringToChar(const string& s) {
  return StringToT<int8_t, int>(
      [](const string& s) { return std::stoi(s); }, s);
}

uint8_t StringToUnsignedChar(const string& s) {
  return StringToT<uint8_t, unsigned long>(
      [](const string& s) { return std::stoul(s); }, s);
}

unsigned int StringToUnsignedInt(const string& s) {
  return StringToT<unsigned, unsigned long>(
    [](const string& s) { return std::stoul(s); }, s);
}

int StringToInt(const string& s) {
  return StringToT<int, int>(
    [](const string& s) { return std::stoi(s); }, s);
}

float StringToFloat(const string& s) {
  return StringToT<float, float>(
    [](const string& s) { return std::stof(s); }, s);
}

const string& StringReplace(string* orig, const string& old_string, const string& new_string) {
  string::size_type pos = orig->find(old_string, 0);
  while (pos != string::npos) {
    orig->replace(pos, old_string.length(), new_string);
    pos = orig->find(old_string, pos + new_string.length());
  }
  return *orig;
}

vector<string> SplitString(const string& original_string, const string& delims) {
  return SplitString(original_string, delims, true);
}

vector<string> SplitString(const string& original_string, const string& delims, bool skip_empty) {
  vector<string> v;
  SplitString(original_string, delims, skip_empty, &v);
  return v;
}

void SplitString(const string& original_string, const string& delims, vector<string>* out) {
  SplitString(original_string, delims, true, out);
}

void SplitString(const string& original_string, const string& delims, bool skip_empty, vector<string>* out) {
  string s(original_string);
  for (string::size_type found = s.find_first_of(delims); found != string::npos; s = s.substr(found + 1), found = s.find_first_of(delims)) {
    if (found != std::string::npos && found > 0) {
      out->push_back(s.substr(0, found));
    }
    else if (!skip_empty && found == 0) {
      // Add empty lines.
      out->push_back({});
    }
  }
  if (!s.empty()) {
    out->push_back(s);
  }
}

bool starts_with(const std::string& input, const std::string& match) {
  return input.size() >= match.size()
      && std::equal(std::begin(match), std::end(match), std::begin(input));
}

bool ends_with(const std::string& input, const std::string& match) {
  return input.size() >= match.size()
    && std::equal(match.rbegin(), match.rend(), input.rbegin());
}

/**
 * Returns a string justified and padded with "bg".
 * @param str The text to justify
 * @param nLength the length of the text
 * @param bg the character to use as the background
 * @param nJustificationType one of the following:
 *      LEFT
 *      RIGHT
 * @return the justified text.
 */
void StringJustify(string* s, string::size_type length, char bg, JustificationType just_type) {
  if (s->size() > length) {
    *s = s->substr(0, length);
    return;
  } else if (s->size() == length) {
    return;
  }

  string::size_type delta = length - s->size();
  switch (just_type) {
  case JustificationType::LEFT: {
    s->resize(length, bg);
  } break;
  case JustificationType::RIGHT: {
    string tmp(*s);
    *s = StrCat(string(delta, bg), tmp);
  } break;
  }
}


/**
 * Removes spaces from the beginning and the end of the string s.
 * @param s the string from which to remove spaces
 * @return s with spaces removed.
 */
void StringTrim(char *str) {
  string s(str);
  StringTrim(&s);
  strcpy(str, s.c_str());
}

/**
* Removes spaces from the beginning and the end of the string s.
* @param s the string from which to remove spaces
* @return s with spaces removed.
*/
void StringTrim(string* s) {
  string::size_type pos = s->find_first_not_of(DELIMS_WHITE);
  s->erase(0, pos);

  pos = s->find_last_not_of(DELIMS_WHITE);
  s->erase(pos + 1);
}

/**
* Removes spaces from the beginning and the end of the string s.
* @param s the string from which to remove spaces
* @return s with spaces removed.
*/
void StringTrimCRLF(string* s) {
  string::size_type pos = s->find_first_not_of(DELIMS_CRLF);
  s->erase(0, pos);

  pos = s->find_last_not_of(DELIMS_CRLF);
  s->erase(pos + 1);
}

/**
* Removes spaces from the beginning and the end of the string s and
* returns it as a new stringl
* @param s the string from which to remove spaces
* @return s with spaces removed.
*/
string StringTrim(const string& orig) {
  string s(orig);
  string::size_type pos = s.find_first_not_of(DELIMS_WHITE);
  s.erase(0, pos);

  pos = s.find_last_not_of(DELIMS_WHITE);
  s.erase(pos + 1);
  return s;
}

void StringTrimBegin(string* s) {
  string::size_type pos = s->find_first_not_of(DELIMS_WHITE);
  s->erase(0, pos);
}

void StringTrimEnd(string* s) {
  string::size_type pos = s->find_last_not_of(DELIMS_WHITE);
  s->erase(pos + 1);
}

/**
 * Removes the whitespace from the end of the string
 * @param str The string from which to remove the trailing whitespace
 */
void StringTrimEnd(char *str) {
  string s(str);
  StringTrimEnd(&s);
  strcpy(str, s.c_str());
}

static char toupper_char(int c) {
  return static_cast<char>(::toupper(c));
}

void StringUpperCase(string* s) {
  std::transform(std::begin(*s), std::end(*s), std::begin(*s), toupper_char);
}

string ToStringUpperCase(const string& orig) {
  string s(orig);
  StringUpperCase(&s);
  return s;
}

static char tolower_char(int c) {
  return static_cast<char>(::tolower(c));
}

void StringLowerCase(string* s) {
  std::transform(std::begin(*s), std::end(*s), std::begin(*s), tolower_char);
}

string ToStringLowerCase(const string& orig) {
  string s(orig);
  StringLowerCase(&s);
  return s;
}

/**
 * Returns string comprised of char chRepeatChar, nStringLength characters in length
 * @param nStringLength The number of characters to create the string
 * @param fill The character to repeat.
 * @return The string containing rc repeated len times.
 */
const char *charstr(string::size_type length, char fill) {
  static string result;
  result = string(std::min<int>(length, 160), fill);
  return result.c_str();
}

void StringRemoveWhitespace(string* str) {
  str->erase(std::remove_if(str->begin(), str->end(), isspace), str->end());
}

char *StringRemoveWhitespace(char *str) {
  CHECK(str != nullptr);

  if (str) {
    char *obuf, *nbuf;
    for (obuf = str, nbuf = str; *obuf; ++obuf) {
      if (!isspace(*obuf)) {
        *nbuf++ = *obuf;
      }
    }
    *nbuf = '\0';
  }
  return str;
}

char *StringRemoveChar(const char *str, char ch) {
  static char s_strip_string[255];

  CHECK(str != nullptr);
  strcpy(s_strip_string, "");

  int i1 = 0;
  for (int i = 0; i < wwiv::strings::GetStringLength(str); i++) {
    if (str[i] != ch) {
      s_strip_string[i1] = str[i];
      i1++;
    } else {
      s_strip_string[i1] = '\0';
      break;
    }
  }

  //if last char is a space, remove it too.
  if (s_strip_string[i1 - 1] == ' ') {
    i1--;
  }
  s_strip_string[i1] = '\0';
  return s_strip_string;
}

std::string JoinStrings(const std::vector<std::string>& lines, const std::string& end_of_line) {
  string out;
  for (const auto& line : lines) {
    out += line;
    out += end_of_line;
  }
  return out;
}

std::string put_time(const struct tm *tm_info, const std::string& fmt_arg) {
  char buffer[1024];

  size_t num = strftime(buffer, sizeof(buffer), fmt_arg.c_str(), tm_info);
  if (num == 0) {
    return "";
  }
  return string(buffer);
}

std::string::size_type size_without_colors(const std::string& s) {
  const string stripped = stripcolors(s);
  return stripped.size();
}

std::string trim_to_size_ignore_colors(const std::string& orig, std::string::size_type size) {
  string s(orig);
  while (size_without_colors(s) > size) {
    s.pop_back();
  }
  return s;
}

std::string pad_to_ignore_colors(const std::string& orig, std::string::size_type size) {
  auto len = size_without_colors(orig);
  if (size <= len) {
    return orig;
  }
  return orig + std::string(size - len, ' ');
}


}  // namespace strings
}  // namespace wwiv

/**
 * Is the character c a possible color code. (is it #, B, or a digit)
 * @param c The Character to test.
 */
static bool IsColorCode(char c) {
  if (!c) {
    return false;
  }
  return (c == '#' || isdigit(c));
}

char *stripcolors(const char *str) {
  CHECK(str != nullptr);
  static char s[255];
  const string result = stripcolors(string(str));
  strcpy(s, result.c_str());
  return s;
}

template<typename I>
static bool is_ansi_seq_start(I& i, const std::string& orig) {
  auto left = string(i, end(orig));
  if (left.size() < 3) {
    return false;
  }
  if (left.at(1) != '[') {
    return false;
  }
  if (left.find('m') == std::string::npos) {
    return false;
  }
  return true;
}

/**
 * Removes the WWIV color codes and pipe codes from the string
 *
 * @param pszOrig The text from which to remove the color codes.
 * @return A new string without the color codes
 */
string stripcolors(const string& orig) {
  string out;
  for (auto i = begin(orig); i != end(orig); i++) {
    if (*i == 27 && (i + 1) != end(orig)) {
      auto left = string(i, end(orig));
      if (!is_ansi_seq_start(i, orig)) {
        out.push_back(*i);
        continue;
      }
      // skip everything until we have the end of the ansi sequence.
      while (i != end(orig) && *i != 'm') {
        i++;
      }
      if (i != end(orig)) {
        i++;
      }
    }
    if (i == end(orig)) {
      break;
    } else if ((i + 1) != end(orig) 
                && (i + 2) != end(orig) 
                && *i == '|'
                && IsColorCode(*(i + 1)) 
                && IsColorCode(*(i + 2))) {
      ++i;
      ++i;
    } else if ((i + 1 ) != end(orig) 
               && *i == 3 
               && isdigit(*(i + 1))) {
      ++i;
    } else {
      out.push_back(*i);
    }
  }
  return out;
}

/**
 * Translates the character ch into uppercase using WWIV's translation tables
 * @param ch The character to translate
 * @return The uppercase version of the character
 */
unsigned char upcase(unsigned char ch) {
  unsigned char *ss = (unsigned char*) strchr((const char*) translate_letters[0], ch);
  if (ss) {
    ch = translate_letters[1][ss - translate_letters[0]];
  }
  return ch;
}

/**
 * Translates the character ch into lower using WWIV's translation tables
 * @param ch The character to translate
 * @return The lowercase version of the character
 */
unsigned char locase(unsigned char ch) {
  unsigned char *ss = (unsigned char*)  strchr((const char*) translate_letters[1], ch);
  if (ss) {
    ch = translate_letters[0][ss - translate_letters[1]];
  }
  return ch;
}

void properize(char *text) {
  if (text == nullptr) {
    return;
  }

  for (int i = 0; i < wwiv::strings::GetStringLength(text); i++) {
    if ((i == 0) || ((i > 0) && ((text[i - 1] == ' ') || (text[i - 1] == '-') ||
                                 (text[i - 1] == '.')))) {
      text[i] = wwiv::strings::to_upper_case<char>(text[i]);
    } else {
      text[i] = wwiv::strings::to_lower_case(text[i]);
    }
  }
}

string properize(const string& text) {
  if (text.empty()) {
    return string("");
  }

  char last = ' ';
  ostringstream os;
  for (auto ch : text) {
    if (last == ' ' || last == '-' || last == '.') {
      os << wwiv::strings::to_upper_case<char>(ch);
    } else {
      os << wwiv::strings::to_lower_case<char>(ch);
    }
    last = ch;
  }
  return os.str();
}

#ifdef _WIN32
char *strcasestr(const char *haystack, const char *needle) {
  if (strlen(needle) == 0) {
    // unlike strstr() and wcsstr() passing an emtpy string results in NULL being returned.
    // See http://msdn.microsoft.com/en-us/library/windows/desktop/bb773439%28v=vs.85%29.aspx
    return const_cast<char*>(haystack);
  }
  return StrStrI(haystack, needle);
}
#else

/** Converts string to uppercase */
char *strupr(char *s) {
  for (int i = 0; s[i] != 0; i++) {
    s[i] = wwiv::strings::to_upper_case<char>(s[i]);
  }

  return s;
}

/** Converts string to lowercase */
char *strlwr(char *s) {
  for (int i = 0; s[i] != 0; i++) {
    s[i] = wwiv::strings::to_lower_case(s[i]);
  }

  return s;
}

// Reverses a string
char *strrev(char *s) {
  CHECK(s != nullptr);
  char szTempBuffer[255];
  int str = strlen(s);
  CHECK_LE(str, 255);

  for (int i = str; i > - 1; i--) {
    s[i] = szTempBuffer[str - i];
  }
  strcpy(s, szTempBuffer);
  return s;
}

#endif  // _WIN32
