#ifndef TERRAIN_H
#define TERRAIN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <array>
#include <list>
#include <map>
#include <set>
#include <stdlib.h>
#include <time.h>

#include "surface.h"
#include "item.h"

template<typename T, std::size_t largeur>
struct Matrice3D : public std::array<std::array<std::array<T, largeur>, largeur>, largeur>
{
};

typedef std::array<int, 3> CoordMap;

// InfosCase est utilisé pour déterminer le chemin à parcourir
class InfosCase {
public:
	InfosCase() {this->distance = 0; this->precedent = CoordMap {0,0,0};}; // constructeur par défaut bidon
	InfosCase(float distance, CoordMap precedent) {this->distance = distance; this->precedent = precedent;};

	float donner_distance() {return this->distance;};
	CoordMap donner_precedent() {return this->precedent;};

private:
	float distance;
	CoordMap precedent;
};

class Terrain {
public:
	Terrain();

	std::vector<Surface> surfaces;
	std::list<Item> items;

	void generer_terrain();

	glm::vec3 donner_position_apparition();
	unsigned int indice_position_apparition;

	static const int largeur_map {50};
	const float largeur_surface {1.0f};
	Matrice3D<bool, largeur_map>& donner_map() {return this->matrice_map;};

	CoordMap convertir_position_coordmap(glm::vec3 position);
	glm::vec3 convertir_coordmap_position(CoordMap coord);

	std::vector<glm::vec3> trouver_chemin(glm::vec3 depart, glm::vec3 destination);

	bool donner_etat_case(CoordMap case_test);
	std::list<Item>& donner_items() {return this->items;};
	std::vector<Surface>& donner_surfaces() {return this->surfaces;};
	CoordMap donner_case_valide(glm::vec3 position);
	glm::vec3 donner_pos_item_plus_proche(glm::vec3 position);

private:
	std::vector<glm::vec3> points_apparition;

	Matrice3D<bool, largeur_map> matrice_map;
};


#endif
