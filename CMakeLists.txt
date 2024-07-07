cmake_minimum_required(VERSION 3.28)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast")


set(SDL2_PATH "C:/Users/Aman's Laptop/Downloads/SDL2-devel-2.30.4-mingw/SDL2-2.30.4/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(RayTracing main.cpp
        CApp.cpp
        include/CApp.h
        include/qbImage.h
        qbImage.cpp
        scene.cpp
        include/scene.h
        ray.cpp
        include/ray.h
        camera.cpp
        include/camera.h
        object.cpp
        include/object.h
        objSphere.cpp
        include/objSphere.h
        light.cpp
        include/light.h
        pointLight.cpp
        include/pointLight.h
        gtfm.cpp
        include/gtfm.h)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})