//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "util/system.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string.h>

#ifndef WIN32
#  include <dirent.h>
#  include <fcntl.h>
#  include <fnmatch.h>
#  include <sys/stat.h>
#  include <sys/types.h>
#  include <unistd.h>
#  include <errno.h>
#else /* WIN32 */
#  include <windows.h>
#  include <direct.h>
#  include <fstream>
#  include <sys/stat.h>
#  include <sys/types.h>
#  include <io.h>
#define chdir  _chdir
#define access _access
#define F_OK   0
#endif

#include "pingus/globals.hpp"
#include "util/pathname.hpp"

std::string System::userdir;
std::string System::default_email;
std::string System::default_username;

System::DirectoryEntry::DirectoryEntry(const std::string& n, FileType t)
  : type (t), name (n)
{
}

System::Directory
System::opendir(const std::string& pathname, const std::string& pattern)
{
  Directory dir_list;

#ifndef WIN32
  DIR* dp;
  dirent* de;

  dp = ::opendir(pathname.c_str());

  if (dp == 0)
  {
    std::cout << "System: Couldn't open: " << pathname << std::endl;
  }
  else
  {
    while ((de = ::readdir(dp)) != 0)
    {
      if (fnmatch(pattern.c_str(), de->d_name, FNM_PATHNAME) == 0)
      {
        struct stat buf;
        stat ((pathname + "/" + de->d_name).c_str (), &buf);

        if (S_ISDIR(buf.st_mode))
        {
          dir_list.push_back(DirectoryEntry(de->d_name, DE_DIRECTORY));
        }
        else
        {
          dir_list.push_back(DirectoryEntry(de->d_name, DE_FILE));
        }
      }
    }

    closedir(dp);
  }
#else /* WIN32 */
  WIN32_FIND_DATA coFindData;
  std::string FindFileDir = pathname + "/" + pattern;
  HANDLE hFind = FindFirstFile(TEXT(FindFileDir.c_str()),&coFindData);

  if (hFind == INVALID_HANDLE_VALUE)
  {
    if (GetLastError() != ERROR_FILE_NOT_FOUND)
      std::cout << "System: Couldn't open: " << pathname << std::endl;
  }
  else
  {
    do
    {
      if (coFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
        dir_list.push_back(DirectoryEntry(coFindData.cFileName, System::DE_DIRECTORY));
      }
      else
      {
        dir_list.push_back(DirectoryEntry(coFindData.cFileName, System::DE_FILE));
      }
    }
    while (FindNextFile(hFind,&coFindData));

    FindClose(hFind);
  }
#endif

  return dir_list;
}

// Returns the basic filename without the path
std::string
System::basename(std::string filename)
{
  // Should be replaced with STL
  const char* str = filename.c_str();
  int i;

  for(i = static_cast<int>(filename.size()) - 1; i >= 0; --i)
  {
    if (*(str + i) == '/') {
      break;
    }
  }

  return (str+i + 1);
}

std::string
System::dirname (std::string filename)
{
  const char* str = filename.c_str();
  int i;

  for(i = static_cast<int>(filename.size()) - 1; i >= 0; --i)
  {
    if (*(str + i) == '/') {
      break;
    }
  }

  return filename.substr(0, i);
}

bool
System::exist(std::string filename)
{
  return !access(filename.c_str(), F_OK);
}

void
System::create_dir(std::string directory)
{
#ifndef WIN32
  if (globals::pingus_debug_flags & PINGUS_DEBUG_DIRECTORIES)
  {
    std::cout << "System::create_dir: " << directory << std::endl;
  }

  if (!exist(directory))
  {
    if (mkdir(directory.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP) != 0)
    {
      throw std::runtime_error("System::create_dir: " + directory + ": " + strerror(errno));
    }
    else
    {
      std::cout << "Successfully created: " << directory << std::endl;
    }
  }
#else
  if (!CreateDirectory(directory.c_str(), 0))
  {
    DWORD dwError = GetLastError();
    if (dwError == ERROR_ALREADY_EXISTS)
    {
    }
    else if (dwError == ERROR_PATH_NOT_FOUND)
    {
      throw std::runtime_error("CreateDirectory: " + directory +
                               ": One or more intermediate directories do not exist; this function will only create the final directory in the path.");
    }
    else
    {
      throw std::runtime_error("CreateDirectory: " + directory + ": failed with error " + StringUtil::to_string(dwError));
    }
  }
  else
  {
    std::cout << "Successfully created: " << directory << std::endl;
  }
#endif
}

std::string
System::find_userdir()
{
#ifdef WIN32
  std::string tmpstr;
  char* appdata  = getenv("APPDATA");
  if (appdata)
  {
    tmpstr = std::string(appdata) + "/Pingus/";
    for (size_t pos = tmpstr.find('\\', 0); pos != std::string::npos; pos = tmpstr.find('\\', 0))
      tmpstr[pos] = '/';
  }
  else
  {
    tmpstr = "user/";
  }

  return tmpstr;

#else /* !WIN32 */
  char* homedir = getenv("HOME");

  if (homedir)
  {
    return std::string(homedir) + "/.pingus/";
  }
  else
  {
    throw std::runtime_error("Environment variable $HOME not set, fix that and start again.");
  }
#endif
}

