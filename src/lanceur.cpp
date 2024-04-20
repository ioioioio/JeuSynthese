#include "lanceur.h"

#include <glm/gtx/string_cast.hpp> //Pour test
#include <iostream>

const int Lanceur::vie_initiale {100};
const int Lanceur::vie_max {150};
const int Lanceur::qte_projectiles_initial {25};
const int Lanceur::qte_projectiles_max {75};
const float Lanceur::norme_vitesse_volontaire {4.0f};
const float Lanceur::sensibilite_viseur {0.1f};
const float Lanceur::rayon {0.3f};
const float Lanceur::vitesse_saut {3.0f};
const float Lanceur::delai_reapparition {2.0f};
const GLfloat Lanceur::delai_max_tir {100.0f};

Lanceur::Lanceur(unsigned int id, std::string nom)
	: Sphere(glm::vec3(0.0f), this->rayon, glm::vec3(0.0f, 0.0f, 0.0f)),
      id(id),
	  nom(nom),
	  type_lancer(LancerType::type1),
	  temps_inactivite(Lanceur::delai_reapparition) // Il est plus grand que le délai. Le lanceur peut donc apparaitre.
{
	memset(this->actions_en_cours, 0, sizeof(GLboolean)*1024);
}

Lanceur::~Lanceur()
{
}

glm::mat4 Lanceur::donner_matrice_vue()
{
    return glm::lookAt(this->position, this->position+axe_z_relatif, axe_y_relatif);
}

LancerType Lanceur::determiner_type_lancer() {
	if (this->actions_en_cours[LanceurActions::choisir_lancer1]) {
		this->type_lancer = LancerType::type1;
	}
	else if (this->actions_en_cours[LanceurActions::choisir_lancer2]) {
		this->type_lancer = LancerType::type2;
	}

	return this->type_lancer;
}

std::list<Projectile> Lanceur::verifier_tir()
{
	LancerType type_lancer {Lanceur::determiner_type_lancer()};

	std::list<Projectile> projectiles;
	if(this->actions_en_cours[LanceurActions::lancer] && this->delai_tir <= 0) {
		if(this->qte_projectiles > 0) {
			if(type_lancer == LancerType::type1) {
				projectiles.push_back(Projectile1(this->position, this->axe_x_relatif, this->axe_y_relatif, this->axe_z_relatif, this->id));
				this->qte_projectiles -= Projectile1::cout;
				this->delai_tir = Projectile1::delai;
			}
			else if(type_lancer == LancerType::type2) {
				switch (this->qte_projectiles) {
					case(1):
						projectiles.push_back(Projectile2(this->position, this->axe_x_relatif, this->axe_y_relatif, this->axe_z_relatif, this->id));
						break;
					default:
					case(3):
						projectiles.push_back(Projectile2(this->position+this->axe_y_relatif*0.207f, this->axe_x_relatif, this->axe_y_relatif, this->axe_z_relatif, this->id));
					case(2):
						projectiles.push_back(Projectile2(this->position+this->axe_x_relatif*0.12f, this->axe_x_relatif, this->axe_y_relatif, this->axe_z_relatif, this->id));
						projectiles.push_back(Projectile2(this->position-this->axe_x_relatif*0.12f, this->axe_x_relatif, this->axe_y_relatif, this->axe_z_relatif, this->id));
				}
				this->qte_projectiles -= Projectile2::cout;
				if(this->qte_projectiles<0) {
					this->qte_projectiles = 0;
				}
				this->delai_tir = Projectile2::delai;
			}
		}
	}

	return projectiles;
}

void Lanceur::deplacer_viseur(float& offset_x, float& offset_y)
{
    offset_x *= Lanceur::sensibilite_viseur;
    offset_y *= Lanceur::sensibilite_viseur;

    this->lacet += offset_x;
    if(this->lacet > 360.0f) {
        this->lacet -= 360.0f;
    }
    else if (this->lacet < -360) {
        this->lacet += 360.0f;
    }

    this->tangage += offset_y;
	if(this->tangage > 89.0f) {
		this->tangage = 89.0f;
	}
	if(this->tangage < -89.0f) {
		this->tangage = -89.0f;
	}

    actualiser_axes_relatifs();
}

glm::vec3 Lanceur::calculer_vitesse_volontaire()
{
    glm::vec3 direction_x_relatif;
    glm::vec3 direction_z_relatif;
	if(this->actions_en_cours[LanceurActions::avancer]) {
		direction_z_relatif = this->axe_z_relatif;
	}
	if(this->actions_en_cours[LanceurActions::reculer]) {
		direction_z_relatif = -this->axe_z_relatif;
	}
    if(this->actions_en_cours[LanceurActions::strafer_gauche]) {
		direction_x_relatif = -this->axe_x_relatif;
	}
    if(this->actions_en_cours[LanceurActions::strafer_droite]) {
		direction_x_relatif = this->axe_x_relatif;
	}


	glm::vec3 vitesse_volontaire;
	glm::vec3 direction_deplacement = direction_z_relatif + direction_x_relatif;
    if(glm::length(direction_deplacement) > 0.0f) {
		if(!this->noclip) {
			direction_deplacement.y = 0.0f;
		}
		vitesse_volontaire = glm::normalize(direction_deplacement);
    }
	else {
		vitesse_volontaire = glm::vec3(0.0f); // Moyen élégant de le faire sans recréer un objet ?
	}

	if(this->actions_en_cours[LanceurActions::sauter] && this->vecteur_vitesse_imposee.y <= 0.0f) {
		this->vecteur_vitesse_imposee.y += Lanceur::vitesse_saut;
	}

	return vitesse_volontaire;
}

