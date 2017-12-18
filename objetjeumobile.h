#ifndef OBJETJEUMOBILE_H
#define OBJETJEUMOBILE_H

#include "objetjeu.h"

class ObjetJeuMobile : public ObjetJeu {
public:
	ObjetJeuMobile(glm::vec3 position, float demie_largeur, float demie_longueur, glm::vec3 vecteur_vitesse_imposee);
	~ObjetJeuMobile();
	void se_deplacer(const GLfloat& delta_temps);

protected:
	// Attibuts de positionnement
	glm::vec3 axe_x_relatif;
	glm::vec3 axe_y_relatif;
	glm::vec3 axe_z_relatif;
	glm::vec3 axe_y_absolu;

	// Attributs de vitesse
	glm::vec3 vecteur_vitesse_imposee;

	void actualiser_axes_relatifs();
};

#endif
