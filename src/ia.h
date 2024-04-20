#ifndef IA_H
#define IA_H

#include <math.h>
#include <map>
#include <vector>

#include "lanceur.h"
#include "terrain.h"

enum class IaAction {attaquer, explorer, trouver_item};

class Ia {

public:
	Ia(Lanceur* lanceur, Terrain& terrain, std::map<unsigned int, Lanceur*>& lanceurs);

	void determiner_actions(float temps_courant);

private:
	Lanceur* lanceur; // Meilleure technique que de carrément passer un pointeur sur le lanceur ?
	Terrain& terrain; // L'IA a continuellement une vue d'ensemble du terrain. C'est un peu de la triche.
	std::map<unsigned int, Lanceur*>& lanceurs; // l'IA connait tous les joueurs. Encore de la triche.

	unsigned int id_cible;

	IaAction action_en_cours;
	std::vector<glm::vec3> chemin;
	unsigned int indice_etape_chemin; // correspond à un indice dans le vecteur chemin
	float temps_changement_indice; // sert à vérifier que l'ia ne reste jamais bloquée sur une case

	glm::vec3 determiner_destination_aleatoire(glm::vec3 position_depart);
	void trouver_chemin(glm::vec3 depart, glm::vec3 , float temps_courant);

	std::pair<int, float> verifier_tir();

	void controler_lanceur(glm::vec3 direction_deplacement);

	void attaquer(glm::vec3 direction_deplacement);
	void explorer(glm::vec3 direction_deplacement);
};

#endif
