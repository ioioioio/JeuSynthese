#ifndef JEU_h
#define JEU_H
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <GLES3/gl3.h>
#else
    #include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>
#include <vector>
#include <map>

#include "objetjeu.h"
#include "affichage.h"
#include "terrain.h"
#include "lanceur.h"
#include "ia.h"
#include "projectile.h"

#include <glm/gtx/string_cast.hpp> //Pour test

enum ActionsJeu {
	AFFICHER_POINTAGE = GLFW_KEY_TAB,
	CHANGER_CAMERA = GLFW_KEY_C,
	NOCLIP = GLFW_KEY_N,
	RECOMMENCER = GLFW_KEY_R
};

class Jeu
{
public:
	Jeu(unsigned int largeur_fenetre, unsigned int hauteur_fenetre);
	~Jeu();

	void commencer_partie(unsigned int qte_lanceurs);
	void actualiser(float temps_courant);
	void afficher();

	// Gestion des p�riph�riques
	void gerer_touches(unsigned int touche, bool etat_touche);
	void gerer_souris(double pos_x, double pos_y);

private:
	unsigned int dernier_id; // un id diff�rent est assign� � chaque lanceur
	unsigned int id_joueur; // id du lanceur assign� au joueur qui aux commandes de l'ordinateur
	unsigned int id_lanceur_camera; // Le id du lanceur assign� � la cam�ra


	Affichage* affichage;
	Terrain terrain;

	std::map<unsigned int, Lanceur*> lanceurs;
	std::vector<Ia> ias;
	std::list<Projectile> projectiles;

	std::map<unsigned int, int> pointage; // <id_joueur, points>

	void recommencer_partie();

	// physique
	const glm::vec3 gravite = glm::vec3(0.0f, -10.0f, 0.0f);

	//gestion du temps
	float delta_temps;
	float temps_derniere_image;

	//Gestion de la souris
	bool debut_jeu;
	float ancien_x_souris;
	float ancien_y_souris;

	//constantes
	static int nb_frags_max;
};

#endif
