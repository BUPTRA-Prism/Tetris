cmake_minimum_required(VERSION 3.10)
project(Tetris)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(SOURCE_FILES
    src/conf/basicconf.cpp
    src/conf/resourceconf.cpp
    src/manager/resourcemanager.cpp
    src/util/sdlresource.cpp
    src/main.cpp
)

set(HEADER_FILES
    include/conf/basicconf.h
    include/conf/resourceconf.h
    include/manager/resourcemanager.h
    include/util/sdlresource.h
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include/)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "C:/msys64/mingw64/bin/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy
        "C:/msys64/mingw64/bin/SDL2_mixer.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy
        "C:/msys64/mingw64/bin/libvorbisfile-3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy
        "C:/msys64/mingw64/bin/libogg-0.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy
        "C:/msys64/mingw64/bin/libvorbis-0.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)