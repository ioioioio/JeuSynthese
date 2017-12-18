#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "jeu.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp> //Pour test

void framebuffer_size_callback(GLFWwindow* fenetre, int largeur, int hauteur);

void key_callback(GLFWwindow* fenetre, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* fenetre, double pos_x, double pos_y);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);



Jeu* jeu; // Est déclaré en dehors du main pour que les fonctions de rappel y aient accès. Meilleure idée ?
int main()
{
	const unsigned int LARGEUR_FENETRE {800};
	const unsigned int HAUTEUR_FENETRE {600};
	//const unsigned int LARGEUR_FENETRE {1680};
	//const unsigned int HAUTEUR_FENETRE {1050};
	//const unsigned int LARGEUR_FENETRE {1920};
	//const unsigned int HAUTEUR_FENETRE {1080};

    //Initialisation de GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 32); // Pourquoi l'anti-aliasing fonctionne même lorsqu'il n'est pas activé ? (voir dans affichage)

	// création de la fenêtre
	// Plein écran
	//GLFWwindow* fenetre = glfwCreateWindow(LARGEUR_FENETRE, HAUTEUR_FENETRE, "Projet synthese", glfwGetPrimaryMonitor(), nullptr);
	// fenêtre
    GLFWwindow* fenetre = glfwCreateWindow(LARGEUR_FENETRE, HAUTEUR_FENETRE, "Projet synthese", NULL, NULL);
	// copié-collé de learnopengl.com
    if(fenetre == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(fenetre);
    glfwSetFramebufferSizeCallback(fenetre, framebuffer_size_callback);

	glfwSetKeyCallback(fenetre, key_callback);
    glfwSetCursorPosCallback(fenetre, mouse_callback);
	glfwSetMouseButtonCallback(fenetre, mouse_button_callback);

    glfwSetInputMode(fenetre, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialisation de GLAD
	// copié-collé de learnopengl.com
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	jeu = new Jeu(LARGEUR_FENETRE, HAUTEUR_FENETRE);
	jeu->commencer_partie(3);
    while (!glfwWindowShouldClose(fenetre))
    {
		jeu->actualiser(static_cast<float>(glfwGetTime()));
		jeu->afficher();

        glfwSwapBuffers(fenetre);
        glfwPollEvents();
    }

	delete jeu;
    return 0;
}

void key_callback(GLFWwindow* fenetre, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(fenetre, GL_TRUE);
	}
    if(key >= 0 && key < 1024) {
		if(action == GLFW_PRESS) {
			jeu->gerer_touches(key, GL_TRUE);
		}
		else if(action == GLFW_RELEASE) {
			jeu->gerer_touches(key, GL_FALSE);
		}
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// Penser à éliminer le copier-coller de key_callback
	if (button >= 0 && button < 1024) {
		if (action == GLFW_PRESS) {
			jeu->gerer_touches(button, GL_TRUE);
		}
		else if (action == GLFW_RELEASE) {
			jeu->gerer_touches(button, GL_FALSE);
		}
	}
}

void framebuffer_size_callback(GLFWwindow* fenetre, int largeur, int hauteur)
{
    glViewport(0, 0, largeur, hauteur);
}

void mouse_callback(GLFWwindow* fenetre, double pos_x, double pos_y)
{
	jeu->gerer_souris(pos_x, pos_y);
}
