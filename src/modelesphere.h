#ifndef MODELESPHERE_H
#define MODELESPHERE_H

#include "modele.h"

class ModeleSphere : public Modele
{
public:
    ModeleSphere();
    ~ModeleSphere();
    void initialier_buffer();
	void dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, int type=0);
};

#endif
