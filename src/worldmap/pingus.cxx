//  $Id: pingus.cxx,v 1.31 2003/04/10 14:36:35 grumbel Exp $
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

#include <iostream>
#include <math.h>
#include "../gui/graphic_context.hxx"
#include "dot.hxx"
#include "../math.hxx"
#include "pingus.hxx"

namespace WorldMapNS {

Pingus::Pingus (PathGraph* arg_path)
  : Drawable("pingus"),
    path(arg_path),
    sprite ("worldmap/pingus", "core", 27.0f, Sprite::RIGHT),
    sprite_standing ("worldmap/pingus_standing", "core"),
    arrow ("worldmap/arrow", "core")
{
  arrow.set_align_center_bottom();

  pos.x = 320;
  pos.y = 200;

  sprite.set_align (-sprite.get_width()/2,  2 - sprite.get_height());
  sprite_standing.set_align (-sprite_standing.get_width()/2,  
                             -sprite_standing.get_height());
}

Pingus::~Pingus ()
{
}


void
Pingus::draw (GraphicContext& gc)
{
  if (final_target_node != NoNode && current_node == NoNode)
    {
      gc.draw(arrow, path->get_dot(final_target_node)->get_pos());
    }

  // FIXME: Replace the sprite and add up/down here
  float direction = get_direction();
  if (direction >= 0 && direction < 180)
    sprite.set_direction(Sprite::RIGHT);
  else
    sprite.set_direction(Sprite::LEFT);

  if (!is_walking())
    gc.draw(sprite_standing, pos);
  else
    gc.draw(sprite, pos);
}

void
Pingus::update (float delta)
{
  sprite.update (delta);
  if (is_walking())
    update_walk(delta);
}

void
Pingus::update_walk (float delta)
{
  float velocity = 70.0f;

  //std::cout << "Updating Walk: " << edge_path_position << "/" << edge_path_length << std::endl;
  // Update the edge_path_position
  edge_path_position += velocity * delta;
  
  if (edge_path_position > edge_path.length()) // target reached
    {
      if (node_path.empty ()) // final target reached
        {
          current_node = target_node;
          final_target_node = NoNode;
        }
      else // edge is traveled, now go to the next node
        {
          update_edge_path();
        }
    }

  // Recalc pingu position on the screen
  last_pos = pos;
  pos = calc_pos ();
}

float
Pingus::get_direction() const
{
  return (atan2(last_pos.x - pos.x,
                -(last_pos.y - pos.y)) / Math::pi * 180.0f) + 180.0f;
}

bool
Pingus::walk_to_node (NodeId target)
{
  final_target_node = target;

  if (current_node == target)
    {
      return true;
    }
  else if (current_node != NoNode) // pingu stands still
    {
      const PathfinderResult& res = path->get_path (current_node, target);

      if (res.path.empty())
        {
          // No path could be found
          return false;
        }
      else
        {
          node_path = res.path;

          // Simulate that we just reached current_node, then update the edge_path
          target_node = node_path.back(); // equal to current_node;
          node_path.pop_back();
          update_edge_path();

          current_node = NoNode;
          return true;
        }
    }
  else // pingu between two nodes
    {
      if (target_node == target)
        {
          node_path.clear();
          return true;
        }
      else if (source_node == target)
        {
          // Reverse the pingu
          std::swap(target_node, source_node);
          edge_path.reverse();
          edge_path_position = edge_path.length() - edge_path_position;         
          node_path.clear();
          return true;
        }
      else
        {
          const PathfinderResult& node_path1 = path->get_path (source_node, target);
          const PathfinderResult& node_path2 = path->get_path (target_node, target);
	
          // Check that a path exist
          if (node_path1.path.empty())
            {
              if (node_path2.path.empty())
                {
                  return false;
                }
              else
                {
                  node_path = node_path2.path;
                }
            }
          else
            {
              // Select the shorter path
              if (node_path1.cost + edge_path_position
                  < node_path2.cost + (edge_path.length() - edge_path_position))
                { // walk to source node, which means to reverse the pingu
                  node_path = node_path1.path;

                  // Reverse the pingu
                  std::swap(target_node, source_node);
                  edge_path.reverse();
                  edge_path_position = edge_path.length() - edge_path_position;
                }
              else
                { // walk to target_node
                  node_path = node_path2.path;
                }
            }

          // Pop the first element on the stack, since we are already targeting it
          node_path.pop_back();

          return true;
        }
    }
}

Vector
Pingus::calc_pos ()
{
  if (current_node != NoNode) // pingu stands still
    {
      return path->graph.resolve_node(current_node).data->get_pos ();
    }
  else // between two nodes
    {
      return edge_path.at(edge_path_position);
    }
}

void
Pingus::set_position (NodeId node)
{
  pos = path->get_dot(node)->get_pos();
  current_node = node;
}

float
Pingus::get_z_pos() const
{
  /** We add 1.0f here so that the pingu is guranteed to stay above
      the level-dots (this is a hack), but I currently don't know a
      better way, since both pingu and level dot have the same
      z-pos */
  return pos.z + 10.0f;
}

void
Pingus::update_edge_path()
{
  // Update source and target nodes
  source_node = target_node;
  target_node = node_path.back ();
  node_path.pop_back (); // remove target node from list of nodes

  edge_path_position = 0.0f;
  edge_path.clear();

  Path* partial_path = path->graph.resolve_edge(source_node, target_node).data;
          
  edge_path.push_back(path->graph.resolve_node(source_node).data->get_pos());
  // Why do we need to reverse this?!
  edge_path.reverse_insert(*partial_path);
  edge_path.push_back(path->graph.resolve_node(target_node).data->get_pos());
}

bool
Pingus::is_walking()
{
  return current_node == NoNode;
}

} // namespace WorldMapNS

/* EOF */
