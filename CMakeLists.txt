# Initial CMake configuration
cmake_minimum_required(VERSION 3.10)
project(Tank98 LANGUAGES CXX)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the executable
add_executable(Tank98 main.cpp math.cpp)

# Link against the SDL2 library
target_link_libraries(Tank98 SDL2::SDL2)
