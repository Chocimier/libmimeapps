#include "DesktopEntry.h"

#include <algorithm>

#include "ConfigReader.h"
#include "Tools.h"

namespace LibMimeApps
{

DesktopEntry::DesktopEntry(const std::string &baseDirectory, const std::string &relative)
{
	path = baseDirectory + relative;
	identifier = relative;

	ConfigReader config(path);

	std::replace(identifier.begin(), identifier.end(), '/', '-');

	name = config.value(std::string("Desktop Entry"), std::string("Name"));
	icon = config.value(std::string("Desktop Entry"), std::string("Icon"));
	executable = config.value(std::string("Desktop Entry"), std::string("Exec"));
	types = split(config.value(std::string("Desktop Entry"), std::string("MimeType")), ';');
}

}
