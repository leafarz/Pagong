#pragma once
#include "Device.h"

namespace Pagong::Graphics
{
	class CommandList;
	class CommandQueue;
	class Factory;
	class SwapChain;

	class PAGONG_API Renderer
	{
	public:
		static TUnique<Renderer> Create(GraphicsApi graphicsApi);

	public:
		Renderer(GraphicsApi graphicsApi);
		void Initialize(uint32 width, uint32 height, void* windowHandle);
		void BeginFrame();
		void EndFrame();
		void Shutdown();

	private:
		GraphicsApi m_Api;
		TUnique<Device> m_Device;
		TShared<CommandList> m_CommandList;
		TShared<CommandQueue> m_CommandQueue;
		TShared<Factory> m_Factory;
		TShared<SwapChain> m_SwapChain;
	};
}
