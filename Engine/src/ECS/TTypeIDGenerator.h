#pragma once

namespace t3d
{
/////////////////////////////////////////////////////////////////
// Type definitions ////////////////////////////////////////Begin
/////////////////////////////////////////////////////////////////

	typedef uint64 T3D_IDType;
	typedef T3D_IDType T3D_EntityID;
	typedef T3D_IDType T3D_ComponentTypeID;

	typedef std::vector<T3D_ComponentTypeID> T3D_ArchetypeID;

	constexpr T3D_IDType NULL_ENTITY = 0;

/////////////////////////////////////////////////////////////////
// Type definitions //////////////////////////////////////////End
/////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////
// TTypeIDGenenrator ///////////////////////////////////////Begin
/////////////////////////////////////////////////////////////////

	template<class T>
	class TTypeIDGenerator
	{
	public:

		template<class U>
		static const T3D_IDType GetNewID()
		{
			static const T3D_IDType IDCounter = Count++;
			return IDCounter;
		};

	private:

		static T3D_IDType Count;
	};

	template<class T> T3D_IDType TTypeIDGenerator<T>::Count = 0;

/////////////////////////////////////////////////////////////////
// TTypeIDGenenrator /////////////////////////////////////////End
/////////////////////////////////////////////////////////////////
}