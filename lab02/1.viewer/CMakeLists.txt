cmake_minimum_required(VERSION 3.9.2)
project(1.viewer VERSION 0.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 gtk4)

find_program(GLIB_COMPILE_RESOURCES glib-compile-resources REQUIRED)
add_custom_command(
	OUTPUT viewer.gresource.c
	COMMAND ${GLIB_COMPILE_RESOURCES} ARGS
		viewer.gresource.xml
		--target=${CMAKE_CURRENT_BINARY_DIR}/viewer.gresource.c
		--generate-source
	MAIN_DEPENDENCY viewer.gresource.xml
	DEPENDS viewer-menu.ui
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(
	viewer
	main.cpp
	viewer-application.cpp
	viewer-window.cpp
	viewer.gresource.c
)
target_include_directories(viewer SYSTEM PRIVATE ${GTK4_INCLUDE_DIRS})
target_link_libraries(viewer ${GTK4_LIBRARIES})
