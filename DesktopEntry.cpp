#include "DesktopEntry.h"

#include <algorithm>
#include <fstream>

#include "Tools.h"

namespace LibMimeApps
{

DesktopEntry::DesktopEntry(const std::string &baseDirectory, const std::string &relative)
{
	path = baseDirectory + relative;

	std::ifstream file(path.c_str());

	identifier = relative;

	std::replace(identifier.begin(), identifier.end(), '/', '-');

	std::string line;
	std::string group;

	while (std::getline(file, line))
	{
		if (line.size() == 0 || line.at(0) == '#')
		{
			continue;
		}
		else if (line.at(0) == '[')
		{
			group = line;
		}

		if (group != "[Desktop Entry]")
		{
			continue;
		}

		if (startsWith(line, "Name="))
		{
			name = split(line, '=').at(1);
		}
		else if (startsWith(line, "Icon="))
		{
			icon = split(line, '=').at(1);
		}
		else if (startsWith(line, "Exec="))
		{
			executable = split(line, '=').at(1);
		}
		else if (startsWith(line, "MimeType="))
		{
			std::vector<std::string> a = split(line, '=');
			if (a.size() > 1)
			{
				types = split(a.at(1), ';');
			}
		}
	}
}

}
