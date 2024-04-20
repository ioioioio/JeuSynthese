#include "jeu.h"

Jeu::Jeu(unsigned int largeur_fenetre, unsigned int hauteur_fenetre)
	: dernier_id(0),
	  id_joueur(0),
      id_lanceur_camera(0), // Par d�faut, la cam�ra est assign�e au joueur (0).
	  delta_temps(0.0f),
      temps_derniere_image(0.0f),
	  debut_jeu(true),
      ancien_x_souris(largeur_fenetre/2.0f),
      ancien_y_souris(hauteur_fenetre/2.0f)
{
	this->affichage = new Affichage(largeur_fenetre, hauteur_fenetre);
}

Jeu::~Jeu()
{
	delete this->affichage;

	for (auto& paire_id_lanceur : this->lanceurs) {
		delete paire_id_lanceur.second;
	}
}
void Jeu::afficher()
{
	this->affichage->afficher(this->id_lanceur_camera, this->lanceurs, this->projectiles, this->terrain, this->pointage);
}

void Jeu::commencer_partie(unsigned int qte_lanceurs)
{
	dernier_id = 0;
	id_joueur = 0;
	id_lanceur_camera = 0;
	ias.clear();
	lanceurs.clear();
	projectiles.clear();

	this->terrain.generer_terrain();

	for(unsigned int i{0}; i < qte_lanceurs; i++) {
		unsigned int id = this->dernier_id;

		std::string nom;
		if (id == this->id_joueur) {
			nom = "Joueur";
		}
		else {
			nom = "IA" + std::to_string(id);
		}

		this->lanceurs[id] = new Lanceur(this->dernier_id, nom);
		this->dernier_id++;
		glm::vec3 pos {this->terrain.donner_position_apparition()};
		this->lanceurs[id]->apparaitre(pos);

		if(id != this->id_joueur) { // on assigne des ias aux lanceurs non-joueurs
			this->ias.push_back(Ia(this->lanceurs[id], this->terrain, this->lanceurs));
		}

		this->pointage[id] = 0;
	}
}

void Jeu::actualiser(float temps_courant)
{
	if(this->temps_derniere_image == 0.0f) {
		// On s'assure que temps_derniere_image est bien �gal au temps de la derni�re image.
		// Autrement, le delta_temps initial est trop grand
		this->temps_derniere_image = temps_courant;
	}
	this->delta_temps = temps_courant-this->temps_derniere_image;
	this->temps_derniere_image = temps_courant;

	if(delta_temps > 0.02) {
		delta_temps = 0.02f;
	}

	for(auto& item : this->terrain.donner_items()) {
		item.actualiser(delta_temps);
	}

	for(auto& ia : this->ias) {
		ia.determiner_actions(temps_courant);
	}

	for(auto& paire_id_lanceur : this->lanceurs) {
		Lanceur* lanceur {paire_id_lanceur.second};

		// On actualise et on obtient un r�sultat
		LanceurRetour retour = lanceur->actualiser(delta_temps, this->lanceurs, projectiles, this->terrain.donner_items(), this->terrain.donner_surfaces(), this->gravite);

		this->projectiles.splice(this->projectiles.end(), retour.projectiles);
		/*if(retour.projectile) {
			this->projectiles.push_back(*retour.projectile);
		}*/

		int id_tueur {retour.id_tueur};
		if(id_tueur >= 0) { // alors le lanceur vient d'�tre tu�
			this->pointage[id_tueur]++; // le tueur gagne un point
		}

		if(!lanceur->en_vie() && lanceur->donner_temps_inactivite() >= Lanceur::delai_reapparition) {
			glm::vec3 pos = this->terrain.donner_position_apparition();
			lanceur->apparaitre(pos);
		}
	}

	std::list<Projectile>::iterator i = projectiles.begin();
	while (i != projectiles.end())
	{
		if(i->est_en_vie()) {
			i->se_deplacer(delta_temps, this->terrain.donner_surfaces());
			i++;
		}
		else {
			i = projectiles.erase(i);
		}
	}
}

void Jeu::gerer_touches(unsigned int touche, bool etat_touche)
{
	if (touche == AFFICHER_POINTAGE && etat_touche == true) {
		//this->affichage->afficher_pointage(this->pointage);
	}
	if(touche == CHANGER_CAMERA && etat_touche == true) {
		if(this->id_lanceur_camera < this->lanceurs.size()-1) {
            ++this->id_lanceur_camera;
		}
		else {
            this->id_lanceur_camera = 0;
		}
	}
	if(touche == NOCLIP && etat_touche == true) {
		this->lanceurs[this->id_joueur]->noclip = (this->lanceurs[this->id_joueur]->noclip) ? false : true;
	}
	if (touche == RECOMMENCER && etat_touche == true) {
		this->commencer_partie(this->lanceurs.size());
	}


	this->lanceurs[this->id_joueur]->actions_en_cours[touche] = etat_touche;
}

void Jeu::gerer_souris(double pos_x, double pos_y)
{
	// Y a-t-il un moyen �l�gant d'�liminer les warnings sans faire des casts partout ?
	if(this->debut_jeu) {
		this->ancien_x_souris = static_cast<float>(pos_x);
		this->ancien_y_souris = static_cast<float>(pos_y);
		this->debut_jeu = false;
	}

	float offset_x = static_cast<float>(-pos_x+this->ancien_x_souris);
	float offset_y = static_cast<float>(this->ancien_y_souris-pos_y);

	this->ancien_x_souris = static_cast<float>(pos_x);
	this->ancien_y_souris = static_cast<float>(pos_y);

	this->lanceurs[this->id_joueur]->deplacer_viseur(offset_x, offset_y);
}
