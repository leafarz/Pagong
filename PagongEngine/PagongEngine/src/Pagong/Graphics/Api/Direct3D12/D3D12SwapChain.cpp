#include "pch.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12SwapChain.h"
#include "Pagong/Graphics/Factory.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Common.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Device.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Factory.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Resource.h"

namespace Pagong::Graphics::D3D12
{
    TShared<Resource> D3D12SwapChain::GetCurrentRenderTarget()
    {
        return m_renderTargets[m_FrameIndex];
    }

	void D3D12SwapChain::Initialize(
        Device* device, TShared<CommandQueue> commandQueue, TShared<Factory> factory,
        void* windowHandle, uint32 width, uint32 height)
	{
		m_Device = (D3D12Device*)device;

        HWND hWnd = (HWND)windowHandle;
        TShared<D3D12Factory> d3d12Factory = std::dynamic_pointer_cast<D3D12Factory>(factory);
        TShared<D3D12CommandQueue> d3d12CommandQueue = std::dynamic_pointer_cast<D3D12CommandQueue>(commandQueue);

        m_SwapChain = CreateSwapChain(d3d12Factory, d3d12CommandQueue, G_FRAME_COUNT, hWnd, width, height);

        m_RTVHeap = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, G_FRAME_COUNT);
        m_RTVDescriptorSize = m_Device->GetNativeDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        CreateBuffers();
	}

    void D3D12SwapChain::Shutdown()
    {
        for (uint32 i = 0; i < G_FRAME_COUNT; ++i)
        {
            m_renderTargets[i]->Shutdown();
        }

        m_RTVHeap->Release();
        m_SwapChain->Release();
    }

    void D3D12SwapChain::Present()
    {
        DXCHECK(m_SwapChain->Present(1, 0));
        m_FrameIndex = (m_FrameIndex + 1) % G_FRAME_COUNT;
    }

    D3D12_CPU_DESCRIPTOR_HANDLE D3D12SwapChain::GetRTVHandle()
    {
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_RTVHeap->GetCPUDescriptorHandleForHeapStart();
        rtvHandle.ptr += (size_t)m_FrameIndex * m_RTVDescriptorSize;
        return rtvHandle;
    }

    ComPtr<IDXGISwapChain4> D3D12SwapChain::CreateSwapChain(
        TShared<D3D12Factory> factory, TShared<D3D12CommandQueue> commandQueue,
        uint32 bufferCount, HWND hWnd, uint32 width, uint32 height)
    {
        ComPtr<IDXGISwapChain4> swapChain4;

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = width;
        swapChainDesc.Height = height;
        swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.Stereo = FALSE;
        swapChainDesc.SampleDesc = { 1, 0 };
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = bufferCount;
        swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        swapChainDesc.Flags = 0;

        ComPtr<IDXGISwapChain1> swapChain1;
        const auto& d3d12Factory = factory->GetNativeFactory();
        DXCHECK(d3d12Factory->CreateSwapChainForHwnd(
            commandQueue->GetNativeCommandQueue().Get(),
            hWnd,
            &swapChainDesc,
            nullptr,
            nullptr,
            &swapChain1));

        DXCHECK(swapChain1.As(&swapChain4));

        return swapChain4;
    }

    void D3D12SwapChain::CreateBuffers()
    {
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_RTVHeap->GetCPUDescriptorHandleForHeapStart());
        for (uint32 i = 0; i < G_FRAME_COUNT; ++i)
        {
            ComPtr<ID3D12Resource> d3d12Resource;
            DXCHECK(m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&d3d12Resource)));
            m_Device->GetNativeDevice()->CreateRenderTargetView(d3d12Resource.Get(), nullptr, rtvHandle);
            rtvHandle.Offset(1, m_RTVDescriptorSize);

            wstring name = L"PagongBuffer_" + String::ToWString(i);
            d3d12Resource->SetName(name.c_str());

            TShared<D3D12Resource> createdResource = MakeShared<D3D12Resource>();
            createdResource->Initialize(d3d12Resource);
            m_renderTargets[i] = createdResource;
        }
    }

    ComPtr<ID3D12DescriptorHeap> D3D12SwapChain::CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 numDescriptors)
    {
        ComPtr<ID3D12DescriptorHeap> descriptorHeap;

        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.NumDescriptors = numDescriptors;
        desc.Type = type;

        DXCHECK(m_Device->GetNativeDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descriptorHeap)));

        return descriptorHeap;
    }
}
