cmake_minimum_required(VERSION 3.11)
project(1.Bezier VERSION 0.0 LANGUAGES CXX)

add_subdirectory(../../common ../../common)

add_executable(
	Bezier
	main.cpp
	bezier-window.cpp
	cubic-bezier.cpp
	vertex-controller.cpp
)
target_link_libraries(Bezier cg-common)
