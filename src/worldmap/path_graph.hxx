//  $Id: path_graph.hxx,v 1.7 2002/10/16 09:14:45 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PATH_GRAPH_HXX
#define HEADER_PATH_GRAPH_HXX

#include <map>
#include <vector>
#include "../vector.hxx"
#include "../libxmlfwd.hxx"
#include "path.hxx"
#include "pathfinder.hxx"
#include "graph.hxx"

namespace WorldMapNS {

class Dot;
class WorldMap;

/** This class represents the walkable path on the Worldmap */
class PathGraph
{
private:
  WorldMap* worldmap;

public:
  // FIXME: Memory leak? Where do we free stuff data inside the graph?
  // FIXME: shouldn't be public
  Graph<Dot*, Path*> graph;

  std::vector<Dot*> dots;
  typedef std::vector<Pathfinder<Dot*, Path*>* > PFinderCache;
  PFinderCache pathfinder_cache;
private:

  // FIXME: This could/should probally be moved inside the graph (or not?!)
  /** Map to look up node names and get the coresponding id's */
  std::map<std::string, NodeId> node_lookup;

  /** Map to look up edge names and get the corresponding id's */
  std::map<std::string, EdgeId> edge_lookup;

public:
  /** @param worldmap is a pointer to the worldmap that holds this
      PathGraph, it is used so that the PathGraph can insert its
      drawables into the world */
  PathGraph(WorldMap* worldmap, xmlDocPtr doc, xmlNodePtr cur);

  /** @return a list of positions to walk to reach node \a end, by
      starting from \a start */
  PathfinderResult get_path(NodeId start, NodeId end);

  /** Get a node by it id */
  Dot* get_dot(NodeId id);

  /** Get a node by its position */
  Dot* get_dot(float x, float y);

  EdgeId lookup_edge(const std::string& name);
  NodeId lookup_node(const std::string& name);

private:
  void parse_nodes(xmlDocPtr doc, xmlNodePtr cur);
  void parse_edges(xmlDocPtr doc, xmlNodePtr cur);

  PathGraph (const PathGraph&);
  PathGraph& operator= (const PathGraph&);
};

} // namespace WorldMapNS

#endif

/* EOF */