#include "ia.h"

#include <glm/gtx/string_cast.hpp> // pour test

Ia::Ia(Lanceur* lanceur, Terrain& terrain, std::map<unsigned int, Lanceur*>& lanceurs)
	: lanceur(lanceur),
	terrain(terrain),
	lanceurs(lanceurs),
	action_en_cours(IaAction::explorer),
	temps_changement_indice{0}
{
}


void Ia::determiner_actions(float temps_courant)
{
	if(this->temps_changement_indice == 0) {
		this->temps_changement_indice = temps_courant;
	}

	glm::vec3 position {this->lanceur->donner_position()};

	this->action_en_cours = IaAction::explorer;

	if (this->lanceur->donner_qte_projectiles() > 0 && this->lanceur->donner_vie() > 30) {
		std::pair<int, float> paire_id_distance_adversaire {this->verifier_tir()};
		this->id_cible = paire_id_distance_adversaire.first;
		if (this->id_cible != this->lanceur->donner_id()) {
			this->action_en_cours = IaAction::attaquer;
			float distance {paire_id_distance_adversaire.second};
			if(distance <= 3.0f) {
				this->lanceur->actions_en_cours[LanceurActions::choisir_lancer1] = false;
				this->lanceur->actions_en_cours[LanceurActions::choisir_lancer2] = true;
			}
			else {
				this->lanceur->actions_en_cours[LanceurActions::choisir_lancer1] = true;
				this->lanceur->actions_en_cours[LanceurActions::choisir_lancer2] = false;
			}
		}
	}
	
	// si le temps depuis le dernier changement d'indice est trop grand, alors l'ia est bloquée.
	// On prétend alors que l'ia est arrivée à l'étape finale de son chemin
	float delta_temps = temps_courant-this->temps_changement_indice;
	if (delta_temps > 1.0) {
		this->indice_etape_chemin = this->chemin.size();
	}

	// Si l'indice est plus grand que la taille du chemin, alors on est arrivé à destination
	// On change donc de trajet
	if (this->indice_etape_chemin >= this->chemin.size()) {
		glm::vec3 destination {this->determiner_destination_aleatoire(position)};
		this->trouver_chemin(position, destination, temps_courant);
	}

	glm::vec3 etape = this->chemin.at(this->indice_etape_chemin);
	glm::vec3 vecteur_deplacement = etape-position;
	glm::vec3 direction_deplacement = glm::normalize(vecteur_deplacement);

	this->controler_lanceur(direction_deplacement);

	if (glm::length(vecteur_deplacement) < this->lanceur->donner_rayon()) {
        ++this->indice_etape_chemin;
		this->temps_changement_indice = temps_courant;
	}
}

std::pair<int, float> Ia::verifier_tir()
{
	glm::vec3 position {this->lanceur->donner_position()};
	int id_ia = this->lanceur->donner_id();
	float dist_max = 7; // distance max arbitraire entre l'ia et les adversaires
	std::pair<int, float> paire_id_distance {id_ia, dist_max+1}; 

	for(auto& paire_id_lanceur : this->lanceurs) {
		int id_adversaire = paire_id_lanceur.first;
		if(id_adversaire != id_ia) {
			Lanceur* adversaire{paire_id_lanceur.second};
			if(!adversaire->en_vie()){
				continue; // On n'analyse pas un lanceur mort.
			}
			glm::vec3 pos_adversaire {adversaire->donner_position()};
			glm::vec3 vec_ia_adversaire {pos_adversaire-position};
			float distance_ia_adversaire {glm::length(vec_ia_adversaire)};
			
			bool tir_possible {true};
			if (distance_ia_adversaire < dist_max) {
				glm::vec3 vec_direction_ia_adversaire {0.02f*glm::normalize(vec_ia_adversaire)};
				
				// Ne fonctionne pas super bien
				for (glm::vec3 droite {vec_direction_ia_adversaire}; glm::length(droite) <= distance_ia_adversaire-1; droite += vec_direction_ia_adversaire) {
					CoordMap case_test = this->terrain.convertir_position_coordmap(position+droite);
					bool etat_case {this->terrain.donner_etat_case(case_test)};
					if (etat_case == false) {
						tir_possible = false;
						break;
					}
				}

				if(tir_possible && distance_ia_adversaire < paire_id_distance.second) {
					paire_id_distance = {id_adversaire , distance_ia_adversaire};
				}
			}
		}
	}

	return paire_id_distance;
}

