cmake_minimum_required(VERSION 3.10)

project(JeuSynthese)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES
    src/affichage.cpp
    src/affichage.h
    src/ai.h
    src/glad.c
    src/ia.cpp
    src/ia.h
    src/item.cpp
    src/item.h
    src/jeu.cpp
    src/jeu.h
    src/lanceur.cpp
    src/lanceur.h
    src/main.cpp
    src/modele.cpp
    src/modele.h
    src/modeleitem.cpp
    src/modeleitem.h
    src/modelelanceur.cpp
    src/modelelanceur.h
    src/modeleprojectile.cpp
    src/modeleprojectile.h
    src/modelesphere.cpp
    src/modelesphere.h
    src/modelesurface.cpp
    src/modelesurface.h
    src/objetjeu.cpp
    src/objetjeu.h
    src/objetjeumobile.cpp
    src/objetjeumobile.h
    src/projectile.cpp
    src/projectile.h
    src/projectile1.cpp
    src/projectile1.h
    src/projectile2.cpp
    src/projectile2.h
    src/sphere.cpp
    src/sphere.h
    src/stb_image.cpp
    src/surface.cpp
    src/surface.h
    src/terrain.cpp
    src/terrain.h
    src/text_rendering.cpp
    src/text_rendering.h
)
add_executable(JeuSynthese ${SOURCES})

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(
        PRELOAD_PATHS 
        " \
        --preload-file ${CMAKE_SOURCE_DIR}/shaders@../shaders \
        --preload-file ${CMAKE_SOURCE_DIR}/textures@../textures \
        --preload-file ${CMAKE_SOURCE_DIR}/fonts@../fonts \
        "
    )
    set_target_properties(JeuSynthese PROPERTIES
        LINK_FLAGS "-s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_FREETYPE=1 ${PRELOAD_PATHS}"
    )
else()
    add_compile_options(-Wall)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

    target_link_libraries(JeuSynthese
        GL
        glfw
        Xi
        dl
        X11
        Xrandr
        Xcursor
        Xxf86vm
        m
        Xinerama
        freetype
        pthread
    )
endif()
