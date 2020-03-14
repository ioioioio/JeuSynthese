# ProjetSynthese
This was my final project for my college degree in Computer Science (December 2017), completing my first sixteen months of programming experience. It has been written in four months, with very limited previous knowledge of C or C++ (or git). It is advised not to look at the code or the folder structure.

The project is a fully playable first person shooter (FPS). The player compete simple AIs on maps randomly generated.

My personal objectives was to use a limited set of libraries to acquire a deep understanding of how everything is done. I used GLFW to manage the window and handle the keyboard, GLAD to load OpenGL's functions, glm for the basic matrix and vector calculus, stb_image to load the textures, and FreeType to display the text. It has been highly influenced by [https://learnopengl.com/](https://learnopengl.com/).

Some shortcuts have been taken in order to deliver a fully playable FPS on time. For example there is no lightning, the maps are a bit square (I see it as a failure everytime someone compares it to Minecraft), and the AIs have a complete knowledge of the map. However, the physic engine does not depend on the squareness of the maps.

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

## Build
The code compiles as well on Linux with gcc and Windows with VisualStudio. C++11 is required. 

### Linux
Dependencies: dl, GL, glfw3, m, freetype, X11, Xcursor, Xi, Xinerama, Xrandr, Xxf86vm  
Headers: include

The dependencies must be installed independently.

These files and folders are useless on Linux and can be deleted: freetype271.dll, libs

A Code::Block project [is available](https://github.com/ioioioio/JeuSynthese/blob/master/JeuSyntheseLinux.cbp). This is probably the easiest way to build the project.

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

