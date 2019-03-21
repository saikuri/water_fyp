#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

//TODO: to be used later for instancing.
//struct MeshGL
//{
//	GLuint first_element_index;
//	GLuint first_vertex_index;
//	GLuint element_count;
//	GLuint instance_count;
//};

//TODO: to be used later for instancing.
//struct Mesh
//{
//	GLuint vertex_vbo{ 0 };
//	GLuint element_vbo{ 0 };
//	GLuint vao{ 0 };
//	int element_count{ 0 };
//};
//

//struct Texture
//{
//	unsigned int id;
//	std::string type;
//	std::string path;
//};

namespace pwgl {
	class Mesh
	{
	public:		
		Mesh() {};

		//std::vector<Vertex>& get_Vertices();
		int get_Vertices();
		//std::vector<unsigned int>& get_Elements();
		unsigned int get_Elements();

		void set_Position(glm::vec3 position);
		void set_Normal(glm::vec3 normal);
		void set_Elements(unsigned int elements);


	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> elements;
		//std::vector<Texture> textures;

		unsigned int cell_width = 128;
		unsigned int cell_height = 128;
		unsigned int vertex_width = cell_width + 1;
		unsigned int vertex_height = cell_height + 1;

		float cell_size = 1.0f;

		GLuint vertex_vbo{ 0 };
		GLuint element_vbo{ 0 };
		GLuint vao{ 0 };

		void create_Mesh();
		void delete_Mesh();
		void build_Mesh();
		void populate_Verts();
	};
}


