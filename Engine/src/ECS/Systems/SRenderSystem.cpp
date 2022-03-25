#include "../../PrecompiledHeaders/t3dpch.h"
#include "SRenderSystem.h"

namespace t3d
{
// Constructors and Destructor:

	SRenderSystem::SRenderSystem(FRenderer& Renderer)
		: Renderer(Renderer),
		  GraphicsPipeline(Renderer)
	{
		LOG_TRACE("Created.");
	}

	SRenderSystem::~SRenderSystem()
	{
		LOG_TRACE("Deleted.");
	}


// Functions:

	void SRenderSystem::Render(FScene& Scene)
	{
	// Binding Graphics Pipeline:

		GraphicsPipeline.Bind(Renderer.GetCurrentCommandBuffer());

	// Camera:

		GraphicsPipeline.MeshUniform.CameraProjection  = Scene.TestCamera.GetProjection();
		GraphicsPipeline.MeshUniform.CameraView        = Scene.TestCamera.GetView();

	// Directional Light:

		GraphicsPipeline.MeshUniform.LightDirection = SEntityComponentSystem::GetComponent<CDirectionalLight>(Scene.LightSource)->Direction;
		GraphicsPipeline.MeshUniform.LightAmbient   = SEntityComponentSystem::GetComponent<CDirectionalLight>(Scene.LightSource)->Ambient;

	// Uniform submition:

		GraphicsPipeline.SubmitUniforms();

		for (uint64 i = 0u; i < Scene.EntityList.size(); i++)
		{
		// Transform:

			GraphicsPipeline.MeshConstant.Translation = SEntityComponentSystem::GetComponent<CTransform>(Scene.EntityList[i])->Translation;
			GraphicsPipeline.MeshConstant.Rotation    = SEntityComponentSystem::GetComponent<CTransform>(Scene.EntityList[i])->Rotation;
			GraphicsPipeline.MeshConstant.Scale       = SEntityComponentSystem::GetComponent<CTransform>(Scene.EntityList[i])->Scale;

			GraphicsPipeline.PushConstants();

		// Draw command submition:

			SEntityComponentSystem::GetComponent<CModel>(Scene.EntityList[i])->Mesh->Bind(Renderer.GetCurrentCommandBuffer());
			SEntityComponentSystem::GetComponent<CModel>(Scene.EntityList[i])->Mesh->Draw(Renderer.GetCurrentCommandBuffer());
		}
	}


// ISystem Interface:

	void SRenderSystem::Update()
	{
		// Access Scene somehow
		// Submit uniforms and oush constants here		
		// To do...
		LOG_TRACE("FPS: " + std::to_string( static_cast<uint64>(1.0f / FDeltaTime::Get()) ));
	}


}