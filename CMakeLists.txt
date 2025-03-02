cmake_minimum_required(VERSION 3.22)

project(editor)

message("Building with CMake version: ${CMAKE_VERSION}")
message("WASM: ${BUILD_WASM}")
message("Output type: ${OUTPUT_TYPE}")

include(${CMAKE_SOURCE_DIR}/cmake/utils.cmake)

###===================================================================================##

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")
list(APPEND CMAKE_PREFIX_PATH "/Users/stasangoliuk/Qt/6.8.2/macos")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

###===================================================================================##

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup(REQUIRES 6.8)

import(executable OFF)
import(compiler ON)
import(dependencies OFF)

###===================================================================================##

install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
qt_generate_deploy_app_script(
        TARGET ${PROJECT_NAME}
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
#import(cpack ON)
