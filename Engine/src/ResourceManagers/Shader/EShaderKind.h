#pragma once

namespace t3d
{
	enum class EShaderKind
	{
		Geometry              = shaderc_glsl_geometry_shader,
		TesselationControl    = shaderc_glsl_tess_control_shader,
		TesselationEvaluation = shaderc_glsl_tess_evaluation_shader,
		Compute               = shaderc_glsl_compute_shader,
		Fragment              = shaderc_glsl_fragment_shader,
		Vertex                = shaderc_glsl_vertex_shader
	};
}