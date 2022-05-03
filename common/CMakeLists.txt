find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

add_library(
	cg-common
	gl-context.cpp
	gl-single-window.cpp
	sdl-application.cpp
)
target_include_directories(
	cg-common SYSTEM
	INTERFACE ""
	PUBLIC
	${OPENGL_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
)
target_link_libraries(
	cg-common INTERFACE
	${OPENGL_LIBRARIES}
	${SDL2_LIBRARIES}
)
