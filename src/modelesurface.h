#ifndef MODELESURFACE_H
#define MODELESURFACE_H

#include "modele.h"
#include "surface.h" // pour SurfaceType. Dépendance nécessaire ?

class ModeleSurface : public Modele
{
public:
	ModeleSurface();
	~ModeleSurface();

	virtual void initialier_buffer();

	void dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, int type);

private:
	static const float sommets[];
	static const int taille_sommets;
	static const int indices[];
	static const int taille_indices;
};

#endif