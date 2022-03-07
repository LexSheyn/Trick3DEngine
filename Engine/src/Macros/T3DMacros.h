#pragma once

// Custom defines:
#if _DEBUG
// In Debug mode does nothing.
#define T3D_INLINE
#else
// In Release mode inlines the function call.
#define T3D_INLINE inline
#endif

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

// Removes copy constructor and copy assignment operator.
#define T3D_NO_COPY(Class) Class(const Class&) = delete; \
                           Class& operator = (const Class&) = delete

// Removes move constructor and move assignment operator.
#define T3D_NO_MOVE(Class) Class(Class&&) = delete; \
						   Class& operator = (Class&&) = delete

// Defines default copy constructor and copy assignment operator.
#define T3D_DEFAULT_COPY(Class) Class(const Class&) = default; \
                           Class& operator = (const Class&) = default

// Defines default move constructor and move assignment operator.
#define T3D_DEFAULT_MOVE(Class) Class(Class&&) = default; \
						   Class& operator = (Class&&) = default

#define T3D_ENTITY_NULL_HANDLE nullptr;