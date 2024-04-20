#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <GLES3/gl3.h>
#else
    #include <glad/glad.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <GLFW/glfw3.h>

#include <iostream>
#include <learnopengl/shader.h>

#include <string>
#include <list>
#include <map>
#include <vector>
#include <math.h>

#include "text_rendering.h"
#include "objetjeu.h"
#include "projectile.h"
#include "lanceur.h"
#include "terrain.h"
#include "modeleitem.h"
#include "modelelanceur.h"
#include "modeleprojectile.h"
#include "modelesurface.h"




class Affichage
{
public:
	Affichage(unsigned int largeur_fenetre, unsigned int hauteur_fenetre);
	~Affichage();

	void afficher(unsigned int id_lanceur_camera, std::map<unsigned int, Lanceur*>& lanceurs, const std::list<Projectile>& projectiles, Terrain& terrain, std::map<unsigned int, int> pointage);
	void afficher_pointage(unsigned int id_lanceur_camera, const std::map<unsigned int, int>& pointage);

private:
	GLuint cossin_VAO;
	ModeleItem modele_item;
	ModeleLanceur modele_lanceur;
	ModeleSurface modele_surface;
	ModeleProjectile modele_projectile;

	glm::mat4 matrice_projection;

	TextRendering text_rendering;

	// position relatives au texte du pointage
	const float taille_relative_interligne {0.08f};
	const glm::vec2 pos_rel_rang {0.15f, 0.80f};
	const glm::vec2 pos_rel_nom {0.35f, 0.80f};
	const glm::vec2 pos_rel_points {0.65f, 0.80f};

	float taille_interligne;
	glm::vec2 position_pointage_rang;
	glm::vec2 position_pointage_nom;
	glm::vec2 position_pointage_points;


	// positions relatives du texte
	const glm::vec2 position_relative_nom {0.03f, 0.9f};
	const glm::vec2 position_relative_vie {0.35f, 0.03f};
	const glm::vec2 position_relative_qte_projectiles {0.60f, 0.03f};
	const glm::vec2 position_relative_type_tir {0.67f, 0.03f};
	const glm::vec2 position_relative_points {0.93f, 0.9f};

	glm::vec2 position_nom;
	glm::vec2 position_vie;
	glm::vec2 position_qte_projectiles;
	glm::vec2 position_type_tir;
	glm::vec2 position_points;

	// couleurs
	const glm::vec3 couleur_nom {0.8f, 0.8f, 0.8f};
	const glm::vec3 couleur_vie {0.8f, 0.2f, 0.3f};
	const glm::vec3 couleur_qte_projectiles {0.16f, 0.28f, 0.05f};
	const glm::vec3 couleur_points {0.1f, 0.5f, 0.9f};
	const glm::vec3 couleur_titre {0.2f, 0.01f, 0.75f};
};

#endif // AFFICHAGE_H
