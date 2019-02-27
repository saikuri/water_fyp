#pragma once
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();

	glm::vec3 GetPosition() const;
	glm::vec3 GetDirection() const;

	float GetVerticalFOV() const;
	float GetNearPlane() const;
	float GetFarPlane() const;

	void SetPosition();
	void GetPosition();

	void SetVerticalFOV();
	void SetNearPlane();
	void SetFarPlane();

private:
	glm::vec3 position;
	glm::vec3 direction;
	float vertical_field_of_view;
	float near_plane_distance;
	float far_plane_distance;

};