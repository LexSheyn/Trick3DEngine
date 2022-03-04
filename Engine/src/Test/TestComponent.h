#pragma once

#include "ECSComponent.h"

namespace t3d
{
	struct TestComponent : public ECSComponent<struct TestComponent>
	{
		float32 X = 0.0f;
		float32 Y = 0.0f;
	};

	struct TestComponent1 : public ECSComponent<struct TestComponent1>
	{
		int64 I = 0;
	};

	struct TestComponent2 : public ECSComponent<struct TestComponent2>
	{
		std::string S;
	};
}