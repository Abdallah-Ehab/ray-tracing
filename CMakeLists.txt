cmake_minimum_required(VERSION 3.10)

# Name of your raytracing project
project(RayTracer VERSION 1.0)

# Use C++17 or C++20 since raytracers benefit from modern features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake to compile main.cpp into an executable called "raytracer"
# (Change main.cpp to match whatever your main file is named!)
add_executable(app main.cpp)
