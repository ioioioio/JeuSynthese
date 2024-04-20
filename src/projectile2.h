#ifndef PROJECTILE2_H
#define PROJECTILE2_H

#include "projectile.h"
#include <math.h>

class Projectile2 : public Projectile
{
public:
	Projectile2(glm::vec3 position, glm::vec3 axe_x_relatif, glm::vec3 axe_y_relatif, glm::vec3 axe_z_relatif, unsigned int id_lanceur);
	~Projectile2();

	static const int cout;
	static const float delai;
	static const int la_force;
	static const float norme_vitesse;

private:
	float temps;
};

#endif
