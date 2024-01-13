#pragma once
#include "Pagong/Core/PrimitiveTypes.h"

namespace Pagong::Graphics
{
	class Factory;
	class Device;
	class Adapter
	{
	public:
		static TUnique<Adapter> Create(GraphicsApi graphicsApi);

		virtual void Initialize(TShared<Factory> factory) = 0;
		virtual void Shutdown() = 0;
		virtual const wchar* GetDescription() = 0;
		virtual uint64 GetDedicatedVideoMemory() = 0;
		virtual uint64 GetSharedSystemMemory() = 0;
	};
}
