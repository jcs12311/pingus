//  Pingus - A free Lemmings clone
//  Copyright (C) 2008 Ingo Ruhnke <grumbel@gmx.de>
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

#include "pingus/worldmap/worldmap_component.hpp"

#include "engine/display/display.hpp"
#include "pingus/worldmap/worldmap.hpp"
#include "pingus/worldmap/worldmap_screen.hpp"

namespace WorldmapNS {

WorldmapComponent::WorldmapComponent(WorldmapScreen* worldmap_screen_) :
  scene_context(new SceneContext),
  worldmap_screen(worldmap_screen_)    
{
}

WorldmapComponent::~WorldmapComponent()
{
}

void
WorldmapComponent::draw (DrawingContext& gc)
{
  Worldmap* worldmap = worldmap_screen->get_worldmap();

  Rect cliprect = worldmap_screen->get_trans_rect();

  scene_context->clear();
  scene_context->push_modelview();
  scene_context->translate(cliprect.left, cliprect.top);

  scene_context->set_cliprect(cliprect);

  //scene_context->color().draw_fillrect(-100, -100, 2000, 2000, Color(255,0,0,0), -10000);
  worldmap->draw(scene_context->color());

  gc.draw(new SceneContextDrawingRequest(scene_context.get(), Vector2i(0,0), -1000));

  scene_context->pop_modelview();

  // Draw border
  if (cliprect != Rect(Vector2i(0,0), Size(Display::get_width(), Display::get_height())))
  {
    Color border_color(0, 0, 0);
    // top
    gc.draw_fillrect(Rect(0, 0, Display::get_width(), cliprect.top),
                     border_color);
    // bottom
    gc.draw_fillrect(Rect(0, cliprect.bottom, Display::get_width(), Display::get_height()),
                     border_color);
    // left
    gc.draw_fillrect(Rect(0, cliprect.top, cliprect.left, cliprect.bottom),
                     border_color);
    // right
    gc.draw_fillrect(Rect(cliprect.right, cliprect.top, Display::get_width(), cliprect.bottom),
                     border_color);
  }
}

void
WorldmapComponent::update (float delta)
{
  worldmap_screen->get_worldmap()->update(delta);
}

void
WorldmapComponent::on_primary_button_press (int x, int y)
{
  Rect cliprect = worldmap_screen->get_trans_rect();
  worldmap_screen->get_worldmap()->on_primary_button_press(x - cliprect.left,
                                                           y - cliprect.top);
}

void
WorldmapComponent::on_pointer_move (int x, int y)
{
  Rect cliprect = worldmap_screen->get_trans_rect();
  worldmap_screen->get_worldmap()->on_pointer_move(x - cliprect.left,
                                                   y - cliprect.top);
}

void
WorldmapComponent::on_secondary_button_press (int x, int y)
{
  Rect cliprect = worldmap_screen->get_trans_rect();
  worldmap_screen->get_worldmap()->on_secondary_button_press(x - cliprect.left,
                                                             y - cliprect.top);
}

} // namespace WorldmapNS

/* EOF */
