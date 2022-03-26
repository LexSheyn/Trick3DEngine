#include "../../PrecompiledHeaders/t3dpch.h"
#include "MShaderManager.h"

// Disable warnings from shaderc:
#pragma warning( push ) // shaderc - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Functions:

	std::string MShaderManager::LoadGLSL(const std::string& FilePath)
	{
		std::string Line;
		Line.reserve(100);

		std::string ShaderCode;
		ShaderCode.reserve(10'000);

		std::ifstream InFile;

		InFile.open(FilePath);

		if (!InFile.is_open())
		{
			LOG_ERROR("Failed to open: " + FilePath);
			throw;
		}

		while (std::getline(InFile, Line))
		{
			ShaderCode += Line + "\n";
		}

		InFile.close();

		return ShaderCode;
	}

	void MShaderManager::SaveAsSPV(const std::string& GLSLCode, const std::string& FilePath, EShaderKind Kind, EShaderOptimizationLevel OptimizationLevel)
	{
		std::vector<uint32> SPVData;

		SPVData = CompileToSPV("FileName", static_cast<shaderc_shader_kind>(Kind), GLSLCode, static_cast<shaderc_optimization_level>(OptimizationLevel));

		std::ofstream OutFile;

		OutFile.open(FilePath, std::ios_base::out);

		for (auto Data : SPVData)
		{
			OutFile << Data << "\n";
		}

		OutFile.close();
	}

	std::vector<uint32> MShaderManager::LoadSPV(const std::string& FilePath)
	{
		uint32 CodeFragment = 0u;

		std::vector<uint32> SPVData;
		SPVData.reserve(100'000);

		std::ifstream InFile;

		InFile.open(FilePath);

		if (!InFile.is_open())
		{
			LOG_ERROR("Failed to open: " + FilePath);
			throw;
		}

		while (InFile >> CodeFragment)
		{
			SPVData.push_back(CodeFragment);
		}

		InFile.close();

		return SPVData;
	}

	void MShaderManager::SaveAsAssembly(const std::string& GLSLCode, const std::string& FilePath, EShaderKind Kind, EShaderOptimizationLevel OptimizationLevel)
	{
		std::string SPVAssembly;

		SPVAssembly = CompileToAssembly("", static_cast<shaderc_shader_kind>(Kind), GLSLCode, static_cast<shaderc_optimization_level>(OptimizationLevel));

		std::ofstream OutFile;

		OutFile.open(FilePath, std::ios_base::out);

		OutFile << SPVAssembly;

		OutFile.close();
	}

	std::vector<uint32> MShaderManager::LoadAssembly(const std::string& FilePath)
	{
		std::string SPVAssembly;

		std::string Line;

		std::ifstream InFile;

		InFile.open(FilePath);

		while (std::getline(InFile, Line))
		{
			SPVAssembly += Line + "\n";
		}

		InFile.close();

		shaderc::CompileOptions Options;

		Options.AddMacroDefinition("MY_DEFINE", "1");

		Options.SetOptimizationLevel(shaderc_optimization_level_zero);

		shaderc::SpvCompilationResult Result = Compiler.AssembleToSpv(SPVAssembly, Options);

		if (Result.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			// Rework FLogger to handle this.
			std::cerr << Result.GetErrorMessage();
			throw;
		}

		return { Result.cbegin(), Result.cend() };
	}


// Private Functions:

	std::string MShaderManager::Preprocess(const std::string& SourceName, shaderc_shader_kind Kind, const std::string& Source)
	{
		shaderc::CompileOptions Options;

		Options.AddMacroDefinition("MY_DEFINE", "1"); // WHAT IS THAT???

		shaderc::PreprocessedSourceCompilationResult Result = Compiler.PreprocessGlsl(Source, Kind, SourceName.c_str(), Options);

		if (Result.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			// Rework FLogger to handle this.
			std::cerr << Result.GetErrorMessage();
			throw;
		}

		return { Result.cbegin(), Result.cend() };
	}

	std::string MShaderManager::CompileToAssembly(const std::string& SourceName, shaderc_shader_kind Kind, const std::string& Source, shaderc_optimization_level OptimizationLevel)
	{
		shaderc::CompileOptions Options;

		Options.AddMacroDefinition("MY_DEFINE", "1"); // WHAT IS THAT???

		Options.SetOptimizationLevel(OptimizationLevel);

		shaderc::AssemblyCompilationResult Result = Compiler.CompileGlslToSpvAssembly(Source, Kind, SourceName.c_str(), Options);

		if (Result.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			// Rework FLogger to handle this.
			std::cerr << Result.GetErrorMessage();
			throw;
		}

		return { Result.cbegin(), Result.cend() };
	}

	std::vector<uint32> MShaderManager::CompileToSPV(const std::string& SourceName, shaderc_shader_kind Kind, const std::string& Source, shaderc_optimization_level OptimizationLevel)
	{
		shaderc::CompileOptions Options;

		Options.AddMacroDefinition("MY_DEFINE", "1");

		Options.SetOptimizationLevel(OptimizationLevel);

		shaderc::SpvCompilationResult Result = Compiler.CompileGlslToSpv(Source, Kind, SourceName.c_str(), Options);

		if (Result.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			// Rework FLogger to handle this.
			std::cerr << Result.GetErrorMessage();
			throw;
		}

		return { Result.cbegin(), Result.cend() };
	}


// Static Variables:

	shaderc::Compiler MShaderManager::Compiler;

}

#pragma warning( pop ) // shaderc - End