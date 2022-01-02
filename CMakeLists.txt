cmake_minimum_required(VERSION 3.0.0)
project(OpenGLApp)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(NOT EMSCRIPTEN)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
endif()

set(SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/Application.cpp
    ${CMAKE_SOURCE_DIR}/src/IndexBuffer.cpp
    ${CMAKE_SOURCE_DIR}/src/Renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/Texture.cpp
    ${CMAKE_SOURCE_DIR}/src/VertexArray.cpp
    ${CMAKE_SOURCE_DIR}/src/VertexBuffer.cpp
    ${CMAKE_SOURCE_DIR}/src/VertexBufferLayout.cpp
    ${CMAKE_SOURCE_DIR}/src/Game.cpp)

add_executable(App ${SRC_FILES})

if(EMSCRIPTEN)
    set(SUFFIX ".html")
    set(LIB_OPENGL GL GLEW glfw)
else()
    set(SUFFIX ".out")
    set(LIB_OPENGL OpenGL::GL GLEW::GLEW glfw)
endif()

set_target_properties(App PROPERTIES SUFFIX ${SUFFIX} CXX_STANDARD 11)

target_include_directories(App PUBLIC ${CMAKE_SOURCE_DIR}/include
                                        ${CMAKE_SOURCE_DIR}/include/vendor)

target_link_libraries(App PUBLIC ${LIB_OPENGL})

if(EMSCRIPTEN)
target_compile_options(App PUBLIC -g)
target_link_options(
    App
  PUBLIC
  -g
  -sUSE_GLFW=3
  -sGL_ASSERTIONS=1
  -sGL_DEBUG=1
  --preload-file
  ../assets
  -sMAX_WEBGL_VERSION=3
  -sMIN_WEBGL_VERSION=3
  -sFULL_ES3=1)
endif()
