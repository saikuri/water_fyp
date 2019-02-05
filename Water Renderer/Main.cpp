#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include <iostream>
#include <string>
#include <fstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int screen_width = 1280;
const unsigned int screen_height = 720;

int main()
{
	// Initialise and configure GLFW.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW window creation.
	GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Test Water Render Window", NULL, NULL);
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

	// I feel like these could be changed significantly by adding in GLM library.
	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
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
		GL_STATIC_DRAW); //TODO: needs sorting out when i've had food.
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint element_vbo{ 0 };
	glGenBuffers(1, &element_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices), indices,
		GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint vao{ 0 };
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Shader compile status.
	GLint compile_status = GL_FALSE;

	// Vertex shader creation.
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	std::ifstream test;
	std::string vertex_shader_string;
	test.open("resource://water_vs.glsl", std::ifstream::in);
	std::getline(test, vertex_shader_string);
	
	//TODO: Need changing potentially with ifstream to load in the appropriate shaders.

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
	std::string fragment_shader_string;

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
		glClearColor(0.f, 0.f, 0.25f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(water_shader_prog);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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