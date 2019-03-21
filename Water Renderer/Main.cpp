#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Source/Camera.hpp"
#include <vector>
#include <unordered_map>
#include <pwgl/Mesh.hpp>
#include <iostream>
#include <string>
#include <fstream>

void framebuffer_Size_CallBack(GLFWwindow* window, int width, int height);
void process_Input(GLFWwindow *window);
void mouse_CallBack(GLFWwindow* window, double xPos, double yPos);
void scroll_CallBack(GLFWwindow* window, double xOffset, double yOffset);
std::string string_FromFile(const std::string &filename);

const unsigned int screen_width = 1280;
const unsigned int screen_height = 720;

Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
//Camera camera(45.0f, 30.0f, 60.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
float lastX = screen_width / 2.0f;
float lastY = screen_height / 2.0f;
bool mouseEnable = true;

float delta_time = 0.0f;
float last_frame = 0.0f;

bool wire_mode = false; // Check at a later date.

typedef unsigned int MeshID;

pwgl::Mesh mesh_;

//struct Vertex
//{
//	glm::vec3 position;
//	glm::vec3 normal;
//	glm::vec2 texCoord;
//	glm::vec3 tangent;
//	glm::vec3 bitangent;
//};

GLuint water_tex;

//TODO: to be used later for instancing.
//struct MeshGL
//{
//	GLuint first_element_index;
//	GLuint first_vertex_index;
//	GLuint element_count;
//	GLuint instance_count;
//};

//struct Mesh
//{
//	GLuint vertex_vbo{ 0 };
//	GLuint element_vbo{ 0 };
//	GLuint vao{ 0 };
//	int element_count{ 0 };
//};

