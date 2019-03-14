#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Source/Camera.hpp"
#include <vector>
#include <unordered_map>

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callBack(GLFWwindow* window, double xPos, double yPos);
void scroll_callBack(GLFWwindow* window, double xOffset, double yOffset);
std::string StringFromFile(const std::string &filename);

const unsigned int screen_width = 1280;
const unsigned int screen_height = 720;

Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
float lastX = screen_width / 2.0f;
float lastY = screen_height / 2.0f;
bool mouseEnable = true;

float delta_time = 0.0f;
float last_frame = 0.0f;

typedef unsigned int MeshID;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct Texture
{
	unsigned int id;
	string type;
};

struct MeshGL
{
	GLuint first_element_index;
	GLuint first_vertex_index;
	GLuint element_count;
	GLuint instance_count;
};

struct Mesh
{
	GLuint vertex_vbo{ 0 };
	GLuint element_vbo{ 0 };
	GLuint vao{ 0 };
	int element_count{ 0 };
};

std::unordered_map<MeshID, MeshGL> meshes;

int main()
{
	// Initialise and configure GLFW.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW window creation.
	GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "P4112379 James Metcalfe Computing Project", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callBack);
	glfwSetScrollCallback(window, scroll_callBack);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// GLAD: Load all OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	//std::vector<Vertex> vertices(4);
	std::vector<Vertex> vertices;
	std::vector<unsigned int> elements;
	std::vector<Texture> textures;

	//vertices[0].position = glm::vec3(0.5f, 0.5f, 0.0f);
	//vertices[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
	//vertices[2].position = glm::vec3(-0.5f, -0.5f, 0.0f);
	//vertices[3].position = glm::vec3(-0.5f, 0.5f, 0.0f);

	//elements = { 0, 1, 3, 1, 2, 3 };

	//std::vector<glm::vec3> positions;
	unsigned int cell_width = 128;
	unsigned int cell_height = 128;
	unsigned int vertex_width = cell_width + 1;
	unsigned int vertex_height = cell_height + 1;
	float cell_size = 1.0f;

	for (int z = 0; z < vertex_height; z++)
	{
		for (int x = 0; x < vertex_width; x++)
		{
			Vertex p;
			p.position = glm::vec3(z * cell_size, 0, x * cell_size);
			p.normal = glm::vec3(0.0f, 0.0f, 0.0f);
			vertices.push_back(p);
			//positions.push_back(glm::vec3(x * cell_size, 0, z * cell_size));

			int mesh_index = z * (vertex_height + 1) + x;

			if ((x % 2 == 0 && z % 2 == 0) || (x % 2 == 1 && z % 2 == 1))
			{
				// Creating the first triangle of the quad.
				elements.push_back(z * vertex_width + x + 1);
				elements.push_back(z * vertex_width + x + vertex_width + 1);
				elements.push_back(z * vertex_width + x + vertex_width); //TODO look into triangulate my terrain exercise [mesh.cpp]

				// Creating the second triangle of the quad.
				elements.push_back(z * vertex_width + x);
				elements.push_back(z * vertex_width + x + 1);
				elements.push_back(z * vertex_width + x + vertex_width);
			}

			else
			{
				// Creating the first triangle of the quad.
				elements.push_back(z * vertex_width + x + vertex_width + 1);
				elements.push_back(z * vertex_width + x + vertex_width);
				elements.push_back(z * vertex_width + x);

				// Creating the second triangle of the quad.
				elements.push_back(z * vertex_width + x + 1);
				elements.push_back(z * vertex_width + x + vertex_width + 1);
				elements.push_back(z * vertex_width + x);
			}
		}
	}

	//for (int i = 0; i < vertices.size(); i++)
	//{
	//	Vertex vert;
	//	vert.position = vertices[i].position;
	//	vert.normal = vertices[i].normal;

	//	if (textures.size() > 0)
	//	{
	//		vert.texCoord = vertices[i].texCoord;
	//		//vert.texCoord = (const glm::vec2 &)textures[i];
	//	}
	//	vertices[i]
	//	//vertices.push_back(vert);
	//}

	// Generating vertex buffer object for position.
	GLuint vertex_vbo{ 0 };
	glGenBuffers(1, &vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex),
		vertices.data(),
		GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint element_vbo{ 0 };
	glGenBuffers(1, &element_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		elements.size() * sizeof(unsigned int),
		elements.data(),
		GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint vao{ 0 };
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);

	//glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
	//	sizeof(Vertex), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, position));

	//glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
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

	// Shader compile status.
	GLint compile_status = GL_FALSE;

	// Vertex shader creation.
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertex_shader_string = StringFromFile("water_vs.glsl");
	const char * vertex_shader_code = vertex_shader_string.c_str();

	glShaderSource(vertex_shader, 1, (const GLchar **)&vertex_shader_code,
		NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);

	if (compile_status != GL_TRUE)
	{
		const int string_length = 1024;
		GLchar compile_log[string_length] = "";
		glGetShaderInfoLog(vertex_shader, string_length, NULL, compile_log);
		std::cerr << compile_log << std::endl;
	}

	// Fragment shader creation.
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragment_shader_string = StringFromFile("water_fs.glsl");
	const char * fragment_shader_code = fragment_shader_string.c_str();

	glShaderSource(fragment_shader, 1, (const GLchar **)&fragment_shader_code,
		NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);

	if (compile_status != GL_TRUE)
	{
		const int string_length = 1024;
		GLchar compile_log[string_length] = "";
		glGetShaderInfoLog(fragment_shader, string_length, NULL, compile_log);
		std::cerr << compile_log << std::endl;
	}

	// Shader program generation.
	GLuint water_shader_prog{ 0 };
	water_shader_prog = glCreateProgram();
	glAttachShader(water_shader_prog, vertex_shader);
	glBindAttribLocation(water_shader_prog, 0, "vertex_position");
	glDeleteShader(vertex_shader);

	glAttachShader(water_shader_prog, fragment_shader);
	glDeleteShader(fragment_shader);
	glLinkProgram(water_shader_prog);

	GLint link_status = 0;
	glGetProgramiv(water_shader_prog, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE)
	{
		const int string_length = 1024;
		GLchar link_log[string_length] = "";
		glGetProgramInfoLog(water_shader_prog, string_length, NULL, link_log);
		std::cerr << link_log << std::endl;
	}

	// Render loop.
	while (!glfwWindowShouldClose(window))
	{

		float currentFrame = glfwGetTime();
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;

		float modelScale = 0.5f;

		processInput(window);

		glClearColor(0.f, 0.f, 0.25f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(water_shader_prog);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screen_width / (float)screen_height, 0.1f, 100.f);
		glUniformMatrix4fv(glGetUniformLocation(water_shader_prog, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(water_shader_prog, "view"), 1, GL_FALSE, glm::value_ptr(view));

		//TODO model matrix implementation and add corresponding shader code.
		//TODO implement more triangles to create mesh [next step].
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(modelScale));
		glUniformMatrix4fv(glGetUniformLocation(water_shader_prog, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertex_vbo);
	glDeleteBuffers(1, &element_vbo);
	glDeleteVertexArrays(1, &vao);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float camera_speed = 2.5 * delta_time;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, delta_time);
	}
}

void mouse_callBack(GLFWwindow * window, double xPos, double yPos)
{
	if (mouseEnable)
	{
		lastX = xPos;
		lastY = yPos;
		mouseEnable = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callBack(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.ProcessMouseScrollWheel(yOffset);
}

std::string StringFromFile(const std::string &filename)
{
	std::ifstream if_str(filename);
	std::string content((std::istreambuf_iterator<char>(if_str)),
		(std::istreambuf_iterator<char>()));

	return content;
}