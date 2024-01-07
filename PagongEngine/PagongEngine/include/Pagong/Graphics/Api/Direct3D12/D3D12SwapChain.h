#pragma once
#include "Pagong/Graphics/SwapChain.h"

namespace Pagong::Graphics::D3D12
{
	class D3D12CommandQueue;
	class D3D12Device;
	class D3D12Factory;
	class D3D12Resource;

	class D3D12SwapChain : public SwapChain
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
			TShared<D3D12Factory> factory, TShared<D3D12CommandQueue> commandQueue,
			uint32 bufferCount, HWND hWnd, uint32 width, uint32 height);
		
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(
			D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 numDescriptors);
		
		void CreateBuffers();

	private:
		D3D12Device* m_Device;
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RTVHeap;
		TShared<D3D12Resource> m_renderTargets[G_FRAME_COUNT];
		uint32 m_RTVDescriptorSize;
		uint32 m_FrameIndex;
	};

}
