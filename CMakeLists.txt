cmake_minimum_required(VERSION 3.28)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

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
        objects/object.cpp
        include/object.h
        objects/objSphere.cpp
        include/objSphere.h
        lights/light.cpp
        include/light.h
        lights/pointLight.cpp
        include/pointLight.h
        gtfm.cpp
        include/gtfm.h
        objects/objectPlane.cpp
        include/objectPlane.h
        materials/material.cpp
        include/material.h
        materials/simpleMaterial.cpp
        include/simpleMaterial.h
        objects/objectCylinder.cpp
        include/objectCylinder.h
        objects/objCone.cpp
        include/objCone.h
        textures/texture.cpp
        include/texture.h
        textures/flatText.cpp
        include/flatText.h
        textures/checkerText.cpp
        include/checkerText.h
        textures/imgText.cpp
        include/imgText.h
        materials/simpleRefractive.cpp
        include/simpleRefractive.h
        objects/objCube.cpp
        include/objCube.h
        raymarch/distFunc.cpp
        include/distFunc.h
        raymarch/rayMarchBase.cpp
        include/rayMarchBase.h
        raymarch/marchSphere.cpp
        include/marchSphere.h
        raymarch/marchTorus.cpp
        include/marchTorus.h
        textures/colormap.cpp
        include/colormap.h
        textures/gradient.cpp
        include/gradient.h)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})