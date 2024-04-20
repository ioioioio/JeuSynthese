#ifndef SURFACE_H
#define SURFACE_H

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

#include <vector>

#include "objetjeu.h"

namespace SurfaceType{
	enum {
	mur1, mur2, plafond, sol
};
};

class Surface : public ObjetJeu {
private:
	int type;
public:
	Surface(glm::vec3 position, float demie_largeur, float demie_hauteur, float lacet, float tangage, int type);

	virtual void subir_collision(glm::vec3 point_collision) override;

	int donner_type() {return this->type;};
	glm::vec3 donner_normale() const;
	std::vector<glm::vec3> donner_sommets();
};


#endif
