cmake_minimum_required(VERSION 3.10)

project(EngineTest)

set (CMAKE_CXX_STANDARD 17)

set(ENGINE_PACKAGE_FILES "--preload-file ../assets --preload-file ../shaders")

set(ENGINE_BUILD_TOOL OFF)
add_subdirectory(subprojects/Engine)

add_executable(EngineTest tests/RenderTest.cpp)
target_link_libraries(EngineTest PUBLIC Engine)

# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
# SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
# SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")


if (EMSCRIPTEN)
    message("Building for Web (Emscripten/WebGL 2)")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENGINE_PACKAGE_FILES}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g4 -s USE_WEBGL2=1 -s USE_GLFW=3 -s DISABLE_EXCEPTION_CATCHING=0 -s ALLOW_MEMORY_GROWTH=1 -s LLD_REPORT_UNDEFINED")

    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined -lglfw")
endif()