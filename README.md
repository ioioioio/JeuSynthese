**Compiler**
==========

## Sur Linux
Dépendances :
- dl
- GL
- m
- freetype
- X11
- Xcursor
- Xi
- Xinerama
- Xrandr
- Xxf86vm

Répertoire de headers :
- include

Les fichiers et dossiers suivants sont inutiles sur Linux et peuvent être supprimés en toute sécurité :
- freetype271.dll
- libs

## Sur Windows
Dépendances :
- glfw3
- opengl32
- freetype271

Répertoire de bibliothèques (pour les dépendances) :
- libs

Répertoire de headers :
- include

Important :
Il est nécessaire de s'assurer d'avoir le glfw3.dll correspondant à sa machine et son compilateur. Le dll fourni est celui pour VisualStudio 2015 64 bits.
Il est possible de le télécharger ici : http://www.glfw.org/

Plein écran
=========
Pour mettre le jeu en plein écran 

Ouvrir main.cpp

variable LARGEUR_FENETRE : valeur exacte de la largeur de l'écran.  
variable HAUTEUR_FENETRE : valeur exacte de la hauteur de l'écran.

Décommenter la ligne suivante :

    GLFWwindow* fenetre = glfwCreateWindow(LARGEUR_FENETRE, HAUTEUR_FENETRE, "Projet synthese", glfwGetPrimaryMonitor(), nullptr);

Commenter la ligne suivante :

    GLFWwindow* fenetre = glfwCreateWindow(LARGEUR_FENETRE, HAUTEUR_FENETRE, "Projet synthese", NULL, NULL);
