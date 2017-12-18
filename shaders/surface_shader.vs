#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_couleur;
layout (location = 2) in vec2 a_texture_coord;

uniform mat4 u_modele;
uniform mat4 u_vue;
uniform mat4 u_projection;

out vec2 v_texture_coord;

void main()
{
	gl_Position = u_projection*u_vue*u_modele*vec4(a_position, 1.0);
	v_texture_coord = vec2(a_texture_coord.x, a_texture_coord.y);
}