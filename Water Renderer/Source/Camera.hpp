#pragma once
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();

	bool IsStatic() const { return false; }

	glm::vec3 GetPosition() const;
	glm::vec3 GetDirection() const;

	float GetVerticalFOV() const;
	float GetNearPlane() const;
	float GetFarPlane() const;

	glm::vec3 GetLinearVelocity() const;
	glm::vec2 GetRotationalVelocity() const;

	void SetPosition(glm::vec3 p);
	void SetDirection(glm::vec3 d);

	void SetVerticalFOV(float d);
	void SetNearPlane(float n);
	void SetFarPlane(float f);

	void SetLinearVelocity(glm::vec3 v);
	void SetRotationalVelocity(glm::vec2 v);

private:
	glm::vec3 position;
	glm::vec3 direction;
	float vertical_field_of_view;
	float near_plane_distance;
	float far_plane_distance;
	glm::vec3 translation_speed;
	glm::vec2 rotation_speed;

};