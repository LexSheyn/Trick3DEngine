#pragma once

namespace std
{
	template<typename T>
	class stupid_ptr
	{
	public:

		stupid_ptr() : Pointer(nullptr)
		{
		}

		stupid_ptr(T* Pointer) : Pointer(Pointer)
		{
		}

			  T* get()       { return Pointer; }

		const T* get() const { return Pointer; }

	private:

		T* Pointer;
	};

	template<class T, typename... Types>
	[[nodiscard]] stupid_ptr<T> make_stupid(Types&&... Args)
	{
		return stupid_ptr<T>(new T(static_cast<Types&&>(Args)...));
	//	return stupid_ptr<T>(new T(Args...));
	}

	template<class T>
	void delete_stupid(T& Pointer)
	{
		delete Pointer.get();
	}
}