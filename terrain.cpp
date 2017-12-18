#include "terrain.h"
#include <glm/gtx/string_cast.hpp>

Terrain::Terrain()
	: indice_position_apparition(0)
{
}

void Terrain::generer_terrain()
{
	points_apparition.clear();
	indice_position_apparition = 0;
	surfaces.clear();
	items.clear();

	// On initialise la matrice
    for(int z = 0; z < this->largeur_map; z++) {
		for (int y = 0; y < this->largeur_map; y++) {
			for (int x = 0; x < this->largeur_map; x++) {
                this->matrice_map[z][y][x] = false;
			}
        }
    }

	// On initialise rand
	srand(static_cast<unsigned int>(time(NULL)));

	const int nb_cases {250};

	const int demie_largeur {this->largeur_map/2};
	const int total_chances {31};
	const int chances_deplacement_x {15};
	const int chances_deplacement_y {1};

	// position initiale
	int x = demie_largeur;
	int y = demie_largeur;
	int z = demie_largeur;

	// on deplace le "curseur" dans la matrice
	for(unsigned int i = 0; i < nb_cases; i++) {
		int x_y_z = rand()%total_chances;

		int deplacement = 1-rand()%3;

		if(x_y_z < chances_deplacement_x) {
			x += deplacement;
			if(x > this->largeur_map-1 || x<2) {
				x = demie_largeur;
			}
		}
		else if(x_y_z < chances_deplacement_x+chances_deplacement_y) {
			y += deplacement;
			if(y > this->largeur_map-1 || y<2) {
				y = demie_largeur;
			}
		}
		else {
			z += deplacement;
			if (z > this->largeur_map-1 || z<2) {
				z = demie_largeur;
			}
		}

		// On fait des cases
		this->matrice_map[z][y][x] = true;
		this->matrice_map[z+1][y+1][x+2] = true;
		this->matrice_map[z+1][y+2][x+2] = true;
	}

	const float demie_largeur_surface {this->largeur_surface/2};
	const float demie_longueur_surface {this->largeur_surface/2};

	// Ne fonctionne pour l'instant que parce que toutes les surfaces ont des largeurs de 1
	for(int z = 0; z < this->largeur_map; z++) {
		for (int y = 0; y < this->largeur_map; y++) {
			for (int x = 0; x < this->largeur_map; x++) {
				if (this->matrice_map[z][y][x] == true) {
					if (this->matrice_map[z][y-1][x] == false) {
						this->surfaces.push_back(Surface(glm::vec3(x, y-0.5f, z), demie_largeur_surface, demie_longueur_surface, 0.0f, 90.0f, SurfaceType::sol));

						// Il y a un sol. Cette case peut donc être un point d'apparition
						int nombre_hasard {rand()%10};
						if (nombre_hasard == 0) {
							this->points_apparition.push_back(glm::vec3(x, y, z));
						}
					}
					if (this->matrice_map[z][y+1][x] == false) {
						this->surfaces.push_back(Surface(glm::vec3(x, y+0.5f, z), demie_largeur_surface, demie_longueur_surface, 0.0f, -90.0f, SurfaceType::plafond));
					}
					if (this->matrice_map[z][y][x+1] == false) {
						int type {SurfaceType::mur1};
						int nombre_hasard {rand() % 15};
						if(nombre_hasard == 1) {
							type = SurfaceType::mur2;
						}
						this->surfaces.push_back(Surface(glm::vec3(x+0.5f, y, z), demie_largeur_surface, demie_longueur_surface, 90.0f, 0.0f, type));
					}
					if (this->matrice_map[z][y][x-1] == false) {
						this->surfaces.push_back(Surface(glm::vec3(x-0.5f, y, z), demie_largeur_surface, demie_longueur_surface, -90.0f, 0.0f, SurfaceType::mur1));
					}
					if (this->matrice_map[z+1][y][x] == false) {
						this->surfaces.push_back(Surface(glm::vec3(x, y, z+0.5f), demie_largeur_surface, demie_longueur_surface, 0.0f, 0.0f, SurfaceType::mur1));
					}
					if (this->matrice_map[z-1][y][x] == false) {
						this->surfaces.push_back(Surface(glm::vec3(x, y, z-0.5f), demie_largeur_surface, demie_longueur_surface, 180.0f, 0.0f, SurfaceType::mur1));
					}

					// On crée des items
					int nombre_hasard {rand()%10};
					if (nombre_hasard == 0) {
						this->items.push_back(Item(glm::vec3(x, y, z)));
					}
				}
			}
		}
	}
}

