#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);

const unsigned int screen_width = 1280;
const unsigned int screen_height = 720;

int main()
	{
	//std::cout << "Testing, 1, 2, 3." << std::endl;

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

	// Render loop.
	while (!glfwWindowShouldClose(window))
		{
		glClearColor(0.f, 0.f, 0.25f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
		}

	glfwTerminate();
	return 0;
	}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
	glViewport(0, 0, width, height);
	}

