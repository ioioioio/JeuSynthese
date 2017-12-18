#include "projectile.h"

Projectile::Projectile(glm::vec3 position, glm::vec3 axe_x_relatif, glm::vec3 axe_y_relatif, glm::vec3 axe_z_relatif, glm::vec3 vitesse, unsigned int id_lanceur)
    : Sphere(position+axe_z_relatif*0.2f, 0.12f, vitesse),
	  id_lanceur(id_lanceur),
	  en_vie {true}
{
	this->axe_x_relatif = axe_x_relatif;
	this->axe_y_relatif = axe_y_relatif;
	this->axe_z_relatif = axe_z_relatif;
}

glm::mat4 Projectile::donner_matrice_modele() const
{
	// Il ne devrait pas être nécessaire de reconstruire la matrice de rotation à chaque fois.
	glm::mat4 matrice_rotation(glm::mat3(this->axe_x_relatif, this->axe_y_relatif, this->axe_z_relatif));

    glm::mat4 matrice_modele;
	matrice_modele = glm::translate(matrice_modele, this->position);
    matrice_modele *= matrice_rotation;
	matrice_modele = glm::scale(matrice_modele, glm::vec3(this->demie_largeur));

	return matrice_modele;
}

void Projectile::se_deplacer(const GLfloat& delta_temps, std::vector<Surface>& surfaces)
{
	this->verifier_collisions(surfaces);

	this->position += this->vecteur_vitesse_imposee*delta_temps;
}

void Projectile::verifier_collisions(std::vector<Surface>& surfaces)
{
	if(this->en_vie) {
		for (Surface& surface : surfaces) {
			InfosCollisionSurface infos_collision = this->verifier_collision_surface(surface);
			if(infos_collision.collision) {
				this->subir_collision_surface(infos_collision);
				rebonds_restants -= 1;
				if(rebonds_restants <= 0) {
					this->en_vie = false;
				}
			}
		}
	}
}

void Projectile::subir_collision_surface(InfosCollisionSurface infos_collision) {
	float distance_sphere_plan {infos_collision.distance};
	glm::vec3 normale_surface {infos_collision.normale_surface};
	if (distance_sphere_plan >= 0) {
		this->position += normale_surface*(this->demie_largeur - distance_sphere_plan);
	}
	else {
		this->position += normale_surface*(this->demie_largeur + distance_sphere_plan);
	}

	// On calcule la projection de vecteur_vitesse_imposee sur la surface
	glm::vec3 projection = glm::dot(this->vecteur_vitesse_imposee, normale_surface)*normale_surface;

	// On élimine cette composante du vecteur_vitesse_imposee.
	this->vecteur_vitesse_imposee -= projection*2.0f;
}

int Projectile::toucher_lanceur()
{
	this->en_vie = false;

	return this->force;
}