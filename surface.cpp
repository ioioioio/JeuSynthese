#include "surface.h"

#include <glm/gtx/string_cast.hpp> //Pour test

Surface::Surface(glm::vec3 position, float demie_largeur, float demie_hauteur, float lacet, float tangage, int type)
	: ObjetJeu(position, demie_largeur, demie_hauteur, lacet, tangage),
	  type(type)
{
	this->actualiser_axes_relatifs();
}

glm::vec3 Surface::donner_normale() const
{
	return glm::normalize(this->axe_z_relatif);
}

std::vector<glm::vec3> Surface::donner_sommets()
{
	std::vector<glm::vec3> sommets;

	glm::vec3 vecteur_demie_largeur = this->demie_largeur*this->axe_x_relatif;
	glm::vec3 vecteur_demie_hauteur = this->demie_longueur*this->axe_y_relatif;

	glm::vec3 sommet1 = this->position+vecteur_demie_largeur+vecteur_demie_hauteur;
	glm::vec3 sommet2 = this->position+vecteur_demie_largeur-vecteur_demie_hauteur;
	glm::vec3 sommet3 = this->position-vecteur_demie_largeur-vecteur_demie_hauteur;
	glm::vec3 sommet4 = this->position-vecteur_demie_largeur+vecteur_demie_hauteur;

	sommets.push_back(sommet1);
	sommets.push_back(sommet2);
	sommets.push_back(sommet3);
	sommets.push_back(sommet4);

	return sommets;
}

void Surface::subir_collision(glm::vec3 point_collision)
{
}