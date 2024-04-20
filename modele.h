#ifndef MODELE_H
#define MODELE_H

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <GLES3/gl3.h>
#else
    #include <glad/glad.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>

#include <learnopengl/shader.h>
#include <stb_image.h>

#include <map>

class Modele
{
public:
    Modele(const Shader& shader);
    ~Modele();

	Shader& donner_shader() {return shader;};

protected:
	Shader shader;
	GLuint buffer_sommets;
	std::map<int, GLuint> textures;

	GLuint charger_texture(char const * path);
};

#endif




