#ifndef LIBMIMEAPPS_INDEX_H
#define LIBMIMEAPPS_INDEX_H

#include <list>
#include <map>
#include <string>
#include <vector>

#include "DesktopEntry.h"

namespace LibMimeApps
{

class Index
{
public:
	Index();
	explicit Index(const std::string &language);
	std::vector<DesktopEntry> appsForMime(const std::string &type);

protected:
	void findDirectories();
	void createBase();
	void processDirectory(const std::string &baseDirectory, const std::string &relative);
	void processDesktopInDirectory(const std::string &baseDirectory, const std::string &relative);
	void processMimeApps(const std::string &path);
	void processDesktopFile(const std::string &baseDirectory, const std::string &relative);
	void addApplication(DesktopEntry *entry);
	void addToType(const std::string &type, DesktopEntry *entry);
	void removeFromType(const std::string &type, const std::string &entryId);
	static std::list<std::string> resolveVariable(const std::string &name);
	static std::vector<std::string> initDirectoryPatterns();

private:
	static std::vector<std::string> directoryPatterns_;
	std::map<std::string, DesktopEntry*> knownApplications_;
	std::map<std::string, std::list<DesktopEntry*> > applicationsCache_;
	std::vector<std::string> directories_;
	std::string language_;
};

}

#endif
