#pragma once

// Core:

#define T3D_INLINE inline

#define T3D_CALL __fastcall

#define T3D_NO_DISCARD [[nodiscard]]


// Types:

#define T3D_DEFINE_TYPES typedef bool bool8;\
						 typedef          char      char8;\
						 typedef signed   char      int8;\
						 typedef signed   char      int8;\
						 typedef signed   short     int16;\
						 typedef signed   int       int32;\
						 typedef signed   long long int64;\
						 typedef unsigned char      uint8;\
						 typedef unsigned short     uint16;\
						 typedef unsigned int       uint32;\
						 typedef unsigned long long uint64;

// Logger:

#if _MSC_VER
#define T3D_FUNCTION __FUNCTION__
#else
#define T3D_FUNCTION __func__
#endif


// Constructors:

// Removes copy constructor and copy assignment operator.
#define T3D_NO_COPY(Class) Class(const Class&) = delete; \
                           Class& operator = (const Class&) = delete

// Removes move constructor and move assignment operator.
#define T3D_NO_MOVE(Class) Class(Class&&) = delete; \
						   Class& operator = (Class&&) = delete

// Defines default copy constructor and copy assignment operator.
#define T3D_DEFAULT_COPY(Class) Class(const Class&) noexcept = default; \
                           Class& operator = (const Class&) = default

// Defines default move constructor and move assignment operator.
#define T3D_DEFAULT_MOVE(Class) Class(Class&&) noexcept = default; \
						   Class& operator = (Class&&) = default


// ECS:

// UINT64_MAX
#define T3D_ENTITY_INVALID_ID 0xffffffffffffffffui64


// Skeletal animation:

#define T3D_MAX_BONE_INFLUENCE 4


// Directories:

#define T3D_RESOURCE_DIR std::string("../Resources/")
#define T3D_SHADER_DIR   std::string("Shaders/SPIR-V/")
