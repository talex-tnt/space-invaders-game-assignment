cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake")

include(utils)
get_folder_name(FOLDER_NAME)
project (${FOLDER_NAME} LANGUAGES CXX)

if(MSVC)
    LIST(APPEND SO_LIBRARIES
        winmm
    )
endif()

add_subdirectory(SpaceInvaders/code)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(TARGET  ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/app")

if(MSVC)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
endif()

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS " -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -lSDL -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"bmp\"]' -s SAFE_HEAP=1 -s ASSERTIONS=1 -s GL_ASSERTIONS=1 -s OFFSCREENCANVAS_SUPPORT=1 --preload-file ${CMAKE_SOURCE_DIR}/app@/ --use-preload-plugins -s GL_UNSAFE_OPTS=0")
# set_target_properties(Engine PROPERTIES LINK_FLAGS "-o dist/engine.js -s USE_FREETYPE=1 -s DISABLE_EXCEPTION_CATCHING=0 -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 --bind -s WASM=1 -O2 -s LEGACY_GL_EMULATION=0  -s GL_UNSAFE_OPTS=0 --pre-js pre-module.js --post-js post-module.js -s ASSERTIONS=1 -s GL_ASSERTIONS=1 -s INVOKE_RUN=0  -std=c++11 -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s OFFSCREENCANVAS_SUPPORT=1 --preload-file textures --preload-file shaders --preload-file fonts")

endif()
