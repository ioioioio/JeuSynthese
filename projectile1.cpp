#include "projectile1.h"

const int Projectile1::cout {1};
const float Projectile1::delai {0.1f};
const int Projectile1::la_force {10};
const float Projectile1::norme_vitesse {10.0f};

Projectile1::Projectile1(glm::vec3 position, glm::vec3 axe_x_relatif, glm::vec3 axe_y_relatif, glm::vec3 axe_z_relatif, unsigned int id_lanceur)
	: Projectile(position, axe_x_relatif, axe_y_relatif, axe_z_relatif, axe_z_relatif*Projectile1::norme_vitesse, id_lanceur)
{
	this->force = Projectile1::la_force;
};
Projectile1::~Projectile1()
{
};