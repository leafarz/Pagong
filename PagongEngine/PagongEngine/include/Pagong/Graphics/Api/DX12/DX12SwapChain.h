#pragma once
#include "Pagong/Graphics/SwapChain.h"

namespace Pagong::Graphics::DX12
{
	class DX12CommandQueue;
	class DX12Device;
	class DX12Factory;
	class DX12Resource;

	class DX12SwapChain : public SwapChain
	{

	public:
#pragma region SwapChain Virtuals
		TShared<Resource> GetCurrentRenderTarget() override;
		void Initialize(
			Device* device, TShared<CommandQueue> commandQueue, TShared<Factory> factory,
			void* windowHandle, uint32 width, uint32 height) override;
		void Shutdown() override;
		void Present() override;
#pragma endregion SwapChain Virtuals

		D3D12_CPU_DESCRIPTOR_HANDLE GetRTVHandle();

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain4> CreateSwapChain(
			TShared<DX12Factory> factory, TShared<DX12CommandQueue> commandQueue,
			uint32 bufferCount, HWND hWnd, uint32 width, uint32 height);
		
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(
			D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 numDescriptors);
		
		void CreateBuffers();

	private:
		DX12Device* m_Device;
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RTVHeap;
		TShared<DX12Resource> m_renderTargets[G_FRAME_COUNT];
		uint32 m_RTVDescriptorSize;
		uint32 m_FrameIndex;
	};

}
