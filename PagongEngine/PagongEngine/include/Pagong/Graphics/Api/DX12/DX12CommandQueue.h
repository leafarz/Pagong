#pragma once
#include "Pagong/Graphics/CommandQueue.h"

namespace Pagong::Graphics::DX12
{
	class DX12Device;
	class DX12CommandQueue : public CommandQueue
	{
	public:
#pragma region CommandQueue Virtuals
		void Initialize(Device* device, uint32 type) override;
		void Shutdown() override;
		uint64 Execute(TShared<CommandList> commandList) override;
		void ClearQueue() override;
		void WaitForFence() override;
#pragma endregion CommandQueue Virtuals

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetNativeCommandQueue();

	private:
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> CreateCommandQueue();
		Microsoft::WRL::ComPtr<ID3D12Fence> CreateFence();

	private:
		DX12Device* m_Device;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
		D3D12_COMMAND_LIST_TYPE m_Type;


		// Synchronization objects.
		HANDLE m_FenceEvent;
		uint64 m_FenceValue;
		Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;
	};
}
