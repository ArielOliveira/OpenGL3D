# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.19
cmake_policy(SET CMP0009 NEW)

# OpenGL3DEngine_SRC at CMakeLists.txt:33 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "E:/OpenGL3D/./include//*.h")
set(OLD_GLOB
  "E:/OpenGL3D/./include//config.h"
  "E:/OpenGL3D/./include//stb_image.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "E:/OpenGL3D/build/cmake/CMakeFiles/cmake.verify_globs")
endif()

# OpenGL3DEngine_SRC at CMakeLists.txt:33 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "E:/OpenGL3D/./include//*.hpp")
set(OLD_GLOB
  "E:/OpenGL3D/./include//AssetManager.hpp"
  "E:/OpenGL3D/./include//Camera.hpp"
  "E:/OpenGL3D/./include//Component.hpp"
  "E:/OpenGL3D/./include//Cube.hpp"
  "E:/OpenGL3D/./include//DirectionalLight.hpp"
  "E:/OpenGL3D/./include//Entity.hpp"
  "E:/OpenGL3D/./include//GLRender.hpp"
  "E:/OpenGL3D/./include//GLSLShader.hpp"
  "E:/OpenGL3D/./include//GLTexture.hpp"
  "E:/OpenGL3D/./include//Input.hpp"
  "E:/OpenGL3D/./include//Light.hpp"
  "E:/OpenGL3D/./include//Material.hpp"
  "E:/OpenGL3D/./include//Math.hpp"
  "E:/OpenGL3D/./include//Mesh.hpp"
  "E:/OpenGL3D/./include//Model.hpp"
  "E:/OpenGL3D/./include//Object.hpp"
  "E:/OpenGL3D/./include//OpenGLDebugger.hpp"
  "E:/OpenGL3D/./include//Plane.hpp"
  "E:/OpenGL3D/./include//PointLight.hpp"
  "E:/OpenGL3D/./include//SpotLight.hpp"
  "E:/OpenGL3D/./include//State.hpp"
  "E:/OpenGL3D/./include//World.hpp"
  "E:/OpenGL3D/./include//fileLoader.hpp"
  "E:/OpenGL3D/./include//pugiconfig.hpp"
  "E:/OpenGL3D/./include//pugixml.hpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "E:/OpenGL3D/build/cmake/CMakeFiles/cmake.verify_globs")
endif()

# OpenGL3DEngine_SRC at CMakeLists.txt:33 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "E:/OpenGL3D/./src//*.cpp")
set(OLD_GLOB
  "E:/OpenGL3D/./src//AssetManager.cpp"
  "E:/OpenGL3D/./src//Camera.cpp"
  "E:/OpenGL3D/./src//Cube.cpp"
  "E:/OpenGL3D/./src//DirectionalLight.cpp"
  "E:/OpenGL3D/./src//Entity.cpp"
  "E:/OpenGL3D/./src//GLRender.cpp"
  "E:/OpenGL3D/./src//GLSLShader.cpp"
  "E:/OpenGL3D/./src//GLTexture.cpp"
  "E:/OpenGL3D/./src//Input.cpp"
  "E:/OpenGL3D/./src//Light.cpp"
  "E:/OpenGL3D/./src//Material.cpp"
  "E:/OpenGL3D/./src//Mesh.cpp"
  "E:/OpenGL3D/./src//Model.cpp"
  "E:/OpenGL3D/./src//Object.cpp"
  "E:/OpenGL3D/./src//Plane.cpp"
  "E:/OpenGL3D/./src//PointLight.cpp"
  "E:/OpenGL3D/./src//SpotLight.cpp"
  "E:/OpenGL3D/./src//State.cpp"
  "E:/OpenGL3D/./src//World.cpp"
  "E:/OpenGL3D/./src//main.cpp"
  "E:/OpenGL3D/./src//pugixml.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "E:/OpenGL3D/build/cmake/CMakeFiles/cmake.verify_globs")
endif()
