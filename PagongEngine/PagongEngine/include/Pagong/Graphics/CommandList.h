#pragma once

namespace Pagong::Graphics
{
	class Device;
	class Resource;
	class SwapChain;
	class CommandList
	{
	public:
		static TShared<CommandList> Create(GraphicsApi graphicsApi);

	public:
		virtual void Initialize(Device* device) = 0;
		virtual void Shutdown() = 0;
		virtual void Reset() = 0;
		virtual void TransitionBarrier(TShared<Resource> resource, uint32 stateBefore, uint32 stateAfter) = 0;
		virtual void ClearRenderTargetView(TShared<SwapChain> swapChain, const Math::vec4& color) = 0;
		virtual void Close() = 0;
	};
}
