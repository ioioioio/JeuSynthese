#include "item.h"

const float Item::duree_inactivite {10.0f};
const float Item::rayon {0.40f};

Item::Item(glm::vec3 position)
	: Sphere(position, Item::rayon, glm::vec3(0)),
	  actif(true),
	  temps_depuis_capture(Item::duree_inactivite)
{
	int nombre_hasard = rand()%2;

	if (nombre_hasard == 1) {
		this->type = ItemType::vie;
	}
	else {
		this->type = ItemType::munition;
	}
};

int Item::se_faire_prendre() {
	int le_type {this->actif ? this->type : ItemType::inactif};
	this->actif = false;
	this->temps_depuis_capture = 0;

	return le_type;
}

void Item::actualiser(float delta_temps) {
	if(temps_depuis_capture < Item::duree_inactivite) {
		this->temps_depuis_capture += delta_temps;
	}
	else {
		this->actif = true;
	}
}