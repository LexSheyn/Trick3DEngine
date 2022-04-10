#pragma once
#include "EShaderType.h"
#include "EShaderOptimizationLevel.h"

namespace t3d
{
	class MShaderManager
	{
	public:

	// Functions:

		static std::string         T3D_CALL LoadGLSL          (const std::string& FilePath);
		static void                T3D_CALL SaveAsSPV         (const std::string& GLSLCode, const std::string& FilePath, EShaderType Kind, EShaderOptimizationLevel OptimizationLevel = EShaderOptimizationLevel::None);
		static std::vector<uint32> T3D_CALL LoadSPV           (const std::string& FilePath);
		static void                T3D_CALL SaveAsAssembly    (const std::string& GLSLCode, const std::string& FilePath, EShaderType Kind, EShaderOptimizationLevel OptimizationLevel = EShaderOptimizationLevel::None);
		static std::vector<uint32> T3D_CALL LoadAssembly      (const std::string& FilePath);
		static std::vector<uint32> T3D_CALL TranslateToSPV    (const std::string& FilePath, EShaderOptimizationLevel OptimizationLevel = EShaderOptimizationLevel::None);

	private:

	// Private Functions:
		
		static std::string         T3D_CALL Preprocess           (const std::string& SourceName, shaderc_shader_kind Kind, const std::string& Source);
		static std::string         T3D_CALL CompileToAssembly    (const std::string& SourceName, shaderc_shader_kind Kind, const std::string& Source, shaderc_optimization_level OptimizationLevel);
		static std::vector<uint32> T3D_CALL CompileToSPV         (const std::string& SourceName, shaderc_shader_kind Kind, const std::string& Source, shaderc_optimization_level OptimizationLevel);

	// Private Constructors and Destructor:

		 MShaderManager() {}
		~MShaderManager() {}

		T3D_NO_COPY(MShaderManager);
		T3D_NO_MOVE(MShaderManager);

	// Variables:

		static shaderc::Compiler Compiler;
	};
}