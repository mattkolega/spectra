cmake_minimum_required(VERSION 3.31)

project(
    Spectra
    VERSION 0.1.0
    DESCRIPTION "Image viewer"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(cmake/ProjectConfig.cmake)

include(FetchContent)
# Get SDL3 for multimedia functionality
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.12
    GIT_SHALLOW    TRUE
)

# Stop SDL from compiling tests
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3)

add_executable(spectra
    src/main.c
)

target_include_directories(spectra
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(spectra
    PRIVATE
        project_sanitizers
        project_warnings
        SDL3::SDL3
)
