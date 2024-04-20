#ifndef LANCEUR_H
#define LANCEUR_H

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


#include <map>
#include <string>
#include <vector>

#include "sphere.h"
#include "projectile1.h"
#include "projectile2.h"
#include "item.h"

namespace LanceurActions {
	enum Enum {
		avancer = GLFW_KEY_W,
		reculer = GLFW_KEY_S,
		strafer_gauche = GLFW_KEY_A,
		strafer_droite = GLFW_KEY_D,
		lancer = GLFW_MOUSE_BUTTON_LEFT,
		sauter = GLFW_KEY_SPACE,
		choisir_lancer1 = GLFW_KEY_1,
		choisir_lancer2 = GLFW_KEY_2
	};
};

enum class LancerType {
	type1, type2
};

struct LanceurRetour {
	std::list<Projectile> projectiles;
	int id_tueur;
};

class Lanceur : public Sphere
{
public:
    Lanceur(unsigned int id, std::string nom);
    ~Lanceur();

	GLboolean actions_en_cours[1024];

    glm::mat4 donner_matrice_vue();

    void deplacer_viseur(float& offset_x, float& offset_y);
    void apparaitre(glm::vec3 position);

	LanceurRetour actualiser(const GLfloat& delta_temps, std::map<unsigned int, Lanceur*>& lanceurs, std::list<Projectile>& projectiles, std::list<Item>& items, std::vector<Surface>& surfaces, const glm::vec3& vitesse_imposee);

	bool noclip {false};
	unsigned int donner_id() {return this->id;};
	std::string donner_nom() {return this->nom;};
	int donner_vie() {return this->vie;};
	bool en_vie() {return this->vie > 0;};
	unsigned int donner_qte_projectiles() {return this->qte_projectiles;};
	float donner_temps_inactivite() {return this->temps_inactivite;};
	glm::mat4 donner_matrice_modele() const;

	LancerType donner_type_lancer() {return this->type_lancer;};
	// constantes
	static const float delai_reapparition;

private:
    unsigned int id;
	std::string nom;
	int vie;
	int qte_projectiles;
	LancerType type_lancer;
    double delai_tir;
	float temps_inactivite;

	std::list<Projectile> verifier_tir();
	LancerType determiner_type_lancer();

	glm::vec3 calculer_vitesse_volontaire();
	void subir_collision_projectile(Projectile& projectile);
	void prendre_item(Item& item);
	void mourir();

	void recevoir_vitesse_imposee(glm::vec3 vitesse);
	void se_deplacer(const GLfloat& delta_temps);
	int verifier_collisions(std::map<unsigned int, Lanceur*>& lanceurs, std::list<Projectile>& projectiles, std::list<Item>& items, std::vector<Surface>& surfaces);
	// constantes
	static const int vie_initiale;
	static const int vie_max;
	static const int qte_projectiles_initial;
	static const int qte_projectiles_max;
	static const float norme_vitesse_volontaire;
	static const float sensibilite_viseur;
	static const float rayon;
	static const float vitesse_saut;
	static const GLfloat delai_max_tir;

};

#endif
