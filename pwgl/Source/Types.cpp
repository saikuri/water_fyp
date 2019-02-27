#include "pwgl/pch.h"
#include "pwgl/Types.hpp"

using namespace pwgl;

Types::Types()
{
}

Types::~Types()
{
}

const char * Exception::what() noexcept
{
	return "an unknown exception has occurred";
}

const char * InconsistencyException::what() noexcept
{
	return "an unrecoverable inconsistency error has occurred";
}

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(float X, float Y) : x(X), y(Y)
{
}

Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z)
{
}

Vector3::Vector3(const Vector2& v, float Z) : x(v.x), y(v.y), z(Z)
{
}
