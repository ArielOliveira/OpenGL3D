cmake_minimum_required(VERSION 3.12)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++20")

set(INCLUDE_DIR "./include/")
set(SRC_DIR "./src/")

set(GLFW_INCLUDE "./libs/glfw/include/GLFW/")
set(GLEW_INCLUDE "./libs/glew/include/GL/")
set(GLM_INCLUDE "./libs/glm/include/glm/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./lib/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)

#set(CMAKE_PREFIX_PATH "./libs/glew/")
#set(CMAKE_LIBRARY_PATH "./libs/glew/lib/")



project(OpenGL3DEngine)

include_directories(
    ${GLFW_INCLUDE}
    ${GLEW_INCLUDE}
    ${GLM_INCLUDE}
    ${INCLUDE_DIR}
)
file(GLOB OpenGL3DEngine_SRC CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.h" "${SRC_DIR}/*.cpp")

add_executable(OpenGL3DEngine ${OpenGL3DEngine_SRC})

add_definitions(-DGLEW_STATIC)

#find_library(GLFW glfw3.lib ./libs/glfw/lib-vc2019/)
#find_library(GLEWS glew32s.lib ./libs/glew/lib/)

#target_link_libraries(OpenGL3DEngine PUBLIC OpenGL32 ${GLEW} ${GLFW})

find_library(GLFW glfw3.lib ./libs/glfw/lib-vc2019/)
target_link_libraries(OpenGL3DEngine ${GLFW})

find_package(OpenGL REQUIRED)
target_link_libraries(OpenGL3DEngine OpenGL::GL)

find_library(GLEW glew32s.lib ./libs/glew/lib/)
target_link_libraries(OpenGL3DEngine ${GLEW})



