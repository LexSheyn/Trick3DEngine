#pragma once

namespace t3d
{
	enum class EShaderOptimization
	{
		// No optimization
		None        = shaderc_optimization_level_zero,

		// Optimize towards reducing code size
		Size        = shaderc_optimization_level_size,

		// Optimize towards performance
		Performance = shaderc_optimization_level_performance
	};
}