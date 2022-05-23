find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE SDL2_image REQUIRED)

add_library(
	cg-common
	gl-context.cpp
	gl-single-window.cpp
	gl-texture.cpp
	sdl-application.cpp
)
set_target_properties(
	cg-common
	PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	cg-common SYSTEM
	INTERFACE ""
	PUBLIC
	${OPENGL_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	PRIVATE
	${SDL2_IMAGE_INCLUDE_DIRS}
)
target_link_libraries(
	cg-common INTERFACE
	${OPENGL_LIBRARIES}
	${SDL2_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
)
