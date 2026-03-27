cmake_minimum_required(VERSION 4.1.0)

project(
    Spectra
    VERSION 0.1.0
    DESCRIPTION "Image viewer"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For intellisense

include(FetchContent)
# Get SDL3 for multimedia functionality
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.2
)
# Get tinyfiledialogs for native dialogs
FetchContent_Declare(
    tinyfiledialogs
    GIT_REPOSITORY https://git.code.sf.net/p/tinyfiledialogs/code
    GIT_TAG master
    GIT_SHALLOW 1
)
FetchContent_MakeAvailable(SDL3 tinyfiledialogs)

# tinyfiledialogs needs to be compiled before it can be used
add_library(tinyfiledialogs_lib STATIC ${tinyfiledialogs_SOURCE_DIR}/tinyfiledialogs.c)
target_include_directories(tinyfiledialogs_lib INTERFACE ${tinyfiledialogs_SOURCE_DIR})

add_executable(spectra
    src/main.c
    src/app.c
    src/logger.c
)

target_link_libraries(spectra
    PRIVATE
        SDL3::SDL3
        tinyfiledialogs_lib
)