glm::vec3 Terrain::donner_position_apparition() {
	glm::vec3 position {this->points_apparition.at(indice_position_apparition)};

	if(this->indice_position_apparition < this->points_apparition.size()-1) {
		++this->indice_position_apparition;
	}
	else {
		this->indice_position_apparition = 0;
	}

	return position;
}


std::vector<glm::vec3> Terrain::trouver_chemin(glm::vec3 depart, glm::vec3 destination) {
	CoordMap coord_depart = this->donner_case_valide(depart);
	CoordMap coord_destination = this->convertir_position_coordmap(destination);
	bool chemin_trouve {false};
	// algorithme A*
	std::set<CoordMap> coords_testees;
	std::set<CoordMap> coords_nontestees;

	coords_nontestees.insert(coord_depart);

	std::map<CoordMap, InfosCase> map_infos_cases;

	map_infos_cases[coord_depart] = InfosCase(0, coord_depart);

	while(coords_nontestees.size() > 0) {

		// On trouve la case non testée la plus proche du départ
		CoordMap coord_courante = *coords_nontestees.begin();

		float distance_min{map_infos_cases[coord_courante].donner_distance()};
		for(CoordMap coord : coords_nontestees) {
			float distance_courante{map_infos_cases[coord].donner_distance()};
			if(distance_courante < distance_min) {
				coord_courante = coord;
			}
		}

		// On vérifie si l'on est arrivé à la destination
		if (coord_courante == coord_destination) {
			chemin_trouve = true;
			break; // il ne sert à rien de poursuivre le calcul.
		}

		// la case courante devient une case testée
		coords_nontestees.erase(coord_courante);
		coords_testees.insert(coord_courante);

		// On parcoure toutes les cases directement adjacentes à la case courante
		for (int i {-1}; i <= 1; i++) { // sur axe x
			for (int j {-1}; j <= 1; j++) { // sur axe y
				for (int k {-1}; k <= 1; k++) { // sur axe z
					int x{coord_courante[2]+i};
					int y{coord_courante[1]+j};
					int z{coord_courante[0]+k};

					// On calcule la distance depuis le début
					// Comme il n'y a que trois possibilités, on les a calculées à l'avance pour éviter les racines carrées
					int total_i_j_k = abs(i) + abs(j) + abs(k);
					float distance_avec_case_courante;
					if (total_i_j_k == 1) {
						distance_avec_case_courante = 1.0f;
					}
					else if (total_i_j_k == 2) {
						distance_avec_case_courante = 1.41421f;
					}
					else if (total_i_j_k == 3) {
						distance_avec_case_courante = 1.73205f;
					}
					else { // total_i_j_k = 0. On n'a donc pas changé de case
						continue;
					}

					// On vérifie que la case est accessible
					if (matrice_map[z][y][x] == false) {
						continue;
					}
					else {
						// Cette partie ne fonctionne pas très bien.
						if (i != 0 && j != 0 && k != 0) {
							if (!((matrice_map[z][y][x-i] == true && matrice_map[z-k][y][x-i] == true)
								||
								(matrice_map[z-k][y][x] == true && matrice_map[z-k][y][x-i] == true)
								||
								(matrice_map[z][y][x-i] == true && matrice_map[z][y-j][x] == true)
								||
								(matrice_map[z][y-j][x] == true && matrice_map[z-k][y][x] == true)
								)) {
								continue;
							}

						}

						if(i != 0 && k != 0) {
							if(matrice_map[z][y][x-i] == false && matrice_map[z-k][y][x] == false) {
								continue;
							}
						}
						if(i != 0 && j != 0) {
							if(matrice_map[z][y][x-i] == false && matrice_map[z][y-j][x] == false) {
								continue;
							}
						}
						if(j != 0 && k != 0) {
							if(matrice_map[z][y-j][x] == false && matrice_map[z-k][y][x] == false) {
								continue;
							}
						}
					}

					CoordMap nouvelle_coord {z,y,x};

					// On vérifie que l'on n'a pas déjà testé cette case
					bool deja_testee = coords_testees.find(nouvelle_coord) != coords_testees.end();

					// On ne teste pas deux fois
					if(deja_testee) {
						continue;
					}

					float distance {map_infos_cases[coord_courante].donner_distance() + distance_avec_case_courante};

					// On regarde si la case est dans la liste coords_nontestees
					bool dans_liste_coords_nontestees {coords_nontestees.find(nouvelle_coord) != coords_nontestees.end()};

					// si elle n'est pas dans coords_nontestees, alors on l'ajoute
					if(!dans_liste_coords_nontestees) {
						coords_nontestees.insert(nouvelle_coord);
					}
					// si elle est déjà testée, alors on regarde si le nouveau chemin est plus court que l'ancien
					else if(distance >= map_infos_cases[nouvelle_coord].donner_distance()) {
						// si le nouveau chemin est plus long que l'ancien, alors on ne fait rien
						continue;
					}

					// On met à jour les infos.
					map_infos_cases[nouvelle_coord] = InfosCase(distance, coord_courante);
				}
			}
		}
	}

	std::vector<glm::vec3> chemin;
	if(chemin_trouve) {
		std::vector<CoordMap> chemin_inverse;
		CoordMap coord_courante {coord_destination}; // Visual Studio 2015 souligne en rouge mais il compile convenablement.
		while(coord_courante != coord_depart) {
			chemin_inverse.push_back(coord_courante);
			coord_courante = map_infos_cases[coord_courante].donner_precedent();
		}

	
		if (chemin_inverse.size() != 0) {
			for (int i = chemin_inverse.size()-1; i >= 0; i--) {
				CoordMap etape = chemin_inverse.at(i);
				chemin.push_back(this->convertir_coordmap_position(etape));
			}
		}
	}

	return chemin;
}

