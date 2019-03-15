#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <vector>

class View
{
public:
	View();

	~View();

private:

	void windowViewWillStart(GLFWwindow* window);

	void windowViewDidReset(GLFWwindow* window);

	void windowViewDidStop(GLFWwindow* window);

	void windowViewDidRender(GLFWwindow* window);


	enum VertexIndexes
	{
		kVertexPos = 0,
		kVertexNorm = 1,
		kVertexCoord = 2,
		kVertexTangent = 3,
		kVertexBitangent = 4
	};
};