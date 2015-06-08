#include "ConfigReader.h"

#include <fstream>

#include "Tools.h"

namespace LibMimeApps
{

ConfigReader::ConfigReader(const std::string &path)
{
	std::ifstream file(path.c_str());
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
			group = line.substr(1, line.find(']')-1);

			if (values_.count(group) < 1)
			{
				values_[group] = std::map<std::string, std::string>();
			}
		}
		else
		{
			size_t pos = line.find('=');

			if ((pos != std::string::npos) && (pos != (line.size()-1)))
			{
				std::string key(line.substr(0, pos));
				std::string value(line.substr(pos+1));

				values_[group][key] = value;
			}
		}
	}
}

std::vector<std::string> ConfigReader::groups() const
{
	std::vector<std::string> result;

	for (std::map< std::string, std::map<std::string, std::string> >::const_iterator it=values_.begin();it!=values_.end();++it)
	{
		result.push_back(it->first);
	}

	return result;
}

bool ConfigReader::hasGroup(const std::string &group) const
{
	return (values_.find(group) != values_.end());
}

std::vector<std::string> ConfigReader::keys(const std::string &group) const
{
	std::vector<std::string> result;

	if (!hasGroup(group))
	{
		return result;
	}

	for (std::map<std::string, std::string>::const_iterator it=values_.at(group).begin();it!=values_.at(group).end();++it)
	{
		result.push_back(it->first);
	}

	return result;
}

bool ConfigReader::hasKey(const std::string &group, const std::string &key) const
{
	return (hasGroup(group) && (values_.at(group).find(key) != values_.at(group).end()));
}

std::string ConfigReader::value(const std::string &group, const std::string &key) const
{
	if (!hasKey(group, key))
	{
		return std::string();
	}

	return values_.at(group).at(key);
}

}

