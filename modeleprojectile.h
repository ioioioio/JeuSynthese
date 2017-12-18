#ifndef MODELEPROJECTILE_H
#define MODELEPROJECTILE_H

#include "modelesphere.h"

class ModeleProjectile : public ModeleSphere
{
public:
	ModeleProjectile();
	~ModeleProjectile();

	void dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, glm::vec4 filtre);
};

#endif
