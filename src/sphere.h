#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <list>

#include "objetjeu.h"
#include "surface.h"

struct InfosCollisionSurface {
	bool collision;
	glm::vec3 normale_surface;
	float distance;
};

class Sphere : public ObjetJeu {
public:
	Sphere(glm::vec3 position, float rayon, glm::vec3 vecteur_vitesse_imposee);
	~Sphere();

	float donner_rayon();

protected:
	bool verifier_collision_sphere(Sphere& sphere);
	void subir_collision_sphere(glm::vec3 position_autre_sphere, float rayon_autre_sphere);
	InfosCollisionSurface verifier_collision_surface(Surface& surface);
	void subir_collision_surface(InfosCollisionSurface infos_collision);
};

#endif
