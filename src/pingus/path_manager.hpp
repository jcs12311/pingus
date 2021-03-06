//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_PINGUS_PATH_MANAGER_HPP
#define HEADER_PINGUS_PINGUS_PATH_MANAGER_HPP

#include <list>
#include <string>

class PathManager
{
private:
  std::string base_path;

public:
  PathManager();
  ~PathManager();

  /** Set the path directly without using find_path/add_path
      Must include trailing slash */
  void set_path(const std::string& path);

  std::string get_path() const { return base_path; }

  /** Complete a releative path to the absolute path, the returned
      path contains a trailing slash */
  std::string complete(const std::string& relative_path);

private:
  PathManager(const PathManager&);
  PathManager& operator=(const PathManager&);
};

extern PathManager g_path_manager;

#endif

/* EOF */
