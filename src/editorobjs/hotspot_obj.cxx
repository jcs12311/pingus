//  $Id: hotspot_obj.cxx,v 1.2 2002/09/27 18:36:40 torangan Exp $
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

#include "../worldobjsdata/hotspot_data.hxx"
#include "../string_converter.hxx"
#include "hotspot_obj.hxx"

namespace EditorObjs {

HotspotObj::HotspotObj (const WorldObjsData::HotspotData& data_)
  : SpriteEditorObj (data_.desc),
    data(new WorldObjsData::HotspotData(data_))
{
  pos_ref = &data->pos;
}

void
HotspotObj::write_xml (std::ostream& xml)
{
  data->write_xml(xml);
}

EditorObj*
HotspotObj::duplicate ()
{
  return new HotspotObj(*data);
}

std::string
HotspotObj::status_line ()
{
  return "Hotspot: "  
         + to_string(data->pos.x) + ", "
	 + to_string(data->pos.y) + ", "
	 + to_string(data->pos.z);
}

} // namespace EditorObjs

/* EOF */