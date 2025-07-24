# Project name
project(tiny_ecs)
cmake_minimum_required(VERSION 3.12)

# Set C++ standard (if it's a C++ project)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
		"src/*.cpp"
		"src/*.h")
# Add executable
find_package(TBB REQUIRED)
add_executable(${PROJECT_NAME}  ${SOURCES})
target_link_libraries(${PROJECT_NAME} TBB::tbb)
