/*
	Cette classe est un copié-collé modifié de https://learnopengl.com/#!In-Practice/Text-Rendering
*/

// Std. Includes
#include <iostream>
#include <map>
#include <string>
// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
// GL includes
#include <learnopengl/shader.h>

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

class TextRendering
{
public:
	TextRendering(unsigned int largeur_fenetre, unsigned int hauteur_fenetre);

	void RenderText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color);

private:
	std::map<GLchar, Character> Characters;
	GLuint VAO;
	GLuint VBO;

	Shader shader {Shader("shaders/text.vs", "shaders/text.fs")};
	glm::mat4 projection;
};