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

#include "pingus/worldobjs/switch_door.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"

namespace WorldObjs {

SwitchDoor::SwitchDoor(const FileReader& reader) :
  door_pos(),
  switch_pos(),
  door_height(),
  door_box     ("worldobjs/switchdoor_box"),
  door_box_cmap("worldobjs/switchdoor_box"),
  door_tile    ("worldobjs/switchdoor_tile"),
  door_tile_cmap("worldobjs/switchdoor_tile_cmap"),
  switch_sur   ("worldobjs/switchdoor_switch"),
  is_opening(false),
  current_door_height()
{
  FileReader subreader;
  reader.read_section("switch", subreader);
  subreader.read_vector("position", switch_pos);

  reader.read_section("door", subreader);
  subreader.read_vector("position", door_pos);
  subreader.read_int("height", door_height);
  
  current_door_height = door_height;
}

void
SwitchDoor::on_startup ()
{
  world->get_colmap()->put(door_box_cmap,
                           static_cast<int>(door_pos.x),
                           static_cast<int>(door_pos.y),
                           Groundtype::GP_SOLID);

  for (int i=0; i < door_height; ++i)
    world->get_colmap()->put(door_tile_cmap,
                             static_cast<int>(door_pos.x),
                             static_cast<int>(door_pos.y)
                             + i * door_tile.get_height()
                             + door_box.get_height(),
                             Groundtype::GP_SOLID);
}

void
SwitchDoor::draw (SceneContext& gc)
{
  gc.color().draw (door_box, door_pos);
  for (int i=0; i < current_door_height; ++i)
    gc.color().draw(door_tile, Vector3f(door_pos.x, 
                                        door_pos.y + static_cast<float>(i * door_tile.get_height() + door_box.get_height())));

  gc.color().draw(switch_sur, switch_pos);
}

void
SwitchDoor::update ()
{
  if (current_door_height > 0)
  {
    if (!is_opening)
    {
      // Check if a pingu is passing the switch
      PinguHolder* holder = world->get_pingus();

      for (PinguIter pingu = holder->begin (); pingu != holder->end (); ++pingu)
      {
        if ((*pingu)->get_pos().x > switch_pos.x &&
            (*pingu)->get_pos().x < switch_pos.x + static_cast<float>(switch_sur.get_width()) &&
            (*pingu)->get_pos().y > switch_pos.y &&
            (*pingu)->get_pos().y < switch_pos.y + static_cast<float>(switch_sur.get_height()))
        {
          is_opening = true;
        }
      }
    }
    else
    {
      // Open the door
      --current_door_height;

      // If the door is opend enough, so that a pingus fits under
      // it, we remove the door from the colmap
      if (current_door_height + 10 < door_height)
      {
        world->get_colmap()->put(door_box_cmap,
                                 static_cast<int>(door_pos.x),
                                 static_cast<int>(door_pos.y),
                                 Groundtype::GP_NOTHING);
        for (int i=0; i < door_height; ++i)
          world->get_colmap()->put(door_tile_cmap,
                                   static_cast<int>(door_pos.x),
                                   static_cast<int>(door_pos.y) + i * door_tile.get_height()
                                   + door_box.get_height(),
                                   Groundtype::GP_NOTHING);
      }
    }
  }
}

} // namespace WorldObjs

/* EOF */
