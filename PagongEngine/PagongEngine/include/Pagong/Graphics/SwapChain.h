#pragma once

namespace Pagong::Graphics
{
	class Resource;
	class SwapChain
	{
	public:
		static TShared<SwapChain> Create(GraphicsApi graphicsApi);

		virtual TShared<Resource> GetCurrentRenderTarget() = 0;

		virtual void Initialize(
			Device* device, TShared<CommandQueue> commandQueue, TShared<Factory> factory,
			void* windowHandle, uint32 width, uint32 height) = 0;

		virtual void Shutdown() = 0;

		virtual void Present() = 0;
	};
}