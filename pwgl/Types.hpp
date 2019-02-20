#pragma once

#ifndef __PWGL_TYPES__
#define __PWGL_TYPES__

#include "Config.hpp"

namespace pwgl {
	inline namespace pwgl_2 {

		class Types
		{
		public:
			Types();
			~Types();
		};

		class PWGL_API_TYPE Exception
		{
		public:
			virtual const char * what() noexcept;
		};

		class PWGL_API_TYPE InconsistencyException : Exception
		{
		public:
			virtual const char * what() noexcept override;
		};

		class PWGL_API_TYPE Vector2
		{
		public:
			float x, y;

		public:
			Vector2();
			Vector2(float X, float Y);
		};

		class PWGL_API_TYPE Vector3
		{
		public:
			float x, y, z;

		public:
			Vector3();
			Vector3(float X, float Y, float Z);
			Vector3(const Vector2& v, float Z);
		};
	}
}

#endif // !__PWGL_TYPES__



