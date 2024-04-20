#ifndef OBJETJEU_H
#define OBJETJEU_H

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <GLES3/gl3.h>
#else
    #include <glad/glad.h>
#endif
//#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>
#include <learnopengl/shader.h>

class ObjetJeu
{
public:
	ObjetJeu(glm::vec3 position, float demie_largeur, float demie_longueur, float lacet=0.0f, float tangage=0.0f, glm::vec3 vecteur_vitesse_imposee=glm::vec3(0.0f));
    ~ObjetJeu();

	virtual glm::mat4 donner_matrice_modele() const;

	virtual void subir_collision(glm::vec3 point_collision);

	// getters
	glm::vec3 donner_position();
	float donner_demie_largeur();

	float donner_lacet() {return this->lacet;};
	float donner_tangage() {return this->tangage;};

protected:
	glm::vec3 position;
	float demie_largeur;
	float demie_longueur;

	// Attributs d'orientation
	float lacet;
	float tangage;

	// Attributs d'orientation #2
	// Avoir deux fa�ons d'orienter l'objet est particuli�rement douteux.
	glm::vec3 axe_x_relatif;
	glm::vec3 axe_y_relatif;
	glm::vec3 axe_z_relatif;
	static const glm::vec3 axe_y_absolu;

	glm::vec3 vecteur_vitesse_imposee;

	void actualiser_axes_relatifs();

};

#endif
