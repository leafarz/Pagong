#pragma once

namespace Pagong::Graphics
{
	class Device;
	class CommandList;
	class CommandQueue
	{
	public:
		static TShared<CommandQueue> Create(GraphicsApi graphicsApi);

		virtual void Initialize(Device* device, uint32 type) = 0;
		virtual void Shutdown() = 0;
		virtual uint64 Execute(TShared<CommandList> commandList) = 0;
		virtual void ClearQueue() = 0;
		virtual void WaitForFence() = 0;
	};
}
