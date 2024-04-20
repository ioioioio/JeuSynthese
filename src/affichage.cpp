#include "affichage.h"

Affichage::Affichage(unsigned int largeur_fenetre, unsigned int hauteur_fenetre)
	: text_rendering(largeur_fenetre, hauteur_fenetre)
{
	glEnable(GL_MULTISAMPLE); // anti-aliasing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->matrice_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(largeur_fenetre)/hauteur_fenetre, 0.1f, 50.0f);

	// calcul de la position du texte
	this->position_nom = glm::vec2(position_relative_nom.x*largeur_fenetre, position_relative_nom.y*hauteur_fenetre);
	this->position_vie = glm::vec2(position_relative_vie.x*largeur_fenetre, position_relative_vie.y*hauteur_fenetre);
	this->position_qte_projectiles = glm::vec2(position_relative_qte_projectiles.x*largeur_fenetre, position_relative_qte_projectiles.y*hauteur_fenetre);
	this->position_type_tir = glm::vec2(position_relative_type_tir.x*largeur_fenetre, position_relative_type_tir.y*hauteur_fenetre);
	this->position_points = glm::vec2(position_relative_points.x*largeur_fenetre, position_relative_points.y*hauteur_fenetre);
	this->taille_interligne = taille_relative_interligne*hauteur_fenetre;
	this->position_pointage_rang = glm::vec2(pos_rel_rang.x*largeur_fenetre, pos_rel_rang.y*hauteur_fenetre);
	this->position_pointage_nom = glm::vec2(pos_rel_nom.x*largeur_fenetre, pos_rel_nom.y*hauteur_fenetre);
	this->position_pointage_points = glm::vec2(pos_rel_points.x*largeur_fenetre, pos_rel_points.y*hauteur_fenetre);
}

Affichage::~Affichage()
{
}

void Affichage::afficher(unsigned int id_lanceur_camera, std::map<unsigned int, Lanceur*>& lanceurs, const std::list<Projectile>& projectiles, Terrain& terrain, std::map<unsigned int, int> pointage)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 matrice_vue = lanceurs[id_lanceur_camera]->donner_matrice_vue();

	for (Projectile projectile : projectiles) {
		glm::vec4 filtre (1.0f);
		if(id_lanceur_camera == projectile.donner_id_lanceur()) {
			filtre = {0.6f, 0.6f, 0.6f, 1.0f};
		}
		this->modele_projectile.dessiner(this->matrice_projection, projectile.donner_matrice_modele(), matrice_vue, filtre);
	}

	for (auto& paire_id_lanceur : lanceurs) {
		if (paire_id_lanceur.first != id_lanceur_camera) {
			Lanceur* lanceur_camera {paire_id_lanceur.second};
			glm::vec4 filtre(1.0f);
			if(!lanceur_camera->en_vie()) {
				float truc {(lanceur_camera->donner_temps_inactivite())/Lanceur::delai_reapparition};
				filtre = glm::vec4(1-truc/2,1, 1-truc/2, 1-truc/2);
			}
			this->modele_lanceur.dessiner(this->matrice_projection, paire_id_lanceur.second->donner_matrice_modele(), matrice_vue, filtre);
		}
	}

	for (auto item : terrain.donner_items()) {
		if (item.est_actif()) {
			this->modele_item.dessiner(this->matrice_projection, item.donner_matrice_modele(), matrice_vue, item.donner_type());
		}
	}

	for (auto surface : terrain.surfaces) {
		this->modele_surface.dessiner(this->matrice_projection, surface.donner_matrice_modele(), matrice_vue, surface.donner_type());
	}

	// affichage du texte
	Lanceur* lanceur_camera {lanceurs[id_lanceur_camera]};
	std::string id {lanceur_camera->donner_nom()};
	std::string vie {std::to_string(lanceur_camera->donner_vie())};
	std::string qte_projectiles {std::to_string(lanceur_camera->donner_qte_projectiles())};

	std::string texte_type_lancer;
	LancerType type_lancer = lanceur_camera->donner_type_lancer();
	if(type_lancer == LancerType::type1) {
		texte_type_lancer = " tir1";
	}
	else if(type_lancer == LancerType::type2) {
		texte_type_lancer = " tir2";
	}

	std::string points {std::to_string(pointage[id_lanceur_camera])};
	text_rendering.RenderText(id, this->position_nom, 1.0f, this->couleur_nom);
	text_rendering.RenderText(vie, this->position_vie, 1.0f, this->couleur_vie);
	text_rendering.RenderText(qte_projectiles, this->position_qte_projectiles, 1.0f, this->couleur_qte_projectiles);
	text_rendering.RenderText(texte_type_lancer, this->position_type_tir, 0.7f, this->couleur_qte_projectiles);
	text_rendering.RenderText(points, this->position_points, 1.0f, this->couleur_points);

	if(!lanceur_camera->en_vie()) {
		this->afficher_pointage(id_lanceur_camera, pointage);
	}
}

void Affichage::afficher_pointage(unsigned int id_lanceur_camera, const std::map<unsigned int, int>& pointage)
{
	// on met les points en ordre
	std::vector<std::pair<int, int>> ordre;
	for(auto& paire_id_points1 : pointage) {
		unsigned int i;
		for (i = 0; i < ordre.size(); i++) {
			std::pair<int, int> paire_id_points2 {ordre.at(i)};
			if(paire_id_points1.second > paire_id_points2.second) {
				break;
			}
		}
		ordre.insert(ordre.begin()+i, paire_id_points1);
	}

	// On affiche
	text_rendering.RenderText("RANG", this->position_pointage_rang, 1.0f, this->couleur_titre);
	text_rendering.RenderText("NOM", this->position_pointage_nom, 1.0f, this->couleur_titre);
	text_rendering.RenderText("POINTS", this->position_pointage_points, 1.0f, this->couleur_titre);
	for(unsigned int i {0}; i < ordre.size(); i++) {
		std::pair<int, int> paire_id_points {ordre.at(i)};
		float taille {1.0f};
		glm::vec3 couleur {this->couleur_points};
		if (id_lanceur_camera == paire_id_points.first) {
			taille = 1.1f;
			couleur *= 0.7f;
		}
		std::string rang {std::to_string(i+1)};

		// N'importe quoi. Chaque lanceur a déjà un nom.
		// Je ne devrais pas le recalculer
		std::string nom;
		if (paire_id_points.first == 0) {
			nom = "Joueur";
		}
		else {
			nom = "IA" + std::to_string(paire_id_points.first);
		}

		//std::string id {std::to_string(paire_id_points.first)};
		std::string points {std::to_string(paire_id_points.second)};
		glm::vec2 offset {0, this->taille_interligne*(i+1)};
		text_rendering.RenderText(rang, this->position_pointage_rang-offset, taille, couleur);
		text_rendering.RenderText(nom, this->position_pointage_nom-offset, taille, couleur);
		text_rendering.RenderText(points, this->position_pointage_points-offset, taille, couleur);
	}

}
