#include "sphere.h"
#include <glm/ext.hpp>


Sphere::Sphere(glm::vec3 position, float rayon, glm::vec3 vecteur_vitesse_imposee)
    : ObjetJeu(position, rayon, rayon, 0.0f, 0.0f, vecteur_vitesse_imposee)
 {
 }

 Sphere::~Sphere()
 {
 }

float Sphere::donner_rayon()
{
	return this->donner_demie_largeur();
}

bool Sphere::verifier_collision_sphere(Sphere& sphere)
{
	float distance {glm::length(this->position-sphere.donner_position())};
	float distance_min {this->demie_largeur+sphere.donner_rayon()};

	return distance_min > distance;
}

// réécriture de ce code : https://github.com/gametutorials/tutorials/blob/master/OpenGL/Sphere%20and%20Polygon%20Collision/3DMath.cpp
InfosCollisionSurface Sphere::verifier_collision_surface(Surface& surface)
{
	//bool collision{ false };
	InfosCollisionSurface infos_collision;
	infos_collision.collision = false;

	// Pour faciliter la lecture
	glm::vec3 position_sphere {this->position};
	float rayon_sphere {this->donner_rayon()};
	glm::vec3 point_plan {surface.donner_position()};

	// Si l'addition du rayon de la sphère et de la demie-largeur de la surface est plus grande que la distance entre la sphère et la surface, alors on arrête immédiatement les calculs.
	if(rayon_sphere+surface.donner_demie_largeur() < glm::length(point_plan-position_sphere)) {
		return infos_collision;
	}

	// Pour faciliter la lecture
	glm::vec3 normale_plan {surface.donner_normale()};

	// On vérifie la distance entre la sphère et un plan sur la surface
	float distance_plan_origine {-glm::dot(normale_plan, point_plan)};
	float distance_sphere_plan {glm::dot(normale_plan, position_sphere)+distance_plan_origine};

	infos_collision.normale_surface = normale_plan;
	infos_collision.distance = distance_sphere_plan;

	if (std::abs(distance_sphere_plan) <= rayon_sphere) {
		glm::vec3 vecteur_offset_sphere_plan {distance_sphere_plan*normale_plan}; // représente le vecteur entre le centre de la sphere et le point du plan le plus près
		glm::vec3 point_plan_plus_proche {position_sphere-vecteur_offset_sphere_plan}; // représente le point du plan le plus près du centre de la sphère

		std::vector<glm::vec3> sommets {surface.donner_sommets()};

		double somme_angles_sommets {0};
		// Pour chaque paire de deux sommets, on calcule l'angle formé à partir du point du plan le plus près du centre de la sphère
		for (unsigned int i {0}; i < sommets.size(); i++) {
			unsigned int i_suivant = (i < sommets.size()-1) ? i+1 : 0;

			// vecteurs entre le points le plus proche et des sommets adjacents de la surface
			glm::vec3 vecteur1 {sommets.at(i)-point_plan_plus_proche};
			glm::vec3 vecteur2 {sommets.at(i_suivant)-point_plan_plus_proche};
			float produit_scalaire = glm::dot(vecteur1, vecteur2);
			float magnitude {glm::length(vecteur1)*glm::length(vecteur2)};

			double angle_entre_sommets {acos(produit_scalaire/magnitude)};

			if (std::isnan(angle_entre_sommets)) {
				angle_entre_sommets = 0;
			}

			somme_angles_sommets += angle_entre_sommets;
		}

		if (somme_angles_sommets >= 0.99*2.0*glm::pi<double>()) {
			infos_collision.collision = true;
		}
		else {
			// On regarde la distance le centre de la sphère (projeté sur le plan) et chaque segment de la surface.
			for (unsigned int i {0}; i < sommets.size(); i++) {
				unsigned int i_suivant = (i < sommets.size()-1) ? i+1 : 0;

				glm::vec3 sommet1 = sommets.at(i);
				glm::vec3 sommet2 = sommets.at(i_suivant);

				// on cherche le point le plus près du centre de la sphère (projeté sur le plan) sur chaque segment
				glm::vec3 vecteur_centre_sommet1 {point_plan_plus_proche-sommet1 };
				glm::vec3 vecteur_direction_segment {glm::normalize(sommet2-sommet1)};
				float longueur_segment{ glm::length(sommet2-sommet1)};

				float distance_sommet1_point = glm::dot(vecteur_centre_sommet1, vecteur_direction_segment);

				glm::vec3 point_plus_pres;

				if (distance_sommet1_point <= 0) {
					point_plus_pres = sommet1;
				}
				else if (distance_sommet1_point >= longueur_segment) {
					point_plus_pres = sommet2;
				}
				else {
					// vecteur de sommet1 jusqu'au point le plus près sur le segment
					glm::vec3 vecteur_sommet1_point {vecteur_direction_segment*distance_sommet1_point};
					point_plus_pres = sommet1+vecteur_sommet1_point;
				}

				// On calcule la distance entre le centre de la sphère (projeté sur le plan) et le point le plus près sur le segment
				float distance_point_sphere = glm::length(point_plan_plus_proche-point_plus_pres);

				if (distance_point_sphere <= rayon_sphere) {
					infos_collision.collision = true;
					break;
				}
			}
		}
	}

	return infos_collision;
}

void Sphere::subir_collision_sphere(glm::vec3 position_autre_sphere, float rayon_autre_sphere) {
	glm::vec3 vecteur_difference = glm::normalize(this->position-position_autre_sphere);
	this->position = position_autre_sphere+vecteur_difference*(rayon_autre_sphere+this->donner_rayon());
}

void Sphere::subir_collision_surface(InfosCollisionSurface infos_collision) {
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
	this->vecteur_vitesse_imposee -= projection;
}
