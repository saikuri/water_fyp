#version 420 core
//layout(location = 0) in vec3 vertex_position;
in vec3 vertex_position;

out vec3 varying_position;

void main(void)
{
	gl_Position = vec4(vertex_position, 1.0); // TODO Need to figure out why this isn't reading to gl_Position.
}