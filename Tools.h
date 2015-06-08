#ifndef LIBMIMEAPPS_TOOLS_H
#define LIBMIMEAPPS_TOOLS_H

#include <string>
#include <vector>

#include "ConfigReader.h"

namespace LibMimeApps
{

bool startsWith(const std::string &str, const std::string &prefix);
bool endsWith(std::string const &str, std::string const &suffix);
std::vector<std::string> split(const std::string &str, const char delimiter);
bool match(std::string const& text, std::string const& pattern);
std::vector<std::string> directoryEntries(const std::string &directory);
std::vector<std::string> unfoldVariable(const std::string &string);
std::vector<std::string> getVariableValues(const std::string &name);
std::string getLocaleValue(const ConfigReader &config, const std::string &group, const std::string &key, const std::string &language);
std::string alnums(const std::string &string, size_t begin);

struct lang {
	std::string language;
	std::string country;
	std::string modifier;

	lang()
	{
	}

	explicit lang(const std::string &string)
	{
		language = alnums(string, 0);

		if (match(string, "_"))
		{
			country= alnums(string, string.find('_')+1);
		}

		if (match(string, "@"))
		{
			modifier = alnums(string, string.find('@')+1);
		}
	}
};

}

#endif
