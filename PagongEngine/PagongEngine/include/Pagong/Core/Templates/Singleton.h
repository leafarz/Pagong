#pragma once
#include "Pagong/Core/CoreTypes.h"

namespace Pagong
{
	template<class T>
	class TSingleton
	{
	public:
		static T& Get()
		{
			static T s_Instance;
			return s_Instance;
		}

		TSingleton(const TSingleton&) = delete;
		TSingleton& operator= (const TSingleton) = delete;

	protected:
		TSingleton() {}
	};
}
