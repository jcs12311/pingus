//  $Id: woodthing.hxx,v 1.4 2003/10/19 12:25:48 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDOBJS_ENTRANCES_WOODTHING_HXX
#define HEADER_PINGUS_WORLDOBJS_ENTRANCES_WOODTHING_HXX

#include "../../game_counter.hxx"
#include "../entrance.hxx"

namespace Pingus {
namespace WorldObjs {
namespace Entrances {

class WoodThing : public Entrance
{
private:
  GameCounter counter;
  CL_Surface  surface2;

public:
  WoodThing (const WorldObjsData::EntranceData& data_);

  void update();
  void draw (GraphicContext& gc);

private:
  WoodThing (const WoodThing&);
  WoodThing& operator= (const WoodThing&);
};

} // namespace Entrances
} // namespace WorldObjs
} // namespace Pingus

#endif

/* EOF */

