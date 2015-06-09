/*
libmimeapps, an implementation of http://standards.freedesktop.org/mime-apps-spec/mime-apps-spec-latest.html

Copyright (c) 2015, Piotr Wójcik
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "DesktopEntry.h"

#include <algorithm>

#include "ConfigReader.h"
#include "Tools.h"

namespace LibMimeApps
{

DesktopEntry::DesktopEntry(const std::string &baseDirectory, const std::string &relative, const std::string &language)
{
	path_ = baseDirectory + relative;
	identifier_ = relative;

	ConfigReader config(path_);

	std::replace(identifier_.begin(), identifier_.end(), '/', '-');

	name_ = getLocaleValue(config, std::string("Desktop Entry"), std::string("Name"), language);
	icon_ = getLocaleValue(config, std::string("Desktop Entry"), std::string("Icon"), language);
	executable_ = config.value(std::string("Desktop Entry"), std::string("Exec"));
	types_ = split(config.value(std::string("Desktop Entry"), std::string("MimeType")), ';');
	noDisplay_ = (config.value(std::string("Desktop Entry"), std::string("NoDisplay")) == std::string("true"));
	hidden_ = (config.value(std::string("Desktop Entry"), std::string("Hidden")) == std::string("true"));
}

std::string DesktopEntry::name() const
{
	return name_;
}

std::string DesktopEntry::icon() const
{
	return icon_;
}

std::string DesktopEntry::executable() const
{
	return executable_;
}

std::string DesktopEntry::identifier() const
{
	return identifier_;
}

std::string DesktopEntry::path() const
{
	return path_;
}

std::vector<std::string> DesktopEntry::types() const
{
	return types_;
}

bool DesktopEntry::noDisplay() const
{
	return noDisplay_;
}

bool DesktopEntry::hidden() const
{
	return hidden_;
}

}
