#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Source/Camera.hpp"
#include <vector>

#include <iostream>
#include <string>
#include <fstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::string StringFromFile(const std::string &filename);

const unsigned int screen_width = 1280;
const unsigned int screen_height = 720;

glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);

glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camera_direction = glm::normalize(camera_pos - camera_target);

glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 camera_right = glm::normalize(glm::cross(up, camera_direction));
glm::vec3 camera_up = glm::cross(camera_direction, camera_right);

Camera camera_;

float delta_time = 0.0f;
float last_frame = 0.0f;


//struct Vertex
//{
//	glm::vec3 position;
//	glm::vec3 normal;
//	glm::vec2 texCoord;
//};

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

	// GLAD: Load all OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
		}

	//std::vector<Vertex> vertices;
	//std::vector<unsigned int> elements;

	// I feel like these could be changed significantly by adding in GLM library.
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
		};

	// I feel like these could be changed significantly by adding in GLM library.
	GLint indices[] = {
		0, 1, 3,
		1, 2, 3
		};
	
	// Generating vertex buffer object for position.
	GLuint vertex_vbo{ 0 };
	glGenBuffers(1, &vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices), vertices,
		GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint element_vbo{ 0 };
	glGenBuffers(1, &element_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices), indices,
		GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//GLuint vertex_vbo{ 0 };
	//glGenBuffers(1, &vertex_vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	//glBufferData(GL_ARRAY_BUFFER,
	//	vertices.size() * sizeof(Vertex),
	//	vertices.data(),
	//	GL_STATIC_DRAW); //TODO: needs sorting out when i've had food.
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//GLuint element_vbo{ 0 };
	//glGenBuffers(1, &element_vbo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	//	elements.size() * sizeof(unsigned int),
	//	elements.data(),
	//	GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint vao{ 0 };
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(float), (void*)0);

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

	glm::vec3 camera_position = camera_.GetPosition();
	glm::mat4 projection = glm::perspective(glm::radians(camera_.GetVerticalFOV()), (float)screen_width / (float)screen_height, camera_.GetNearPlane(), camera_.GetFarPlane());

	glm::mat4 view = glm::lookAt(camera_position, camera_position + camera_.GetDirection(),
		up);

	// Render loop.
	while (!glfwWindowShouldClose(window))
		{
		glClearColor(0.f, 0.f, 0.25f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		glUseProgram(water_shader_prog);

		glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, up);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
		camera_pos += camera_speed * camera_front;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera_pos -= camera_speed * camera_front;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera_pos -= glm::normalize(glm::cross(camera_front, up)) * camera_speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera_pos += glm::normalize(glm::cross(camera_front, up)) * camera_speed;
	}
}

std::string StringFromFile(const std::string &filename)
	{
	std::ifstream if_str(filename);
	std::string content((std::istreambuf_iterator<char>(if_str)),
		(std::istreambuf_iterator<char>()));

	return content;
	}