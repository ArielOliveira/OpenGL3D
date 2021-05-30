cmake_minimum_required(VERSION 3.12)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "/Wall /wd4464 /sdl")
set(CMAKE_CXX_FLAGS_DEBUG "/Wall /wd4464 /sdl /fsanitizer=address")

set(INCLUDE_DIR "./include/")
set(SRC_DIR "./src/")
set(OUTPUT_DIR "./build/cmake/")

set(GLFW_INCLUDE "./lib/glfw/include/GLFW/")
set(GLEW_INCLUDE "./lib/glew/include/GL/")
set(GLM_INCLUDE "./lib/glm/include/glm/")
set(ASSIMP_INCLUDE "./lib/assimp/include/")

project(OpenGL3DEngine)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "./bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin/")


include_directories(
    ${GLFW_INCLUDE}
    ${GLEW_INCLUDE}
    ${GLM_INCLUDE}
    ${ASSIMP_INCLUDE}
    ${INCLUDE_DIR}
)
file(GLOB OpenGL3DEngine_SRC CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp" "${SRC_DIR}/*.cpp")

add_executable(OpenGL3DEngine ${OpenGL3DEngine_SRC})

add_definitions(-DGLEW_STATIC)

find_library(GLFW glfw3.lib "./lib/glfw/lib-vc2019/")
find_package(OpenGL REQUIRED)
find_library(GLEW glew32s.lib "./lib/glew/lib/")
find_library(ASSIMP assimp-vc142-mt.lib "./lib/assimp/lib/")

target_link_libraries(OpenGL3DEngine ${GLEW} ${GLFW} OpenGL::GL ${ASSIMP})