#pragma once

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

// GLFW and Vulkan:
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>

// GLM (Graphics Library Math)
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/constants.hpp>
#include <GLM/gtx/hash.hpp>

// FMOD
#include <FMOD/fmod.hpp>

// ShaderC:
#pragma warning( disable : 26439 ) // Warning C26439: This kind of function may not throw. Declare it 'noexcept' (f.6).

#include <shaderc/shaderc.hpp>

#pragma warning( pop ) // Vulkan SDK - End

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// C++ core:
#include <iostream>
#include <sstream>
//#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <chrono>
//#include <map>
#include <unordered_map>
//#include <set>
#include <unordered_set>
#include <algorithm>
//#include <vector>
#include <list>
#include <deque>
#include <random>
#include <numeric>
#include <new>
//#include <utility>
#include <tuple>
#include <typeinfo>
#include <functional>

// STB Image:
#include <stdarg.h>
#include <stddef.h> // ptrdiff_t on osx
#include <stdlib.h>
//#include <string.h>
//#include <limits.h>
#include <math.h>  // ldexp, pow
#include <stdio.h>
#include <assert.h>

// Tiny OBJ Loader:
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <limits>
#include <set>
#include <sstream>
#include <utility>

#undef CreateEvent
#undef LoadImage
#undef LoadImageW
#undef GetMessage
#undef GetMessageW

// Custom types:
#include "../Types/T3DTypes.h"
#include "../Types/ECSTypes.h"

// Custom defines:
#include "../Macros/T3DMacros.h"

//#ifndef DISABLE_WINDOWS
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
//#endif // DISABLE_WINDOWS