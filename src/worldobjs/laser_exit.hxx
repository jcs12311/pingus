//  $Id: laser_exit.hxx,v 1.3 2002/09/10 19:24:19 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_PINGUS_WORLDOBJS_LASER_EXIT_HXX
#define HEADER_PINGUS_WORLDOBJS_LASER_EXIT_HXX

#include "../worldobj.hxx"

namespace WorldObjsData {
class LaserExitData;
} // namespace WorldObjsData

class Pingu;

namespace WorldObjs {

class LaserExit : public WorldObj
{
private:
  bool killing;
  WorldObjsData::LaserExitData* const data;
    
public:
  LaserExit (WorldObjsData::LaserExitData* data_);
  ~LaserExit ();

  float get_z_pos () const;

  void draw (GraphicContext& gc);
  void update (float delta);

protected:
  void catch_pingu (Pingu*);

private:
  LaserExit (const LaserExit&);
  LaserExit operator= (const LaserExit&);
}; 

} // namespace WorldObjs

#endif

/* EOF */