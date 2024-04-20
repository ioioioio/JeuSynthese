#version 300 es
precision mediump float;
out vec4 FragColor;

in vec2 v_texture_coord;

uniform vec4 u_filtre;
uniform sampler2D u_texture;

void main()
{
	//FragColor = texture(u_texture, v_texture_coord);
	vec4 couleur = texture(u_texture, v_texture_coord);
	FragColor = vec4(couleur.r*u_filtre.r, couleur.g*u_filtre.g, couleur.b*u_filtre.b, couleur.a*u_filtre.a);
}

