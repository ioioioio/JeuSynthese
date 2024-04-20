cmake_minimum_required(VERSION 3.10)

project(JeuSynthese)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES
    affichage.cpp
    affichage.h
    ai.h
    glad.c
    ia.cpp
    ia.h
    item.cpp
    item.h
    jeu.cpp
    jeu.h
    lanceur.cpp
    lanceur.h
    main.cpp
    modele.cpp
    modele.h
    modeleitem.cpp
    modeleitem.h
    modelelanceur.cpp
    modelelanceur.h
    modeleprojectile.cpp
    modeleprojectile.h
    modelesphere.cpp
    modelesphere.h
    modelesurface.cpp
    modelesurface.h
    objetjeu.cpp
    objetjeu.h
    objetjeumobile.cpp
    objetjeumobile.h
    projectile.cpp
    projectile.h
    projectile1.cpp
    projectile1.h
    projectile2.cpp
    projectile2.h
    sphere.cpp
    sphere.h
    stb_image.cpp
    surface.cpp
    surface.h
    terrain.cpp
    terrain.h
    text_rendering.cpp
    text_rendering.h
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
