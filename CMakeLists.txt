cmake_minimum_required(VERSION 2.6)

project(mimeapps)

set(mimeapps_VERSION_MAJOR 0)
set(mimeapps_VERSION_MINOR 3)

add_library(mimeapps
	ConfigReader.cpp
	DesktopEntry.cpp
	Index.cpp
	Tools.cpp
)

add_executable(test
	main.cpp
)

target_link_libraries (test mimeapps)

set_property(TARGET test PROPERTY CXX_STANDARD 11)
