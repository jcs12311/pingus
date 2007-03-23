//  $Id: xml_file_writer.cxx,v 1.6 2004/03/31 18:17:38 torangan Exp $
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

#include <iostream>
#include <map>
#include "vector.hpp"
///#include "xml_file_writer.hpp"


XMLFileWriter::XMLFileWriter(std::ostream& out_)
  : out(&out_)
{
	(*out) << "<?xml version=\"1.0\"  encoding=\"ISO-8859-1\"?>\n\n";
}

XMLFileWriter::~XMLFileWriter()
{

}

void
XMLFileWriter::begin_section (const char* name)
{
  (*out) << "<" << name << ">\n";
  section_stack.push(name);
}

void
XMLFileWriter::begin_section (const char* name, const char* attributes)
{
  (*out) << "<" << name << " " << attributes << ">\n";
  section_stack.push(name);
}

void
XMLFileWriter::end_section ()
{
  const std::string& section_name = section_stack.top();

  (*out) << "</" << section_name << ">\n";

  section_stack.pop();
}

void
XMLFileWriter::write_int    (const char* name, int value)
{
  (*out) << "<" << name << ">" << value << "</" << name << ">\n";
}

void
XMLFileWriter::write_float  (const char* name, float value)
{
  (*out) << "<" << name << ">" << value << "</" << name << ">\n";
}

void
XMLFileWriter::write_color  (const char* name, const Color& color)
{
  (*out) << "<" << name << ">\n"
         << "  <red>"   << int(color.r * 255)   << "</red>\n"
         << "  <green>" << int(color.g * 255) << "</green>\n"
         << "  <blue>"  << int(color.b * 255) << "</blue>\n"
         << "  <alpha>" << int(color.a * 255) << "</alpha>\n"
         << "</" << name << ">"
         << std::endl;
}

void
XMLFileWriter::write_bool   (const char* name, bool value)
{
  (*out) << "<" << name << ">" << value << "</" << name << ">\n";
}

void
XMLFileWriter::write_string (const char* name, const std::string& value)
{
	// Perform basic XML encoding (turns apostrophes into &apos;, etc.
	std::string new_value = value;
	std::string::size_type pos;

	std::map<std::string, std::string> replacements;
	
	replacements["&"] = "&amp;";
	replacements["\""] = "&quot;";
	replacements["\'"] = "&apos;";
	replacements["<"] = "&lt;";
	replacements[">"] = "&gt;";

	for (std::map<std::string, std::string>::iterator i = replacements.begin();
		i != replacements.end(); i++)
	{
		for (pos = new_value.find(i->first); pos != std::string::npos; pos = new_value.find(i->first))
		{
			// Replace character with encoding characters
			new_value.replace(pos, 1, i->second);
		}
	}
	
	(*out) << "<" << name << ">" << new_value << "</" << name << ">\n";
}

void
XMLFileWriter::write_vector (const char* name, const Vector3f& value)
{
  (*out) << "<" << name << ">\n"
         << "  <x>" << value.x << "</x>\n"
         << "  <y>" << value.y << "</y>\n"
         << "  <z>" << value.z << "</z>\n"
         << "</" << name << ">\n";
}

/* EOF */