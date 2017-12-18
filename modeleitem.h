#ifndef MODELEITEM_H
#define MODELEITEM_H

#include "modele.h"
#include "item.h" // nécessaire ?

class ModeleItem : Modele
{
public:
	ModeleItem();
	~ModeleItem();

	void initialier_buffer();
	void dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, int type);

private:
	static const float sommets[];
	static const int taille_sommets;
	static const int indices[];
	static const int taille_indices;
};

#endif
