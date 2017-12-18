#include "modelesurface.h"

const float ModeleSurface::sommets[] {
	/*Positions*/			/*Normales*/		/*textures*/
	1.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f,  1.0f,
	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 	0.0f, 0.0f, 1.0f,	0.0f,  1.0f
};

const int ModeleSurface::taille_sommets {sizeof(ModeleSurface::sommets)};
const int ModeleSurface::indices[] {
	0, 1, 3,
	1, 2, 3
};
const int ModeleSurface::taille_indices {sizeof(ModeleSurface::indices)};

ModeleSurface::ModeleSurface()
    : Modele(Shader("shaders/shader.vs", "shaders/shader.fs"))
{
    this->initialier_buffer();

	this->textures[SurfaceType::sol] = charger_texture("textures/230.jpg");
	this->textures[SurfaceType::mur1] = charger_texture("textures/rustytiles02_diff.png");
	this->textures[SurfaceType::mur2] = charger_texture("textures/concrete01_diff.png");
	this->textures[SurfaceType::plafond] = charger_texture("textures/rustytiles02_diff.png");
}


ModeleSurface::~ModeleSurface()
{
}

void ModeleSurface::initialier_buffer()
{
	//Les données des sommets doivent être inscrites dans cet ordre: positions, normales, texture
    unsigned int VBO, EBO;
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &(this->buffer_sommets));
	glBindVertexArray(this->buffer_sommets);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, ModeleSurface::taille_sommets, ModeleSurface::sommets, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ModeleSurface::taille_indices, ModeleSurface::indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);
}

void ModeleSurface::dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, int type)
{
	this->shader.use();
	this->shader.setMat4("u_modele", matrice_modele);
	this->shader.setMat4("u_vue", matrice_vue);
	this->shader.setMat4("u_projection", matrice_projection);

	glm::vec4 filtre;
	if(type == SurfaceType::mur2) {
		filtre = glm::vec4(0.95, 0.85f, 0.85f, 1.0f);
	}
	else {
		filtre = glm::vec4(1.0f);
	}

	this->shader.setVec4("u_filtre", filtre);

	glBindTexture(GL_TEXTURE_2D, this->textures[type]);
	glBindVertexArray(this->buffer_sommets);
	glDrawElements(GL_TRIANGLES, ModeleSurface::taille_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
