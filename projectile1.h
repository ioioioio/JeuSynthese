#ifndef PROJECTILE1_H
#define PROJECTILE1_H

#include "projectile.h"

class Projectile1 : public Projectile
{
public:
	Projectile1(glm::vec3 position, glm::vec3 axe_x_relatif, glm::vec3 axe_y_relatif, glm::vec3 axe_z_relatif, unsigned int id_lanceur);
	~Projectile1();

	static const int cout;
	static const float delai;
	static const int la_force;
	static const float norme_vitesse;
};

#endif
