#pragma once

namespace t3d
{
	template<typename T, typename ArgT>
	struct TEventCallbackRecord
	{
		void* Instance;
		T     Callback;
		ArgT  Data;
	};

//	struct TEventStruct
//	{
//		FEventKey k;
//		void* Instance;
//		FKeyData a;
//	};
//
//	std::vector<TEventStruct> EventStructs;
//
//	void Invoke()
//	{
//		for (auto& Struct : EventStructs)
//		{
//			(*Struct.k) (Struct.Instance, Struct.a);
//		}
//	}
}