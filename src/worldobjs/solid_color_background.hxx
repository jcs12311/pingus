//  $Id: solid_color_background.hxx,v 1.1 2002/09/15 09:54:34 torangan Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_WORLDOBJS_SOLID_COLOR_BACKGROUND_HXX
#define HEADER_PINGUS_WORLDOBJS_SOLID_COLOR_BACKGROUND_HXX

#include "../worldobj.hxx"

namespace WorldObjsData {
class SolidColorBackgroundData;
}

namespace WorldObjs {

class SolidColorBackground : public WorldObj
{
private:
  WorldObjsData::SolidColorBackgroundData* data;
  
public:
  SolidColorBackground (WorldObjsData::SolidColorBackgroundData* data_);
 ~SolidColorBackground ();

  // FIXME: Make z_position editable
  float get_z_pos () const { return -10; }  
  void update (float delta) { UNUSED_ARG(delta); }
  
  void draw_offset (int x_of, int y_of, float s = 1.0);
  
private:
  SolidColorBackground (const SolidColorBackground&);
  SolidColorBackground operator= (const SolidColorBackground&);
};

} // namespace WorldObjs

#endif

/* EOF */