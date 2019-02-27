#include "Camera.hpp"

Camera::Camera()
{
	position = glm::vec3(0, 0, 0);
	direction = glm::vec3(0, 0, -1);
	vertical_field_of_view = 60;
	near_plane_distance = 1;
	far_plane_distance = 10000;
	translation_speed = glm::vec3(0, 0, 0);
	rotation_speed = glm::vec2(0, 0);
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::SetPosition(glm::vec3 p)
{
	position = p;
}

glm::vec3 Camera::GetDirection() const
{
	return direction;
}

void Camera::SetDirection(glm::vec3 d)
{
	direction = d;
}

float Camera::GetVerticalFOV() const
{
	return vertical_field_of_view;
}

void Camera::SetVerticalFOV(float d)
{
	vertical_field_of_view = d;
}

float Camera::GetNearPlane() const
{
	return near_plane_distance;
}

void Camera::SetNearPlane(float n)
{
	near_plane_distance = n;
}

float Camera::GetFarPlane() const
{
	return far_plane_distance;
}

void Camera::SetFarPlane(float f)
{
	far_plane_distance = f;
}

glm::vec3 Camera::GetLinearVelocity() const
{
	return glm::vec3();
}

void Camera::SetLinearVelocity(glm::vec3 v)
{
	translation_speed = v;
}

glm::vec2 Camera::GetRotationalVelocity() const
{
	return glm::vec2();
}

void Camera::SetRotationalVelocity(glm::vec2 v)
{
	rotation_speed = v;
}