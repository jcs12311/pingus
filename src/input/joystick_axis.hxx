//  $Id: joystick_axis.hxx,v 1.3 2002/07/09 17:00:10 torangan Exp $
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

#ifndef HEADER_PINGUS_INPUT_JOYSTICK_AXIS_HXX
#define HEADER_PINGUS_INPUT_JOYSTICK_AXIS_HXX

#include "axis.hxx"

namespace Input
{
  class JoystickAxis : public Axis {

  private:
    int     id;
    int     axis;
    float   angle;
    
  public:
  
    JoystickAxis(int id_, int axis_, float angle_);

    virtual float get_pos ();
    virtual float get_angle ();
    virtual void  update (float);
  };
}

#endif

/* EOF */