#include "modeleitem.h"

const float ModeleItem::sommets[]{ // copié-collé de https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/6.multiple_lights/multiple_lights.cpp
								   // positions          // normales           // texture
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
};
const int ModeleItem::taille_sommets {sizeof(ModeleItem::sommets)};
const int ModeleItem::indices[]{ //copié-collé modifié de http://learningwebgl.com/lessons/lesson06/index.html
	0, 2, 1,      0, 3, 2,
	4, 5, 6,      4, 6, 7,
	8, 9, 10,     8, 10, 11,
	12, 14, 13,   12, 15, 14,
	16, 17, 18,   16, 18, 19,
	20, 22, 21,   20, 23, 22
};
const int ModeleItem::taille_indices{ sizeof(ModeleItem::indices) };

ModeleItem::ModeleItem()
	: Modele(Shader("shaders/shader.vs", "shaders/shader.fs"))
{
	this->initialier_buffer();

	this->textures[ItemType::vie] = charger_texture("textures/MP_diff_red.png");
	this->textures[ItemType::munition] = charger_texture("textures/MP_diff_green.png");
};

ModeleItem::~ModeleItem()
{
};

void ModeleItem::initialier_buffer()
{
	//Les données des sommets doivent être inscrites dans cet ordre: positions, normales, texture
	unsigned int VBO, EBO;
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &(this->buffer_sommets));
	glBindVertexArray(this->buffer_sommets);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, ModeleItem::taille_sommets, ModeleItem::sommets, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ModeleItem::taille_indices, ModeleItem::indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void ModeleItem::dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, int type)
{
	this->shader.use();
	this->shader.setMat4("u_modele", matrice_modele);
	this->shader.setMat4("u_vue", matrice_vue);
	this->shader.setMat4("u_projection", matrice_projection);

	this->shader.setVec4("u_filtre", glm::vec4(1.0f));

	glBindTexture(GL_TEXTURE_2D, this->textures[type]);
	glBindVertexArray(this->buffer_sommets);
	glDrawElements(GL_TRIANGLES, ModeleItem::taille_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}