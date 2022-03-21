#pragma once

typedef          bool      bool8;

typedef          char      char8;

typedef signed   char      int8;
typedef signed   short     int16;
typedef signed   int       int32;
typedef signed   long long int64;

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef float              float32;
typedef double             float64;

// Render related types:
typedef uint32 T3D_Index;

namespace t3d
{
	// GLM vectors:
	using FVec2 = glm::vec2;
	using FVec3 = glm::vec3;
	using FVec4 = glm::vec4;

	// GLM matrices:
	using FMat2 = glm::mat2;
	using FMat3 = glm::mat3;
	using FMat4 = glm::mat4;
}
