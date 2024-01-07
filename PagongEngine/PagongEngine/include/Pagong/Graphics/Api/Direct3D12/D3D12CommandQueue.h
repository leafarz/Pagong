#pragma once
#include "Pagong/Graphics/CommandQueue.h"

namespace Pagong::Graphics::D3D12
{
	class D3D12Device;
	class D3D12CommandQueue : public CommandQueue
	{
	public:
#pragma region CommandQueue Virtuals
		void Initialize(Device* device, uint32 type) override;
		void Shutdown() override;
		uint64 Execute(TShared<CommandList> commandList) override;
		void ClearQueue() override;
		void WaitForFence() override;
#pragma endregion CommandQueue Virtuals

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetD3D12CommandQueue();

	private:
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> CreateCommandQueue();
		Microsoft::WRL::ComPtr<ID3D12Fence> CreateFence();

	private:
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
		D3D12Device* m_Device;
		D3D12_COMMAND_LIST_TYPE m_Type;


		// Synchronization objects.
		HANDLE m_FenceEvent;
		Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;
		uint64 m_FenceValue;
	};
}
