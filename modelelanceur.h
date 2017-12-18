#ifndef MODELELANCEUR_H
#define MODELELANCEUR_H

#include "modelesphere.h"

class ModeleLanceur : public ModeleSphere
{
public:
	ModeleLanceur();
	~ModeleLanceur();

	void dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, glm::vec4 filtre);
};

#endif