//std::vector<Vertex> vertices;

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
	glfwSetFramebufferSizeCallback(window, framebuffer_Size_CallBack);
	glfwSetCursorPosCallback(window, mouse_CallBack);
	glfwSetScrollCallback(window, scroll_CallBack);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// GLAD: Load all OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	//////////////////// MESH ////////////////////
	glEnable(GL_DEPTH_TEST);

	//mesh_.populate_Verts();
	//mesh_.build_Mesh();
	//mesh_.create_Mesh();

	//std::vector<Vertex> vertices;
	//std::vector<unsigned int> elements;
	//std::vector<Texture> textures;

	//unsigned int cell_width = 128;
	//unsigned int cell_height = 128;
	//unsigned int vertex_width = cell_width + 1;
	//unsigned int vertex_height = cell_height + 1;
	//float cell_size = 1.0f;

	//for (int z = 0; z < vertex_height + 1; z++)
	//{
	//	for (int x = 0; x < vertex_width + 1; x++)
	//	{
	//		Vertex p;
	//		p.position = glm::vec3(x * cell_size, 0, z * cell_size);
	//		p.normal = glm::vec3(0, 0, 0);
	//		vertices.push_back(p);
	//	}
	//}

	//for (int z = 0; z < vertex_height; z++)
	//{
	//	for (int x = 0; x < vertex_width; x++)
	//	{
	//		int index = z * (vertex_height + 1) + x;

	//		if ((x % 2 == 0 && z % 2 == 0) || (x % 2 == 1 && z % 2 == 1))
	//		{
	//			// Creating the first triangle of the quad.
	//			elements.push_back(index);
	//			elements.push_back(index + 1);
	//			elements.push_back(index + (vertex_width + 2));

	//			// Creating the second triangle of the quad.
	//			elements.push_back(index);
	//			elements.push_back(index + (vertex_width + 2));
	//			elements.push_back(index + (vertex_width + 1));
	//		}

	//		else
	//		{
	//			// Creating the first triangle of the quad.
	//			elements.push_back(index);
	//			elements.push_back(index + 1);
	//			elements.push_back(index + (vertex_width + 1));

	//			// Creating the second triangle of the quad.
	//			elements.push_back(index + 1);
	//			elements.push_back(index + (vertex_width + 2));
	//			elements.push_back(index + (vertex_width + 1));
	//		}
	//	}
	//}

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
	//GLuint vertex_vbo{ 0 };
	//glGenBuffers(1, &vertex_vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	//glBufferData(GL_ARRAY_BUFFER,
	//	vertices.size() * sizeof(Vertex),
	//	vertices.data(),
	//	GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//GLuint element_vbo{ 0 };
	//glGenBuffers(1, &element_vbo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	//	elements.size() * sizeof(unsigned int),
	//	elements.data(),
	//	GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//GLuint vao{ 0 };
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);

	//glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
	//	sizeof(Vertex), (void*)offsetof(Vertex, position));

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
	//	sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
	//	sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
	//	sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE,
	//	sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//////////////////// TEXTURE ///////////////////
	//glGenTextures(1, &water_tex);
	//glBindTexture(GL_TEXTURE_2D, water_tex);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
	//glBindTexture(GL_TEXTURE_2D, 0);


	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//////////////////// SHADER ////////////////////

	// Shader compile status.
	GLint compile_status = GL_FALSE;

	// Vertex shader creation.
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertex_shader_string = string_FromFile("water_vs.glsl");
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
	std::string fragment_shader_string = string_FromFile("water_fs.glsl");
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

		process_Input(window);

		glClearColor(0.f, 0.f, 0.25f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(water_shader_prog);

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, water_tex); // Texture data to use.
		//glUniform1i(glGetUniformLocation(water_shader_prog, "water_tex"), 0);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screen_width / (float)screen_height, 0.1f, 100.f);
		glUniformMatrix4fv(glGetUniformLocation(water_shader_prog, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(water_shader_prog, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(modelScale));
		glUniformMatrix4fv(glGetUniformLocation(water_shader_prog, "model"), 1, GL_FALSE, glm::value_ptr(model));
		
		//glBindVertexArray(mesh_.vao);
		glDrawElements(GL_TRIANGLES, mesh_.get_Elements(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glDeleteTextures(1, &water_tex);

	glfwTerminate();
	return 0;
}

//////////////////// UTILITY ////////////////////

void framebuffer_Size_CallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void toggleShading()
{
	wire_mode = !wire_mode;
}

//TODO: Look into applying noise into my mesh
//void ApplyNoise()
//{
//	//std::vector<Vertex> p;
//	//Vertex p;
//
//	for (int i = 0; i < vertices.size(); i++)
//	{
//		auto& v = vertices[i].position;
//		auto& n = vertices[i].normal;
//
//		auto result = Brownian(v);
//		vertices[i].position += n * result;
//	}
//}

//float Brownian(glm::vec3& pos)
//{
//	float octaves = 8.0f;
//	float lacunarity = 2.0f;
//	float gain = 0.5f;
//	int amp = 100;
//	float result = 0.0f;
//	float frequency = 0.005f;
//
//	for (int i = 0; i < octaves; i++)
//	{
//
//		amp *= gain;
//		frequency *= lacunarity;
//	}
//
//	return result;
//}

//TODO: Look into applying displacement into my mesh
void Displacement()
{
}

void process_Input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float camera_speed = 5 * delta_time;
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

	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
	{
		toggleShading();
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void mouse_CallBack(GLFWwindow * window, double xPos, double yPos)
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

void scroll_CallBack(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.ProcessMouseScrollWheel(yOffset);
}

std::string string_FromFile(const std::string &filename)
{
	std::ifstream if_str(filename);
	std::string content((std::istreambuf_iterator<char>(if_str)),
		(std::istreambuf_iterator<char>()));

	return content;
}

//TODO: Would I need to read directly into an image class?
std::vector<uint8_t> ImageFromFile(const std::string &filename)
{
	std::ifstream if_str(filename, std::ios::binary);
	std::vector<uint8_t> content((std::istreambuf_iterator<char>(if_str)),
		(std::istreambuf_iterator<char>()));

	return content;
}