#version 420 core

uniform sampler2D water_tex;

in vec3 varying_position;
in vec3 varying_normal;
in vec2 varying_texcoord;

out vec4 fragment_colour;

void main(void)
{
	//fragment_colour = texture(water_tex) * vec4(1.0, 0.5, 0.25, 1.0);
	fragment_colour = vec4(1.0, 0.5, 0.25, 1.0);
}