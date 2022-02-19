#include "../PrecompiledHeaders/t3dpch.h"
#include "CMovementComponent.h"

namespace t3d
{
// Functions:

	void CMovementComponent::MoveInPlaneXZ(FWindow& Window, OGameObject& GameObject, const float32& DeltaTime)
	{
		glm::vec3 Rotation{0.0f};

		if (FKeyboard::IsKeyPressed(FKey::Right)) { Rotation.y += 1.0f; }
		if (FKeyboard::IsKeyPressed(FKey::Left) ) { Rotation.y -= 1.0f; }
		if (FKeyboard::IsKeyPressed(FKey::Up)   ) { Rotation.x += 1.0f; }
		if (FKeyboard::IsKeyPressed(FKey::Down) ) { Rotation.x -= 1.0f; }

		// Temporary hardcoded implementation:
	//	if (FMouse::GetX() >= Window.GetWidth() - 1 ) { Rotation.y += 1.0f; }
	//	if (FMouse::GetX() <=   0.0f                ) { Rotation.y -= 1.0f; }
	//	if (FMouse::GetY() >= Window.GetHeight()    ) { Rotation.x -= 1.0f; }
	//	if (FMouse::GetY() <=   0.0f                ) { Rotation.x += 1.0f; }

		if (Rotation != glm::vec3(0.0f))
		{
			GameObject.GetTransform().Rotate( TurnSpeed * DeltaTime * glm::normalize(Rotation) ); //+= TurnSpeed * DeltaTime * glm::normalize(Rotation);
		}

		// Limit pitch value between about +/- 85ish degrees.
	//	GameObject.Transform.Rotation.x = glm::clamp(GameObject.Transform.Rotation.x, -1.5f, 1.5f);
	//	GameObject.Transform.Rotation.y = glm::mod(GameObject.Transform.Rotation.y, glm::two_pi<float32>());

		GameObject.GetTransform().SetRotation({ glm::clamp(GameObject.GetTransform().GetRotation().x, -1.5f, 1.5f),
			                                    glm::mod(GameObject.GetTransform().GetRotation().y, glm::two_pi<float32>()), 0.0f });

		float32 Yaw = GameObject.GetTransform().GetRotation().y;

		const glm::vec3 ForwardDirection{glm::sin(Yaw), 0.0f, glm::cos(Yaw)};
		const glm::vec3 RightDirection{ForwardDirection.z, 0.0f, -ForwardDirection.x};
		const glm::vec3 UpDirection{0.0f, -1.0f, 0.0f};

		glm::vec3 MoveDirection{0.0f};

		if (FKeyboard::IsKeyPressed(FKey::W)) { MoveDirection += ForwardDirection; }
		if (FKeyboard::IsKeyPressed(FKey::S)) { MoveDirection -= ForwardDirection; }
		if (FKeyboard::IsKeyPressed(FKey::D)) { MoveDirection += RightDirection;   }
		if (FKeyboard::IsKeyPressed(FKey::A)) { MoveDirection -= RightDirection;   }
		if (FKeyboard::IsKeyPressed(FKey::E)) { MoveDirection += UpDirection;      }
		if (FKeyboard::IsKeyPressed(FKey::Q)) { MoveDirection -= UpDirection;      }

		if (MoveDirection != glm::vec3(0.0f))
		{
			GameObject.GetTransform().Translate( MoveSpeed * DeltaTime * glm::normalize(MoveDirection) ); //+= MoveSpeed * DeltaTime * glm::normalize(MoveDirection);
		}
	}

	void CMovementComponent::Move(FWindow& Window, OGameObject& Object, const float32& DeltaTime)
	{
//	// Key bindings would be moved out there!
//
//		glm::vec3 Rotation{0.0f};
//
//		// Temporary hardcoded implementation:
//		if (FMouse::GetX() >= Window.GetWidth() - 1 ) { Rotation.y += 1.0f; }
//		if (FMouse::GetX() <=   0.0f                ) { Rotation.y -= 1.0f; }
//		if (FMouse::GetY() >= Window.GetHeight()    ) { Rotation.x -= 1.0f; }
//		if (FMouse::GetY() <=   0.0f                ) { Rotation.x += 1.0f; }
//
//		if (Rotation != glm::vec3(0.0f))
//		{
//			Object.Transform.Rotation += TurnSpeed * DeltaTime * glm::normalize(Rotation);
//		}
//
//		// Limit pitch value between about +/- 85ish degrees.
//		Object.Transform.Rotation.x = glm::clamp(Object.Transform.Rotation.x, -1.5f, 1.5f);
//		Object.Transform.Rotation.y = glm::mod(Object.Transform.Rotation.y, glm::two_pi<float32>());
//
//		float32 Yaw = Object.Transform.Rotation.y;
//
//		const glm::vec3 ForwardDirection{glm::sin(Yaw), 0.0f, glm::cos(Yaw)};
//		const glm::vec3 RightDirection{ForwardDirection.z, 0.0f, -ForwardDirection.x};
//		const glm::vec3 UpDirection{0.0f, -1.0f, 0.0f};
//
//		glm::vec3 MoveDirection{0.0f};
//
//		if (FKeyboard::IsKeyPressed(Keys.MoveForward) ) { MoveDirection += ForwardDirection; }
//		if (FKeyboard::IsKeyPressed(Keys.MoveBackward)) { MoveDirection -= ForwardDirection; }
//		if (FKeyboard::IsKeyPressed(Keys.MoveRight)   ) { MoveDirection += RightDirection;   }
//		if (FKeyboard::IsKeyPressed(Keys.MoveLeft)    ) { MoveDirection -= RightDirection;   }
//		if (FKeyboard::IsKeyPressed(Keys.MoveUp)      ) { MoveDirection += UpDirection;      }
//		if (FKeyboard::IsKeyPressed(Keys.MoveDown)    ) { MoveDirection -= UpDirection;      }
//
//		if (MoveDirection != glm::vec3(0.0f))
//		{
//			Object.Transform.Translation += MoveSpeed * DeltaTime * glm::normalize(MoveDirection);
//		}
	}
}