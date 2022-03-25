#pragma once

namespace t3d
{
	enum class EShaderType
	{
		Geometry = 0,
		TesselationControl,
		TesselationEvaluation,
		Compute,
		Fragment,
		Vertex,
		SIZE
	};
}