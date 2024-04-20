#include "projectile2.h"

const int Projectile2::cout {3};
const float Projectile2::delai {0.6f};
const float Projectile2::norme_vitesse {13.0f};
const int Projectile2::la_force {20};

Projectile2::Projectile2(glm::vec3 position, glm::vec3 axe_x_relatif, glm::vec3 axe_y_relatif, glm::vec3 axe_z_relatif, unsigned int id_lanceur)
	: Projectile(position,axe_x_relatif, axe_y_relatif, axe_z_relatif, axe_z_relatif*Projectile2::norme_vitesse, id_lanceur),
	  temps(0)
{
	this->force = Projectile2::la_force;
};
Projectile2::~Projectile2()
{
};
