#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <map>

#include "sphere.h"

class Projectile : public Sphere
{
public:
	Projectile(glm::vec3 position, glm::vec3 axe_x_relatif, glm::vec3 axe_y_relatif, glm::vec3 axe_z_relatif, glm::vec3 vitesse, unsigned int id_lanceur);

	virtual glm::mat4 donner_matrice_modele() const override;
	
	void se_deplacer(const GLfloat& delta_temps, std::vector<Surface>& surfaces);
	int toucher_lanceur();
	unsigned int donner_id_lanceur() {return this->id_lanceur;};
	bool est_en_vie() {return this->en_vie;};

protected:
    int id_lanceur;
    int force {15};
	float taille {0.12f};
	//float vitesse {10.0f};

	

	int rebonds_restants {3};

	bool en_vie;

    //explosion
    int force_explosion;
    bool peut_exploser;

    bool transperce;

    //position
    float portee;
    float distance_parcourue;

	void verifier_collisions(std::vector<Surface>& surfaces);
	void subir_collision_surface(InfosCollisionSurface infos_collision);
};

#endif // PROJECTILE_H
