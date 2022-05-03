#include "../../PCH/t3dpch.h"
#include "FObject.h"

namespace t3d
{
	bool8 FObject::IsEmpty()
	{
		return Instance == nullptr;
	}

}