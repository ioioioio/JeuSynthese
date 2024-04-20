#include "modelesphere.h"


ModeleSphere::ModeleSphere()
	: Modele(Shader("shaders/shader.vs", "shaders/shader.fs"))
{
	this->initialier_buffer();
}

ModeleSphere::~ModeleSphere()
{
}

//Adaptation de la fonction initBuffers() sur http://learningwebgl.com/lessons/lesson11/index.html
void ModeleSphere::initialier_buffer()
{
	const int nb_bandes_latitude {15};
	const int nb_bandes_longitude {15};

	float donnees[8*(nb_bandes_latitude+1)*(nb_bandes_longitude+1)];

	int i {0};
	for(int latitude {0}; latitude <= nb_bandes_latitude; latitude++) {
		float theta {latitude*glm::pi<float>()/nb_bandes_latitude};
		float sin_theta {std::sin(theta)};
		float cos_theta {std::cos(theta)};

		for(int longitude {0}; longitude <= nb_bandes_longitude; longitude++) {
			float phi {longitude*2*glm::pi<float>()/nb_bandes_longitude};
			float sin_phi {std::sin(phi)};
			float cos_phi {std::cos(phi)};

			float x {cos_phi*sin_theta};
			float y {cos_theta};
			float z {sin_phi*sin_theta};
			float u {1-((float)longitude/(float)nb_bandes_longitude)};
			float v {1-((float)latitude/(float)nb_bandes_latitude)};

            // position sommet
			donnees[i++] = x;
			donnees[i++] = y;
			donnees[i++] = z;

			// vecteur norme
			donnees[i++] = x;
			donnees[i++] = y;
			donnees[i++] = z;

			// position texture
			donnees[i++] = u;
			donnees[i++] = v;
		}
	}

	i = 0;
    unsigned int indices_donnees[6*(nb_bandes_latitude)*(nb_bandes_longitude)];
    for(int latitude {0}; latitude < nb_bandes_latitude; latitude++) {
        for(int longitude {0}; longitude < nb_bandes_longitude; longitude++) {
            int premier {(latitude*(nb_bandes_longitude+1)+longitude)};
            int second {premier+nb_bandes_longitude+1};

			indices_donnees[i++] = premier;
			indices_donnees[i++] = premier+1;
			indices_donnees[i++] = second;

			indices_donnees[i++] = second;
			indices_donnees[i++] = premier+1;
			indices_donnees[i++] = second+1;
        }
    }

	unsigned int VBO, EBO;
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &(this->buffer_sommets));
	glBindVertexArray(this->buffer_sommets);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(donnees), donnees, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_donnees), indices_donnees, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);
}

void ModeleSphere::dessiner(glm::mat4 matrice_projection, glm::mat4 matrice_modele, glm::mat4 matrice_vue, int type)
{
	this->shader.use();
	this->shader.setMat4("u_modele", matrice_modele);
	this->shader.setMat4("u_vue", matrice_vue);
	this->shader.setMat4("u_projection", matrice_projection);

	this->shader.setVec4("u_filtre", glm::vec4(1.0f));

	glBindTexture(GL_TEXTURE_2D, this->textures[type]);
	glBindVertexArray(this->buffer_sommets);
	glDrawElements(GL_TRIANGLES, 1350, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}