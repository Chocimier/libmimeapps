#ifndef LIBMIMEAPPS_CONFIGREADER_H
#define LIBMIMEAPPS_CONFIGREADER_H

#include <map>
#include <string>
#include <vector>

namespace LibMimeApps
{

class ConfigReader
{
public:
	explicit ConfigReader(const std::string &path);
	std::vector<std::string> groups() const;
	bool hasGroup(const std::string &group) const;
	std::vector<std::string> keys(const std::string &group) const;
	bool hasKey(const std::string &group, const std::string &key) const;
	std::string value(const std::string &group, const std::string &key) const;

private:
	std::map< std::string, std::map<std::string, std::string> > values_;
};

}

#endif