void Lanceur::apparaitre(glm::vec3 position)
{
    this->position = position;
	this->vie = Lanceur::vie_initiale;
	this->qte_projectiles = Lanceur::qte_projectiles_initial;
	this->delai_tir = 0;
    actualiser_axes_relatifs();
}

void Lanceur::recevoir_vitesse_imposee(glm::vec3 vitesse)
{
	if(!this->noclip) {
		this->vecteur_vitesse_imposee += vitesse;
	}
	else {
		this->vecteur_vitesse_imposee = glm::vec3(0.0f);
	}
}

LanceurRetour Lanceur::actualiser(const GLfloat& delta_temps, std::map<unsigned int, Lanceur*>& lanceurs, std::list<Projectile>& projectiles, std::list<Item>& items, std::vector<Surface>& surfaces, const glm::vec3& vitesse_imposee)
{
	LanceurRetour retour;
	retour.id_tueur = -1; // initialisation bidon

	if (this->en_vie()) {
		this->recevoir_vitesse_imposee(vitesse_imposee*delta_temps);
		this->se_deplacer(delta_temps);

		if (!this->noclip) {
			retour.id_tueur = this->verifier_collisions(lanceurs, projectiles, items, surfaces);
		}

		retour.projectiles.splice(retour.projectiles.begin(), this->verifier_tir());

		if(this->delai_tir > 0) {
			this->delai_tir -= delta_temps;
		}

	}
	else {
		this->temps_inactivite += delta_temps;
	}

	return retour;
}

void Lanceur::se_deplacer(const GLfloat& delta_temps)
{
	glm::vec3 vitesse_volontaire = this->calculer_vitesse_volontaire();

	this->position += (this->vecteur_vitesse_imposee+vitesse_volontaire*this->norme_vitesse_volontaire)*delta_temps;
}

int Lanceur::verifier_collisions(std::map<unsigned int, Lanceur*>& lanceurs, std::list<Projectile>& projectiles, std::list<Item>& items, std::vector<Surface>& surfaces)
{
	int id_tueur {-1};
	for (Projectile& projectile : projectiles) {
		bool collision{ this->verifier_collision_sphere(projectile) };
		if (collision) {
			this->subir_collision_projectile(projectile);
			if(!this->en_vie()) {
				id_tueur = projectile.donner_id_lanceur();
				this->mourir();
			}
		}
	}

	for (auto& paire_id_lanceur : lanceurs) {
		if(paire_id_lanceur.first != this->id) {
			Lanceur lanceur {*paire_id_lanceur.second};
			bool collision {this->verifier_collision_sphere(lanceur)};
			if(collision) {
				this->subir_collision_sphere(lanceur.donner_position(), lanceur.donner_rayon());
			}
		}
	}

	for (Surface& surface : surfaces) {
		InfosCollisionSurface infos_collision = this->verifier_collision_surface(surface);
		if(infos_collision.collision) {
			this->subir_collision_surface(infos_collision);
		}
	}

	for (Item& item : items) {
		bool collision {this->verifier_collision_sphere(item)};
		if(collision) {
			this->prendre_item(item);
		}
	}

	return id_tueur;
}

void Lanceur::subir_collision_projectile(Projectile& projectile) {
	if(projectile.donner_id_lanceur() != this->id) {
		this->vie -= projectile.toucher_lanceur();
	}
	if (this->vie <= 0) {
		this->vie = 0;
	}

	this->subir_collision_sphere(projectile.donner_position(), projectile.donner_rayon());
}

void Lanceur::prendre_item(Item& item) {
	int type_item {item.se_faire_prendre()};

	if(type_item == ItemType::munition) {
		this->qte_projectiles += 20;
		if (this->qte_projectiles > Lanceur::qte_projectiles_max) {
			this->qte_projectiles = Lanceur::qte_projectiles_max;
		}
	}
	else if (type_item == ItemType::vie) {
		this->vie += 15;
		if (this->vie > Lanceur::vie_max) {
			this->vie = Lanceur::vie_max;
		}
	}
	// else if (ItemType::inactif) {}; // alors il ne se passe rien
}

void Lanceur::mourir() {
	this->temps_inactivite = 0;
}

glm::mat4 Lanceur::donner_matrice_modele() const
{
	glm::mat4 matrice_rotation(glm::mat3(this->axe_x_relatif, this->axe_y_relatif, -this->axe_z_relatif));

	glm::mat4 matrice_modele;
	matrice_modele = glm::translate(matrice_modele, this->position);
	matrice_modele *= matrice_rotation;
	matrice_modele = glm::scale(matrice_modele, glm::vec3(this->demie_largeur));

	return matrice_modele;
}
