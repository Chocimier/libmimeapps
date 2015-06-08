#ifndef LIBMIMEAPPS_TOOLS_H
#define LIBMIMEAPPS_TOOLS_H

#include <string>
#include <vector>

namespace LibMimeApps
{

bool startsWith(const std::string &str, const std::string &prefix);
bool endsWith(std::string const &str, std::string const &suffix);
std::vector< std::string > split(const std::string &str, const char delimiter);
bool match(std::string const& text, std::string const& pattern);
std::vector< std::string > directoryEntries(const std::string &directory);
std::vector<std::string> unfoldVariable(const std::string &string);
std::vector<std::string> getVariableValues(const std::string &name);

}

#endif
