cmake_minimum_required(VERSION 3.10)
project(Tetris)

find_package(SDL2 REQUIRED)

set(SOURCE_FILES
    src/conf/basicconf.cpp
    src/util/sdlresource.cpp
    src/main.cpp
)

set(HEADER_FILES
    include/conf/basicconf.h
    include/util/sdlresource.h
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include/)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "C:/msys64/mingw64/bin/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)