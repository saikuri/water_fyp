#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines possible movement options for camera.
enum Camera_Movement 
{
FORWARD,
BACKWARD,
LEFT,
RIGHT
};

// Default camera values.
const float cam_yaw = -90.0f;
const float cam_pitch = 0.0f;
const float cam_speed = 2.5f;
const float cam_sense = 0.1f;
const float cam_zoom = 45.0f;

class Camera
{
public:
	// Camera Attributes.
	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up_direction;
	glm::vec3 camera_right;
	glm::vec3 world_up_direction;

	// Euler Angles.
	float Yaw;
	float Pitch;

	// Camera Options.
	float movement_speed;
	float mouse_sensitivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = cam_yaw, float pitch = cam_pitch);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
	void ProcessMouseScrollWheel(float yOffset);

private:
	void UpdateCameraVectors();
};