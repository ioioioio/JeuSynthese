#ifndef ITEM_H
#define ITEM_H

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

#include "sphere.h"

namespace ItemType {
	enum {
		vie, munition, inactif
	};
};

class Item : public Sphere {
public:
	Item(glm::vec3 position);

	void actualiser(float delta_temps);
	int se_faire_prendre();

	bool est_actif() {return actif;};
	int donner_type() {return this->type;};

private:
	int type;
	bool actif;
	static const float duree_inactivite;
	float temps_depuis_capture;

	static const float rayon;
};

#endif
