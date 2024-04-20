# ProjetSynthese
This was my final project for my associate degree in Computer Science (December 2017), marking the completion of my first sixteen months of programming experience. It was written over four months with very limited prior knowledge of C or C++ (or Git).

The project is a fully playable first-person shooter (FPS) where the player competes against simple bots on randomly generated maps.

My personal objective was to use a limited set of libraries to gain a deep understanding of how everything works. I used [GLFW](êhttps://www.glfw.org/) to manage the window and handle the keyboard, [GLAD](https://glad.dav1d.de/) to load OpenGL's functions, [GLM](https://glm.g-truc.net/0.9.9/index.html) for basic matrix and vector calculus, [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) to load the textures, and [FreeType](https://freetype.org/) to display text. This project was heavily influenced by [https://learnopengl.com/](https://learnopengl.com/).

Some shortcuts were taken to deliver a fully playable FPS on time. For example, there is no lighting, the maps are a bit square, and the bots have complete knowledge of the map. However, the physics engine does not depend on the squareness of the maps.

I am not the author of the textures. The credits can be found in [source.txt](https://github.com/ioioioio/JeuSynthese/blob/master/textures/sources.txt).

## Images
[![image1](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/thumbnails/image1.png)](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/source/image1.png)
[![image2](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/thumbnails/image2.png)](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/source/image2.png)
[![image3](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/thumbnails/image3.png)](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/source/image3.png)
[![image4](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/thumbnails/image4.png)](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/source/image4.png)
[![image5](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/thumbnails/image5.png)](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/source/image5.png)
[![image6](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/thumbnails/image6.png)](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/source/image6.png)

## Video
[![video](https://raw.githubusercontent.com/ioioioio/JeuSynthese/master/images/source/video_preview.png)](https://drive.google.com/open?id=1K2qOEwOy1DAEULGPxS6SaIC325uOlYIq)

## Building and running

### WebAssembly
#### Dependencies
[Emscripten](https://emscripten.org/) has to be installed

#### Build
``` shell
mkdir build
cd build
emcmake cmake ..
emmake make
```

#### Launch
1. Serve the build folder
ex: `python -m http.server`
2. Open `build/JeuSynthese.html` with a browser

### Linux

#### Dependencies

The following dependencies are required: dl, GL, glfw3, m, freetype, X11, Xcursor, Xi, Xinerama, Xrandr, Xxf86vm 

On Ubuntu:
``` shell
sudo apt-get install libgl1-mesa-dev libglfw3 libglfw3-dev libfreetype6-dev libx11-dev libxcursor-dev libxi-dev libxinerama-dev libxrandr-dev libxxf86vm-dev
```

#### Build
``` shell
mkdir build
cd build
cmake ..
make
```

#### Launch
The game has to be launched from the root folder
``` shell
./build/JeuSynthese
```

### Windows
Dependencies: glfw3, opengl32, freetype271  
Libraries: libs  
Headers: include

The dll for freetype is included in [libs](https://github.com/ioioioio/JeuSynthese/tree/master/libs).

The dll for glfw3.dll can be downloaded on [http://www.glfw.org/](http://www.glfw.org/). There is already one included for VisualStudio 2015 64 bit in [libs](https://github.com/ioioioio/JeuSynthese/tree/master/libs). 

### Full screen
Open [main.cpp](https://github.com/ioioioio/JeuSynthese/blob/master/main.cpp)  
Set the variable LARGEUR_FENETRE to the exact value of the width of the screen  
Set the variable HAUTEUR_FENETRE to the exact value of the height of the screen  
Uncomment that line:  
    GLFWwindow* fenetre = glfwCreateWindow(LARGEUR_FENETRE, HAUTEUR_FENETRE, "Projet synthese", glfwGetPrimaryMonitor(), nullptr);  
Comment that line:  
    GLFWwindow* fenetre = glfwCreateWindow(LARGEUR_FENETRE, HAUTEUR_FENETRE, "Projet synthese", NULL, NULL);

