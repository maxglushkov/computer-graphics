cmake_minimum_required(VERSION 3.11)
project(2.ICE VERSION 0.0 LANGUAGES CXX)

add_subdirectory(../../common ../../common)

add_executable(
	ICE
	main.cpp
	ice-window.cpp
	ice.cpp
)
target_link_libraries(ICE cg-common)
