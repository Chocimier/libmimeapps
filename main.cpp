#include <iostream>

#include "../libmimeapps/Index.h"

int main()
{
	LibMimeApps::Index index("pl_PL");

	std::vector<std::string> files{"/home/piotr/image.png", "/home/piotr/image2.png"};
	std::vector<std::string> urls{"http://example.com/image.png", "https://example.com/image.png"};
	auto apps = index.appsForMime(std::string("image/png"));


	for (auto &app: apps)
	{
		std::cout << app.name() << std::endl;
		auto words = (app.execAllowRemoteUrl() ? app.parseExec(urls) : app.parseExec(files));
		for (auto &word: words)
			std::cout << "'" << word << "' ";
		std::cout << std::endl;
	}

}
