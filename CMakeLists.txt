cmake_minimum_required(VERSION 3.20)
project(pong LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# raylib est téléchargé automatiquement à la configuration
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
if(EMSCRIPTEN)
    set(PLATFORM Web CACHE STRING "" FORCE)
endif()
FetchContent_Declare(raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(raylib)

add_executable(pong
        main.cpp
        Jouet.cpp Jouet.h
        Raquette.cpp Raquette.h
        Balle.cpp Balle.h
        Brique.cpp Brique.h
        Affichage.cpp Affichage.h
        Son.cpp Son.h
        Utilitaires/Configuration.cpp Utilitaires/Configuration.h)
target_link_libraries(pong PRIVATE raylib)

if(EMSCRIPTEN)
    # Version web : produit index.html + index.js + index.wasm + index.data
    set_target_properties(pong PROPERTIES OUTPUT_NAME index SUFFIX ".html")
    target_link_options(pong PRIVATE
            -sUSE_GLFW=3
            -sALLOW_MEMORY_GROWTH=1
            # le son de raylib (miniaudio) lit Module.HEAPF32
            -sEXPORTED_RUNTIME_METHODS=HEAPF32
            "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/assets@/assets"
            "SHELL:--shell-file ${CMAKE_SOURCE_DIR}/web/shell.html")
    set_property(TARGET pong APPEND PROPERTY LINK_DEPENDS ${CMAKE_SOURCE_DIR}/web/shell.html)
else()
    # Version ordinateur : copie les sons et la police à côté de l'exécutable
    add_custom_command(TARGET pong POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:pong>/assets)
endif()
