#include "objetjeumobile.h"

ObjetJeuMobile::ObjetJeuMobile(glm::vec3 position, float demie_largeur, float demie_longueur, glm::vec3 vecteur_vitesse_imposee)
    : ObjetJeu(position, demie_largeur, demie_longueur),
	  axe_y_absolu(glm::vec3(0.0f, 1.0f, 0.0f)),
	  vecteur_vitesse_imposee(vecteur_vitesse_imposee)
 {
 }

ObjetJeuMobile::~ObjetJeuMobile()
{
}

void ObjetJeuMobile::se_deplacer(const GLfloat& delta_temps)
{
	this->position += vecteur_vitesse_imposee*delta_temps;
}

void ObjetJeuMobile::actualiser_axes_relatifs()
{
	glm::vec3 nouvel_axe_z_relatif;
	nouvel_axe_z_relatif.x = cos(glm::radians(this->lacet))*cos(glm::radians(this->tangage));
	nouvel_axe_z_relatif.y = sin(glm::radians(this->tangage));
	nouvel_axe_z_relatif.z = sin(glm::radians(this->lacet))*cos(glm::radians(this->tangage));
	this->axe_z_relatif = glm::normalize(nouvel_axe_z_relatif);
	this->axe_x_relatif = glm::normalize(glm::cross(this->axe_z_relatif, this->axe_y_absolu));
	this->axe_y_relatif = glm::normalize(glm::cross(this->axe_x_relatif, this->axe_z_relatif));
}
