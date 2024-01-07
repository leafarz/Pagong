#pragma once
#include "Pagong/Graphics/CommandList.h"

namespace Pagong::Graphics::D3D12
{
	class D3D12Device;
	class D3D12CommandList : public CommandList
	{
	public:
#pragma region CommandList Virtuals
		void Initialize(Device* device) override;
		void Shutdown() override;
		void Reset() override;
		void TransitionBarrier(TShared<Resource> resource, uint32 stateBefore, uint32 stateAfter) override;
		void ClearRenderTargetView(TShared<SwapChain> swapChain, const Math::vec4& color) override;
		void Close() override;
#pragma endregion CommandList Virtuals

		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetD3D12CommandList();

	private:
		void ClearRenderTargetView_Impl(D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle, const float* color);
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CreateCommandList(D3D12_COMMAND_LIST_TYPE type);
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type);


		
	private:
		D3D12Device* m_Device;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_CommandAllocator;
	};
}
