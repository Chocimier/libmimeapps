#ifndef LIBMIMEAPPS_DESKTOPENTRY_H
#define LIBMIMEAPPS_DESKTOPENTRY_H

#include <string>
#include <vector>

namespace LibMimeApps
{

struct DesktopEntry
{
	explicit DesktopEntry(const std::string &baseDirectory, const std::string &relative);

	std::string name;
	std::string icon;
	std::string executable;
	std::string identifier;
	std::string path;
	std::vector< std::string > types;
};


}
#endif