CoordMap Terrain::convertir_position_coordmap(glm::vec3 position) {
	int x {static_cast<int>(position.x)};
	int y {static_cast<int>(position.y)};
	int z {static_cast<int>(position.z)};

	return CoordMap {z, y, x};
}

glm::vec3 Terrain::convertir_coordmap_position(CoordMap coord) {
	float x {static_cast<float>(coord[2])};
	float y {static_cast<float>(coord[1])};
	float z {static_cast<float>(coord[0])};

	return glm::vec3(x, y, z);
}


bool Terrain::donner_etat_case(CoordMap case_test) {
	int x{case_test[2]};
	int y{case_test[1]};
	int z{case_test[0]};
	
	return this->matrice_map[z][y][x];
}

CoordMap Terrain::donner_case_valide(glm::vec3 position) {
	CoordMap coord_courante = this->convertir_position_coordmap(position);
	bool valide {this->donner_etat_case(coord_courante)};
	float distance_plus_proche = 10; // nombre trop grand arbitraire pour initialiser
	CoordMap plus_proche = coord_courante;
	
	// si la case est invalide, alors on cherche la case valide la plus proche
	if (!valide) {
		for(int i {-1}; i <= 1; i++) { // sur axe x
			for(int j {-1}; j <= 1; j++) { // sur axe y
				for(int k {-1}; k <= 1; k++) { // sur axe z
					int x{coord_courante[2]+i};
					int y{coord_courante[1]+j};
					int z{coord_courante[0]+k};
					glm::vec3 distance_test(x, y, z);
					
					float distance_courante {glm::length(distance_test-position)};
					if(distance_plus_proche > distance_courante) {
						distance_plus_proche = distance_courante;
						plus_proche = CoordMap {z, y, x};
					}

				}
			}
		}
	}

	return plus_proche;
}

glm::vec3 Terrain::donner_pos_item_plus_proche(glm::vec3 position) {
	glm::vec3 pos_item_plus_proche {position};
	float distance_item_plus_proche {1000}; // distance arbitraire trop grande pour initialiser

	for(auto& item : this->items) {
		if(item.est_actif()) {
			glm::vec3 pos_item {item.donner_position()};
			float distance {glm::length(pos_item-position)};
			if(distance < distance_item_plus_proche) {
				distance_item_plus_proche = distance;
				pos_item_plus_proche = pos_item;

				if(distance < 1.5) {
					break; // pas la peine de chercher plus loin
				}
			}
		}
	}

	return pos_item_plus_proche;
}