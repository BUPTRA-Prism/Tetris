set(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 3.21)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MSYS2_PREFIX "C:/msys64/mingw64")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

file(GLOB SOURCE_FILES 
    "src/*.cpp"
    "src/*/*.cpp"
    "src/*/*/*.cpp"
)

file(GLOB HEADER_FILES 
    "include/*.h"
    "include/*/*.h"
    "include/*/*/*.h"
)

# add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/resource/icon.rc)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-subsystem,windows")

target_include_directories(${PROJECT_NAME} PRIVATE include/)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
)

install(TARGETS ${PROJECT_NAME} 
    RUNTIME_DEPENDENCY_SET game_deps
    DESTINATION .
)

install(RUNTIME_DEPENDENCY_SET game_deps
    DIRECTORIES 
        "${MSYS2_PREFIX}/bin"
    PRE_EXCLUDE_REGEXES ".*system32.*" "api-ms-" "KERNEL32" "USER32" "GDI32" "ADVAPI32"
    POST_EXCLUDE_REGEXES ".*system32.*" "api-ms-" "KERNEL32" "USER32" "GDI32" "ADVAPI32"
    DESTINATION .
)

install(DIRECTORY resource DESTINATION .)