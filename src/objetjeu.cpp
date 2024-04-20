#include "objetjeu.h"

#include <glm/gtx/string_cast.hpp> //Pour test
#include <iostream>

const glm::vec3 ObjetJeu::axe_y_absolu(0.0f, 1.0f, 0.0f);

ObjetJeu::ObjetJeu(glm::vec3 position, float demie_largeur, float demie_longueur, float lacet, float tangage, glm::vec3 vecteur_vitesse_imposee)
	: position(position), demie_largeur(demie_largeur), demie_longueur(demie_longueur), lacet(lacet), tangage(tangage), vecteur_vitesse_imposee(vecteur_vitesse_imposee)
{
}

ObjetJeu::~ObjetJeu()
{
}


glm::mat4 ObjetJeu::donner_matrice_modele() const
{
	glm::mat4 matrice_modele;
	matrice_modele = glm::translate(matrice_modele, this->position);

    matrice_modele = glm::rotate(matrice_modele, glm::radians(this->tangage), glm::vec3(1.0f, 0.0f, 0.0f));
	matrice_modele = glm::rotate(matrice_modele, glm::radians(this->lacet), glm::vec3(0.0f, 1.0f, 0.0f));

	matrice_modele = glm::scale(matrice_modele, glm::vec3(this->demie_largeur, this->demie_longueur, this->demie_largeur)); // le dernier paramètre du vecteur ne fait pas de sens.

	return matrice_modele;
}

void ObjetJeu::actualiser_axes_relatifs()
{
	glm::vec3 nouvel_axe_z_relatif;
	nouvel_axe_z_relatif.x = cos(glm::radians(this->lacet+90))*cos(glm::radians(this->tangage));
	nouvel_axe_z_relatif.y = sin(glm::radians(this->tangage));
	nouvel_axe_z_relatif.z = -sin(glm::radians(this->lacet+90))*cos(glm::radians(this->tangage));
	this->axe_z_relatif = glm::normalize(nouvel_axe_z_relatif);
	this->axe_x_relatif = glm::normalize(glm::cross(this->axe_z_relatif, this->axe_y_absolu));
	this->axe_y_relatif = glm::normalize(glm::cross(this->axe_x_relatif, this->axe_z_relatif));
}

void ObjetJeu::subir_collision(glm::vec3 point_collision)
{

}

glm::vec3 ObjetJeu::donner_position()
{
	return this->position;
}

float ObjetJeu::donner_demie_largeur()
{
	return this->demie_largeur;
}