void
System::init_directories()
{
  if (userdir.empty())
    userdir = find_userdir();

  std::string statdir  = get_userdir();

  create_dir(statdir);

  // FIXME: We need a better seperation between user created levels,
  // FIXME: third party levels and levels from the base distri
  create_dir(statdir + "levels/");
  create_dir(statdir + "levels/dist");
  create_dir(statdir + "themes/");

  // Savegames (FIXME: rename to savegames/?)
  create_dir(statdir + "savegames/");

  // User created images
  create_dir(statdir + "images/");

  // Thumbnail cache
  create_dir(statdir + "cache/");

  // Recorded demos will per default be writen in this directory
  create_dir(statdir + "demos/");

  // User created images
  create_dir(statdir + "backup/");

  // Screenshots will be dumped to that directory:
  create_dir(statdir + "screenshots/");
}

void
System::set_userdir(const std::string& u)
{
  userdir = u + "/";
}

std::string
System::get_userdir()
{
  return userdir;
}

std::string
System::get_cachedir()
{
  return get_userdir() + "cache/";
}

/** Returns the username of the current user or an empty string */
std::string
System::get_username()
{
  if (default_username.empty())
  {
    char* username = getenv("USERNAME");

    if (username)
      return std::string(username);
    else
      return "";
  }
  else
  {
    return default_username;
  }
}

/** Returns the EMail of the user or an empty string */
std::string
System::get_email()
{
  if (default_email.empty())
  {
    char* email = getenv("EMAIL");

    if (email)
      // FIXME: $EMAIL contains the complete from header, not only
      // the email address
      return std::string(email);
    else
      return "";
  }
  else
  {
    return default_email;
  }
}

std::string
System::get_language()
{
#ifdef WIN32
  char* lang_c = getenv("LC_MESSAGES");
#else
  char* lang_c = setlocale(LC_MESSAGES, NULL);
#endif

  std::string lang;

  if (lang_c)
    lang = lang_c;

  if (lang.empty() || lang == "C")
    lang = getenv("LANG");

  if (lang.empty() || lang == "C")
    return globals::default_language;
  else
    return lang.substr(0, 2);
}

std::string
System::checksum(const Pathname& pathname)
{
  return checksum(pathname.get_sys_path());
}

/** Read file and create a checksum and return it */
std::string
System::checksum(std::string filename)
{ // FIXME: Replace sys with SHA1 or MD5 or so 
  FILE* in;
  size_t bytes_read;
  char buffer[4096];
  long int checksum = 0;

  in = fopen(filename.c_str(), "r");

  if (!in)
  {
    std::cout << "System::checksum: Couldn't open file: " << filename << std::endl;
    return "";
  }

  do
  {
    bytes_read = fread(buffer, sizeof (char), 4096, in);

    if (bytes_read != 4096 && !feof(in))
    {
      throw std::runtime_error("System:checksum: file read error");
    }

    for (size_t i=0; i < bytes_read; ++i)
      checksum = checksum * 17 + buffer[i];
  }
  while (bytes_read != 0);

  fclose (in);
  
  std::ostringstream str;
  str << checksum;
  return str.str();
}

uint64_t
System::get_mtime(const std::string& filename)
{
#ifndef WIN32

  struct stat stat_buf;
  if (stat(filename.c_str(), &stat_buf) == 0)
    return stat_buf.st_mtime;
  else
    return 0;

#else

  struct _stat stat_buf;
  if (_stat(filename.c_str(), &stat_buf) == 0)
    return stat_buf.st_mtime;
  else
    return 0;

#endif
}

std::string
System::realpath(const std::string& pathname)
{
  std::string fullpath;
  std::string drive;
  
  if (pathname.size() > 0 && pathname[0] == '/')
  {
    fullpath = pathname;
  }
#ifdef WIN32
  else if (pathname.size() > 2 && pathname[1] == ':' && pathname[2] == '/')
  {
    drive = pathname.substr(0, 2);
    fullpath = pathname;
  }
#endif
  else
  {
    char buf[PATH_MAX];
    if (getcwd(buf, PATH_MAX) == 0)
    {
      std::cout << "System::realpath: Error: couldn't getcwd()" << std::endl;
      return pathname;
    }
#ifdef WIN32
    for (char *p = buf; *p; ++p)
    {
      if (*p == '\\')
        *p = '/';
    }
    drive.assign(buf, 2);
#endif
      
    fullpath = fullpath + buf + "/" + pathname;
  }
  
  std::string result;
  std::string::reverse_iterator last_slash = fullpath.rbegin();
  int skip = 0;
  // /foo/bar/../../bar/baz/
  //std::cout << "fullpath: '" << fullpath << "'" << std::endl;
  for(std::string::reverse_iterator i = fullpath.rbegin(); i != fullpath.rend(); ++i)
  { // FIXME: Little crude and hackish
    if (*i == '/')
    {
      std::string dir(last_slash, i); 
      //std::cout << "'" << dir << "'" << std::endl;
      if (dir == ".." || dir == "/..")
      {
        skip += 1;
      }
      else if (dir == "." || dir == "/." || dir.empty() || dir == "/")
      {
        // pass
      }
      else
      {
        if (skip == 0)
        {
          result += dir;
        }
        else
          skip -= 1;
      }

      last_slash = i;
    }
  }
  
  return drive + "/" + std::string(result.rbegin(), result.rend());
}

/* EOF */
