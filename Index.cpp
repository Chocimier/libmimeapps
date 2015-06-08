#include "Index.h"
#include "ConfigReader.h"
#include "Tools.h"

namespace LibMimeApps
{

std::vector<std::string>Index::directoryPatterns_ = Index::initDirectoryPatterns();

Index::Index()
{
	findDirectories();
	createBase();
}

std::vector<DesktopEntry> Index::appsForMime(const std::string &type)
{
	std::vector<DesktopEntry> result;

	if (applicationsCache_.count(type) > 0)
	{
		std::list<DesktopEntry*> list = applicationsCache_.at(type);
		for (std::list<DesktopEntry*>::iterator entry=list.begin();entry!=list.end();++entry)
		{
			result.push_back(**entry);
		}
	}

	return result;
}

void Index::findDirectories()
{
	directories_ = directoryPatterns_;

	bool again;

	do
	{
		std::vector<std::string> directories;

		again = false;

		for (std::vector<std::string>::iterator directory=directories_.begin();directory!=directories_.end();++directory)
		{
			std::vector<std::string> unfolded = unfoldVariable(*directory);

			if (unfolded.size() > 0 && unfolded.at(0) != *directory)
			{
				again = true;
			}

			for (std::vector<std::string>::iterator path=unfolded.begin();path!=unfolded.end();++path)
			{
				directories.push_back(*path);
			}
		}

		directories_.swap(directories);
		directories.clear();
	} while (again);
}

void Index::createBase()
{
	for (std::vector<std::string>::iterator directory=directories_.begin();directory!=directories_.end();++directory)
	{
		processDirectory(*directory, std::string());
	}
}

void Index::processDirectory(const std::string &baseDirectory, const std::string &relative)
{
	std::string directory = baseDirectory + relative;
	std::vector<std::string> subdirectories = directoryEntries(directory);

	for (std::vector<std::string>::iterator a=subdirectories.begin();a!=subdirectories.end();++a)
	{
		processDirectory(baseDirectory, relative + *a + "/");
	}

	processDesktopInDirectory(baseDirectory, relative);
	processMimeApps(directory + "mimeapps.list");
}

void Index::processDesktopInDirectory(const std::string &baseDirectory, const std::string &relative)
{
	std::vector<std::string> filenames = directoryEntries(baseDirectory + relative);

	for (std::vector<std::string>::iterator filename=filenames.begin();filename!=filenames.end();++filename)
	{
		if (endsWith(*filename, std::string(".desktop")))
		{
			processDesktopFile(baseDirectory, relative + *filename);
		}
	}
}

void Index::processMimeApps(const std::string &path)
{
	ConfigReader config(path);
	std::vector<std::string> types;

	types = config.keys("Added Associations");

	for (size_t i=0;i<types.size();++i)
	{
		std::vector<std::string> identifiers = split(config.value("Added Associations", types.at(i)), ';');

		for (int j=identifiers.size()-1;j>=0;--j)
		{
			if (knownApplications_.count(identifiers[j]) > 0)
			{
				addToType(types[i], knownApplications_.at(identifiers[j]));
			}
		}
	}

	types = config.keys("Removed Associations");

	for (size_t i=0;i<types.size();++i)
	{
		std::vector<std::string> identifiers = split(config.value("Removed Associations", types.at(i)), ';');

		for (size_t j=0;j<identifiers.size();++j)
		{
			removeFromType(types[i], identifiers[j]);
		}
	}
}

void Index::processDesktopFile(const std::string &baseDirectory, const std::string &relative)
{
	DesktopEntry *entry = new DesktopEntry(baseDirectory, relative);
	addApplication(entry);
}

void Index::addApplication(DesktopEntry *entry)
{
	for (std::map<std::string, std::list<DesktopEntry*> >::iterator type=applicationsCache_.begin();type!=applicationsCache_.end();++type)
	{
		removeFromType(type->first, entry->identifier);
	}

	knownApplications_[entry->identifier] = entry;

	for (std::vector<std::string>::iterator type=entry->types.begin();type!=entry->types.end();++type)
	{
		addToType(*type, entry);
	}
}

void Index::addToType(const std::string &type, DesktopEntry *entry)
{
	if (applicationsCache_.count(type) > 0)
	{
		removeFromType(type, entry->identifier);
	}

	applicationsCache_[type].push_front(entry);
}

void Index::removeFromType(const std::string &type, const std::string &entryId)
{
	if (applicationsCache_.count(type) > 0)
	{
		for (std::list<DesktopEntry*>::iterator it=applicationsCache_.at(type).begin();it!=applicationsCache_.at(type).end();)
		{
			if ((*it)->identifier == entryId)
			{
				applicationsCache_.at(type).erase(it++);
			}
			else
			{
				++it;
			}
		}
	}
}

std::vector<std::string> Index::initDirectoryPatterns()
{
	std::vector<std::string> result;

	result.push_back("$XDG_DATA_DIRS/applications/");
	result.push_back("$XDG_DATA_HOME/applications/");
	result.push_back("$XDG_CONFIG_DIRS/");
	result.push_back("$XDG_CONFIG_HOME/");

	return result;
}

}

