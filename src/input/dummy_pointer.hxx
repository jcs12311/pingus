//  $Id: dummy_pointer.hxx,v 1.1 2002/07/10 14:06:06 torangan Exp $
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

#ifndef HEADER_PINGUS_INPUT_DUMMY_POINTER_HXX
#define HEADER_PINGUS_INPUT_DUMMY_POINTER_HXX

#include "pointer.hxx"

namespace Input
{
  class DummyPointer : public Pointer {
  
    public:

      virtual float get_x_pos () { return 0; }
      virtual float get_y_pos () { return 0; }
      virtual void  set_pos (float, float) { }
      virtual void  update (float)         { }
  };
}

#endif

/* EOF */