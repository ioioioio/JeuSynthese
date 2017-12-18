#include "modelelanceur.h"

ModeleLanceur::ModeleLanceur()
	: ModeleSphere()
{
	this->textures[0] = charger_texture("textures/brick3.png");
};

ModeleLanceur::~ModeleLanceur()
{
};

void ModeleLanceur::dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, glm::vec4 filtre)
{
	this->shader.use();
	this->shader.setMat4("u_modele", matrice_modele);
	this->shader.setMat4("u_vue", matrice_vue);
	this->shader.setMat4("u_projection", matrice_projection);

	this->shader.setVec4("u_filtre", filtre);

	glBindTexture(GL_TEXTURE_2D, this->textures[0]);
	glBindVertexArray(this->buffer_sommets);
	glDrawElements(GL_TRIANGLES, 5400, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}