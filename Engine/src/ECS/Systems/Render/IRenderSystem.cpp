#include "../../../PrecompiledHeaders/t3dpch.h"
#include "IRenderSystem.h"

namespace t3d
{
// Constructors and Destructor:

	IRenderSystem::IRenderSystem(FRenderer& Renderer)
		: Renderer(Renderer)
	{
		this->Initialize();

		LOG_TRACE("Created.");
	}

	IRenderSystem::~IRenderSystem()
	{
		delete DescriptorPool;

		delete DescriptorSetLayout;

		delete Pipeline;

		vkDestroyPipelineLayout(Renderer.GetDevice().Device(), PipelineLayout, nullptr);

		LOG_TRACE("Deleted.");
	}


// Functions:

	const FMat4& IRenderSystem::ToMatrix4x4(CTransform* Transform)
	{
		Sin1 = glm::sin(Transform->Rotation.z);
		Cos1 = glm::cos(Transform->Rotation.z);

		Sin2 = glm::sin(Transform->Rotation.y);
		Cos2 = glm::cos(Transform->Rotation.y);
		
		Sin3 = glm::sin(Transform->Rotation.x);
		Cos3 = glm::cos(Transform->Rotation.x);

		TransformationMatrix =
		{
			// Basis X:
			{
				Transform->Scale.x * (  Cos1 * Cos2 ),
				Transform->Scale.x * (  Cos2 * Sin1 ),
				Transform->Scale.x * ( -Sin2 ),
				0.0f
			},

			// Basis Y:
			{
				Transform->Scale.y * ( (Cos1 * Sin2 * Sin3) - (Cos2 * Sin1) ),
				Transform->Scale.y * ( (Cos1 * Cos3) + (Sin1 * Sin2 * Sin3) ),
				Transform->Scale.y * ( Cos2 * Sin3 ),
				0.0f
			},
			
			// Basis Z:
			{
				Transform->Scale.z * ( (Sin1 * Sin3) + (Cos1 * Cos3 * Sin2) ),
				Transform->Scale.z * ( (Cos3 * Sin1 * Sin2) - (Cos1 * Sin3) ),
				Transform->Scale.z * ( Cos2 * Cos3 ),
				0.0f
			},
			
			// Basis W sneaky abused for translation.
			{
				Transform->Translation.x,
				Transform->Translation.y,
				Transform->Translation.z,
				1.0f
			}
		};

		return TransformationMatrix;
	}


// Private Functions:

	void IRenderSystem::Initialize()
	{
		PipelineLayout = nullptr;

		Pipeline = nullptr;

		for (uint64 i = 0u; i < DescriptorSets.Size(); i++)
		{
			DescriptorSets[i] = nullptr;
		}

		DescriptorSetLayout = nullptr;

		DescriptorPool = nullptr;
	}

}