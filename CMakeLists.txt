cmake_minimum_required(VERSION 3.10)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(SOURCE_FILES
    src/animation/animation.cpp
    src/animation/blinkanimation.cpp
    src/core/context.cpp
    src/core/logic.cpp
    src/core/settings.cpp
    src/manager/audiomanager.cpp
    src/manager/inputmanager.cpp
    src/manager/resourcemanager.cpp
    src/scene/scene.cpp
    src/scene/titlescene.cpp
    src/scene/menuscene.cpp
    src/scene/settingscene.cpp
    src/scene/gamescene.cpp
    src/scene/countscene.cpp
    src/scene/scenemanager.cpp
    src/ui/layout.cpp
    src/ui/optionicon.cpp
    src/ui/text.cpp
    src/util/sdlresource.cpp
    src/util/util.cpp
    src/main.cpp
)

set(HEADER_FILES
    include/animation/animation.h
    include/animation/blinkanimation.h
    include/conf/basicconf.h
    include/conf/keyconf.h
    include/conf/resourceconf.h
    include/conf/sceneconf.h
    include/conf/settingconf.h
    include/core/context.h
    include/core/logic.h
    include/core/settings.h
    include/manager/audiomanager.h
    include/manager/inputmanager.h
    include/manager/resourcemanager.h
    include/scene/scene.h
    include/scene/titlescene.h
    include/scene/menuscene.h
    include/scene/settingscene.h
    include/scene/gamescene.h
    include/scene/countscene.h
    include/scene/scenemanager.h
    include/ui/layout.h
    include/ui/optionicon.h
    include/ui/text.h
    include/util/sdlresource.h
    include/util/util.h
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