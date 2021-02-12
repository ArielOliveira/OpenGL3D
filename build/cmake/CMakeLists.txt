cmake_minimum_required(VERSION 3.12)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++20")

set(ROOT "../..")

set(INCLUDE_DIR "${ROOT}/include/")
set(SRC_DIR "${ROOT}/src/")

set(GLFW_INCLUDE "${ROOT}/lib/glfw/include/GLFW/")
set(GLEW_INCLUDE "${ROOT}/lib/glew/include/GL/")
set(GLM_INCLUDE "${ROOT}/lib/glm/include/glm/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/lib/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ROOT}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ROOT}/bin/")

project(OpenGL3DEngine)

include_directories(
    ${GLFW_INCLUDE}
    ${GLEW_INCLUDE}
    ${GLM_INCLUDE}
    ${INCLUDE_DIR}
)
file(GLOB OpenGL3DEngine_SRC CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp" "${SRC_DIR}/*.cpp")

add_executable(OpenGL3DEngine ${OpenGL3DEngine_SRC})

add_definitions(-DGLEW_STATIC)

find_library(GLFW glfw3.lib "${ROOT}/lib/glfw/lib-vc2019/")
find_package(OpenGL REQUIRED)
find_library(GLEW glew32s.lib "${ROOT}/lib/glew/lib/")

target_link_libraries(OpenGL3DEngine ${GLEW} ${GLFW} OpenGL::GL)