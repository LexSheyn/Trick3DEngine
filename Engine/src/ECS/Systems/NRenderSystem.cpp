#include "../../PrecompiledHeaders/t3dpch.h"
#include "NRenderSystem.h"

namespace t3d
{
// Constructors and Destructor:

	NRenderSystem::NRenderSystem(FRenderer& Renderer)
		: Renderer(Renderer),
		  GraphicsPipeline(Renderer)
	{
		LOG_TRACE("Created.");
	}

	NRenderSystem::~NRenderSystem()
	{
		LOG_TRACE("Deleted.");
	}


// Functions:

	void NRenderSystem::Render(FScene& Scene)
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

		GraphicsPipeline.UniformBuffers[Renderer.GetFrameIndex()]->WriteToBuffer(&GraphicsPipeline.MeshUniform);
		GraphicsPipeline.UniformBuffers[Renderer.GetFrameIndex()]->Flush();

		for (uint64 i = 0u; i < Scene.EntityList.size(); i++)
		{
		// Transform:

			GraphicsPipeline.MeshConstant.Translation = SEntityComponentSystem::GetComponent<CTransform>(Scene.EntityList[i])->Translation;
			GraphicsPipeline.MeshConstant.Rotation    = SEntityComponentSystem::GetComponent<CTransform>(Scene.EntityList[i])->Rotation;
			GraphicsPipeline.MeshConstant.Scale       = SEntityComponentSystem::GetComponent<CTransform>(Scene.EntityList[i])->Scale;

			vkCmdPushConstants(Renderer.GetCurrentCommandBuffer(), GraphicsPipeline.PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(FMeshPushConstant), &GraphicsPipeline.MeshConstant);

		// Draw command submition:

			SEntityComponentSystem::GetComponent<CModel>(Scene.EntityList[i])->Mesh->Bind(Renderer.GetCurrentCommandBuffer());
			SEntityComponentSystem::GetComponent<CModel>(Scene.EntityList[i])->Mesh->Draw(Renderer.GetCurrentCommandBuffer());
		}
	}


// ISystem Interface:

	void NRenderSystem::Update()
	{
	}


}