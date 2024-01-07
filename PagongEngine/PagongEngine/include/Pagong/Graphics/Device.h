#pragma once
#include "Pagong/Core/CoreTypes.h"

namespace Pagong::Graphics
{
	class Device
	{
	public:
		static TUnique<Device> Create(GraphicsApi graphicsApi);

	public:
		virtual void Initialize(uint32 width, uint32 height, void* windowHandle) = 0;
		virtual void Shutdown() = 0;
	};
}
