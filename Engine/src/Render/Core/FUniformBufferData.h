#pragma once

#include "../Primitives/PointLight/FPointLight.h"

namespace t3d
{
#define MAX_LIGHTS 10

	struct FUniformBufferData
	{
		alignas(16) FMat4 ProjectionMatrix {  1.0f };
		alignas(16) FMat4 ViewMatrix       {  1.0f };
		alignas(16) FVec4 AmbientLightColor{  1.0f, 1.0f, 1.0f, 0.02f };  // w is intensity
	//	alignas(16) FVec3 LightPosition    { -1.0f };
	//	alignas(16) FVec4 LightColor       {  1.0f };  // w is light intensity

		FPointLight PointLights[MAX_LIGHTS];
		uint32 NumLights;
	};
}