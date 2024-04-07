cmake_minimum_required(VERSION 3.10)

project(JeuSynthese)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

include_directories(include)

add_executable(JeuSynthese
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
