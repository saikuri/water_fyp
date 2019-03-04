#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
	camera_front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(cam_speed), mouse_sensitivity(cam_sense), Zoom(cam_zoom)
{
	camera_position = position;
	world_up_direction = up;
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
	camera_front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(cam_speed), mouse_sensitivity(cam_sense), Zoom(cam_zoom)
{
	camera_position = glm::vec3(posX, posY, posZ);
	world_up_direction = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(camera_position, camera_position + camera_front, camera_up_direction);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = movement_speed * deltaTime;
	if (direction == FORWARD)
		camera_position += camera_front * velocity;
	if (direction == BACKWARD)
		camera_position -= camera_front * velocity;
	if (direction == LEFT)
		camera_position -= camera_right * velocity;
	if (direction == RIGHT)
		camera_position += camera_right * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
	xOffset *= mouse_sensitivity;
	yOffset *= mouse_sensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}

		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}
	}
	UpdateCameraVectors();
}

void Camera::ProcessMouseScrollWheel(float yOffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
	{
		Zoom -= yOffset;
	}
	
	if (Zoom <= 1.0f)
	{
		Zoom = 1.0f;
	}

	if (Zoom >= 45.0f)
	{
		Zoom = 45.0f;
	}
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	camera_front = glm::normalize(front);

	camera_right = glm::normalize(glm::cross(camera_front, world_up_direction));
	camera_up_direction = glm::normalize(glm::cross(camera_right, camera_front));
}

