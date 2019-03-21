#include <pwgl/Mesh.hpp>

using namespace pwgl;

Mesh::Mesh()
{
	build_Mesh();
	create_Mesh();
	populate_Verts();
}

int Mesh::get_Vertices()
{
	return vertices.size();
}

unsigned int Mesh::get_Elements()
{
	return elements.size();
}

void Mesh::set_Position(glm::vec3 position)
{
}

void Mesh::set_Normal(glm::vec3 normal)
{
}

void Mesh::set_Elements(unsigned int elements)
{
}

void Mesh::create_Mesh()
{
	glGenBuffers(1, &vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, 
		vertices.size() * sizeof(Vertex), 
		vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &element_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		elements.size() * sizeof(unsigned int), 
		elements.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::delete_Mesh()
{
	glDeleteBuffers(1, &vertex_vbo);
	glDeleteBuffers(1, &element_vbo);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::build_Mesh()
{
	for (int z = 0; z < vertex_height; z++)
	{
		for (int x = 0; x < vertex_width; x++)
		{
			int index = z * (vertex_height + 1) + x;

			if ((x % 2 == 0 && z % 2 == 0) || (x % 2 == 1 && z % 2 == 1))
			{
				elements.push_back(index);
				elements.push_back(index + 1);
				elements.push_back(index + (vertex_width + 2));

				elements.push_back(index);
				elements.push_back(index + (vertex_width + 2));
				elements.push_back(index + (vertex_width + 1));
			}

			else
			{
				elements.push_back(index);
				elements.push_back(index + 1);
				elements.push_back(index + (vertex_width + 1));

				elements.push_back(index + 1);
				elements.push_back(index + (vertex_width + 2));
				elements.push_back(index + (vertex_width + 1));
			}
		}
	}
}

void Mesh::populate_Verts()
{
	for (int z = 0; z < vertex_height + 1; z++)
	{
		for (int x = 0; x < vertex_width + 1; x++)
		{
			Vertex p;
			p.position = glm::vec3(x * cell_size, 0, z * cell_size);
			p.normal = glm::vec3(0, 0, 0);
			vertices.push_back(p);
		}
	}
}

