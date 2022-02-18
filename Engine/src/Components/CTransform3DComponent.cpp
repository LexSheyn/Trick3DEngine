#include "../PrecompiledHeaders/t3dpch.h"
#include "CTransform3DComponent.h"

namespace t3d
{
// Functions:

	glm::mat4 CTransform3DComponent::Mat4()
    {
        const float32 Sin1 = glm::sin(Rotation.y);
        const float32 Cos1 = glm::cos(Rotation.y);

        const float32 Sin2 = glm::sin(Rotation.x);
        const float32 Cos2 = glm::cos(Rotation.x);

        const float32 Sin3 = glm::sin(Rotation.z);
        const float32 Cos3 = glm::cos(Rotation.z);

        return glm::mat4
        {
            {
                Scale.x * (Cos1 * Cos3 + Sin1 * Sin2 * Sin3),
                Scale.x * (Cos2 * Sin3),
                Scale.x * (Cos1 * Sin2 * Sin3 - Cos3 * Sin1),
                0.0f,
            },

            {
                Scale.y * (Cos3 * Sin1 * Sin2 - Cos1 * Sin3),
                Scale.y * (Cos2 * Cos3),
                Scale.y * (Cos1 * Cos3 * Sin2 + Sin1 * Sin3),
                0.0f,
            },

            {
                Scale.z * (Cos2 * Sin1),
                Scale.z * (-Sin2),
                Scale.z * (Cos1 * Cos2),
                0.0f,
            },

            { Translation.x, Translation.y, Translation.z, 1.0f }
        };
    }

    glm::mat3 CTransform3DComponent::NormalMatrix()
    {
        const float32 Sin1 = glm::sin(Rotation.y);
        const float32 Cos1 = glm::cos(Rotation.y);

        const float32 Sin2 = glm::sin(Rotation.x);
        const float32 Cos2 = glm::cos(Rotation.x);

        const float32 Sin3 = glm::sin(Rotation.z);
        const float32 Cos3 = glm::cos(Rotation.z);

        const glm::vec3 InverseScale = 1.0f / Scale;

        return glm::mat3
        {
            {
                InverseScale.x * (Cos1 * Cos3 + Sin1 * Sin2 * Sin3),
                InverseScale.x * (Cos2 * Sin3),
                InverseScale.x * (Cos1 * Sin2 * Sin3 - Cos3 * Sin1)
            },

            {
                InverseScale.y * (Cos3 * Sin1 * Sin2 - Cos1 * Sin3),
                InverseScale.y * (Cos2 * Cos3),
                InverseScale.y * (Cos1 * Cos3 * Sin2 + Sin1 * Sin3)
            },

            {
                InverseScale.z * (Cos2 * Sin1),
                InverseScale.z * (-Sin2),
                InverseScale.z * (Cos1 * Cos2)
            }
        };
    }

    void CTransform3DComponent::Translate(const glm::vec3& Translation)
    {
        this->Translation += Translation;
    }

    void CTransform3DComponent::Upscale(const glm::vec3& Scale)
    {
        this->Scale += Scale;
    }

    void CTransform3DComponent::Rotate(const glm::vec3& Rotation)
    {
        this->Rotation += Rotation;
    }


// Modifiers:

    void CTransform3DComponent::SetTranslation(const glm::vec3& Translation)
    {
        this->Translation = Translation;
    }

    void CTransform3DComponent::SetScale(const glm::vec3& Scale)
    {
        this->Scale = Scale;
    }

    void CTransform3DComponent::SetRotation(const glm::vec3& Rotation)
    {
        this->Rotation = Rotation;
    }

}