void Ia::controler_lanceur(glm::vec3 direction_deplacement)
{
	if(this->action_en_cours == IaAction::explorer) {
		this->explorer(direction_deplacement);
	}
	else if(this->action_en_cours == IaAction::attaquer) {
		this->attaquer(direction_deplacement);
	}

}
void Ia::attaquer(glm::vec3 direction_deplacement) {
	float lacet {this->lanceur->donner_lacet()};
	float tangage {this->lanceur->donner_tangage()};

	glm::vec3 position_adversaire {this->lanceurs[this->id_cible]->donner_position()};

	glm::vec3 vec_ia_adversaire {position_adversaire-this->lanceur->donner_position()};

	float angle_deplacement_horizontal {0};

	if (vec_ia_adversaire.z == 0) {
		if (vec_ia_adversaire.x < 0) {
			angle_deplacement_horizontal = 90;
		}
		else {
			angle_deplacement_horizontal = -90;
		}
	}
	else {
		angle_deplacement_horizontal = atan2(vec_ia_adversaire.x, vec_ia_adversaire.z)*180/glm::pi<float>();

		if (angle_deplacement_horizontal > 0) {
			angle_deplacement_horizontal -= 180;
		}
		else {
			angle_deplacement_horizontal += 180;
		}
	}

	glm::vec3 vec_unitaire_regard {glm::normalize(vec_ia_adversaire)};

	float angle_deplacement_vertical {asin(vec_unitaire_regard.y)*180/glm::pi<float>()};

	float offset_viseur_x = angle_deplacement_horizontal-lacet;
	float offset_viseur_y = angle_deplacement_vertical-tangage;

	this->lanceur->deplacer_viseur(offset_viseur_x, offset_viseur_y);
	lanceur->actions_en_cours[LanceurActions::lancer] = true;
}

void Ia::explorer(glm::vec3 direction_deplacement) {
	lanceur->actions_en_cours[LanceurActions::lancer] = false;
	float lacet {this->lanceur->donner_lacet()};
	float angle_deplacement_horizontal = 0;

	// calcul de l'angle de déplacement horizontal
	if (direction_deplacement.z == 0) {
		if (direction_deplacement.x < 0) {
			angle_deplacement_horizontal = 90;
		}
		else {
			angle_deplacement_horizontal = -90;
		}
	}
	else {
		angle_deplacement_horizontal = atan2(direction_deplacement.x, direction_deplacement.z) * 180 / glm::pi<float>();//-180;

		if (angle_deplacement_horizontal > 0) {
			angle_deplacement_horizontal -= 180;
		}
		else {
			angle_deplacement_horizontal += 180;
		}
	}

	float offset_viseur_x = angle_deplacement_horizontal-lacet;

	// On corrige l'angle pour qu'il ne soit pas plus grand que 180
	if (offset_viseur_x > 180) {
		offset_viseur_x = 360 - offset_viseur_x;
	}
	else if (offset_viseur_x < -180) {
		offset_viseur_x = 360 + offset_viseur_x;
	}

	// On avance seulement si l'angle n'est pas trop grand
	if (abs(offset_viseur_x) < 20) {
		lanceur->actions_en_cours[LanceurActions::avancer] = true;
	}
	else {
		lanceur->actions_en_cours[LanceurActions::avancer] = false;
	}


	// calcul de l'angle de déplacement vertical
	float angle_deplacement_vertical = sin(direction_deplacement.y) * 180 / glm::pi<float>();

	if (angle_deplacement_vertical > 15) {
		lanceur->actions_en_cours[LanceurActions::sauter] = true;
	}
	else {
		lanceur->actions_en_cours[LanceurActions::sauter] = false;
	}

	float tangage {this->lanceur->donner_tangage() };
	float offset_viseur_y = 0-tangage; // On veut que l'ia regarde toujours devant soi

	//déplacement du viseur
	this->lanceur->deplacer_viseur(offset_viseur_x, offset_viseur_y);
}

glm::vec3 Ia::determiner_destination_aleatoire(glm::vec3 depart)
{
	glm::vec3 destination {depart};
	CoordMap coord_depart = this->terrain.donner_case_valide(depart);
	CoordMap coord_destination = coord_depart;
	bool items_verifies {false};
	while(coord_depart == coord_destination) {
		if(!items_verifies) { // s'il y a encore des items actifs en jeu, alors on veut collecter des items
			destination = this->terrain.donner_pos_item_plus_proche(depart);

			items_verifies = true;
		}
		else {
			destination = this->terrain.donner_position_apparition();
		}
		
		//coord_destination = this->terrain.convertir_position_coordmap(destination);
		coord_destination = this->terrain.donner_case_valide(destination);
	}

	return destination;
}

void Ia::trouver_chemin(glm::vec3 depart, glm::vec3 destination, float temps_courant)
{
	this->chemin = this->terrain.trouver_chemin(depart, destination);
	this->indice_etape_chemin = 0;
	this->temps_changement_indice = temps_courant;
}

