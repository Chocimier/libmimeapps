#include "Tools.h"

#include <dirent.h>

#include <algorithm>
#include <cstring>
#include <map>
#include <sstream>

namespace LibMimeApps
{

bool startsWith(const std::string &str, const std::string &prefix)
{
	if (str.size() < prefix.size())
	{
		return false;
	}

	return std::equal(prefix.begin(), prefix.end(), str.begin());
}

bool endsWith(std::string const &str, std::string const &suffix)
{
	if (str.size() < suffix.size())
	{
		return false;
	}

	return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

std::vector<std::string> split(const std::string &str, char delim)
{
	std::vector<std::string> chunks;
	std::stringstream stream(str);
	std::string item;

	while (std::getline(stream, item, delim))
	{
		chunks.push_back(item);
	}

	return chunks;
}

bool match(std::string const& text, std::string const& pattern)
{
	return std::search(text.begin(), text.end(),  pattern.begin(), pattern.end() ) != text.end();
}

std::vector<std::string> directoryEntries(const std::string &directory)
{
	std::vector<std::string> result;
	DIR *stream = opendir(directory.c_str());

	if (stream == NULL)
	{
		return result;
	}

	struct dirent *entry;

	while ((entry = readdir(stream)) != NULL)
	{
		std::string name(entry->d_name);
		if (name.size() > 0 && name.at(0) != '.')
			result.push_back(name);
	}

	closedir(stream);

	return result;
}

std::vector<std::string> unfoldVariable(const std::string &string)
{
	std::vector<std::string> result;

	if (!match(string, "$"))
	{
		result.push_back(string);

		return result;
	}

	int begin = 0;

	while (string.at(begin) != '$')
	{
		++begin;
	}

	int end = begin+1;

	while (std::isalnum(string.at(end)) || string.at(end) == '_')
	{
		++end;
	}

	std::string name = string.substr(begin+1, end-(begin+1));

	std::vector<std::string> values = getVariableValues(name);

	for (std::vector<std::string>::iterator value=values.begin();value!=values.end();++value)
	{
		result.push_back(string.substr(0, begin) + (*value) + string.substr(end));
	}

	return result;
}

std::vector<std::string> getVariableValues(const std::string &name)
{
	std::string value;
	char *env = std::getenv(name.c_str());

	if (env && std::strlen(env) > 0)
	{
		value = std::string(env);
	}
	else
	{
		std::map<std::string, std::string> defaultVariableValues;
		defaultVariableValues["XDG_DATA_HOME"] = std::string("$HOME/.local/share");
		defaultVariableValues["XDG_CONFIG_HOME"] = std::string("$HOME/.config");
		defaultVariableValues["XDG_DATA_DIRS"] = std::string("/usr/local/share/:/usr/share/");
		defaultVariableValues["XDG_CONFIG_DIRS"] = std::string("/etc/xdg");

		if (defaultVariableValues.count(name) > 0)
		{
			value = defaultVariableValues.at(name);
		}
	}

	return split(value, ':');
}

std::string getLocaleValue(const ConfigReader &config, const std::string &group, const std::string &key, const std::string &language)
{
	lang wanted(language);
	std::vector<std::string> localeKeys;

	if (wanted.country.size() > 0 && wanted.modifier.size() > 0)
	{
		localeKeys.push_back(wanted.language + "_" + wanted.country + "@" + wanted.modifier);
	}

	if (wanted.country.size() > 0)
	{
		localeKeys.push_back(wanted.language + "_" + wanted.country);
	}

	if (wanted.modifier.size() > 0)
	{
		localeKeys.push_back(wanted.language + "@" + wanted.modifier);
	}

	localeKeys.push_back(wanted.language);

	for (size_t i=0;i<localeKeys.size();++i)
	{
		std::string localeKey = key + "[" + localeKeys[i] + "]";

		if (config.hasKey(group, localeKey))
		{
			return config.value(group, localeKey);
		}
	}

	return config.value(group, key);
}

std::string alnums(const std::string &string, size_t begin)
{
	if (begin == std::string::npos || begin >= string.size())
	{
		return std::string();
	}

	size_t end = begin;

	while (end < string.size() && std::isalnum(string.at(end)))
	{
		++end;
	}

	return string.substr(begin, end-begin);
}

}
