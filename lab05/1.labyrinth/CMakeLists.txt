cmake_minimum_required(VERSION 3.11)
project(1.labyrinth VERSION 0.0 LANGUAGES CXX)

add_subdirectory(../../common ../../common)

add_executable(
	labyrinth
	main.cpp
	labyrinth-window.cpp
	load-default.cpp
	player-controller.cpp
	render-data.cpp
	world.cpp
)
set_target_properties(
	labyrinth
	PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_link_libraries(labyrinth cg-common)
