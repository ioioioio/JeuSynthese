#include "modeleprojectile.h"

ModeleProjectile::ModeleProjectile()
	: ModeleSphere()
{
	this->textures[0] = charger_texture("textures/MP_diff_green.png");
};

ModeleProjectile::~ModeleProjectile()
{
};

void ModeleProjectile::dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, glm::vec4 filtre)
{
	this->shader.use();
	this->shader.setMat4("u_modele", matrice_modele);
	this->shader.setMat4("u_vue", matrice_vue);
	this->shader.setMat4("u_projection", matrice_projection);

	this->shader.setVec4("u_filtre", filtre);

	glBindTexture(GL_TEXTURE_2D, this->textures[0]);
	glBindVertexArray(this->buffer_sommets);
	glDrawElements(GL_TRIANGLES, 1350, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}