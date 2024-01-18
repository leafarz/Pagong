#include "pch.h"
#include "Pagong/Graphics/Api/DX12/DX12SwapChain.h"
#include "Pagong/Graphics/Factory.h"
#include "Pagong/Graphics/Api/DX12/DX12Common.h"
#include "Pagong/Graphics/Api/DX12/DX12Device.h"
#include "Pagong/Graphics/Api/DX12/DX12Factory.h"
#include "Pagong/Graphics/Api/DX12/DX12Resource.h"

namespace Pagong::Graphics::DX12
{
    TShared<Resource> DX12SwapChain::GetCurrentRenderTarget()
    {
        return m_renderTargets[m_FrameIndex];
    }

	void DX12SwapChain::Initialize(
        Device* device, TShared<CommandQueue> commandQueue, TShared<Factory> factory,
        void* windowHandle, uint32 width, uint32 height)
	{
		m_Device = (DX12Device*)device;

        HWND hWnd = (HWND)windowHandle;
        TShared<DX12Factory> dx12Factory = std::dynamic_pointer_cast<DX12Factory>(factory);
        TShared<DX12CommandQueue> dx12CommandQueue = std::dynamic_pointer_cast<DX12CommandQueue>(commandQueue);
        m_SwapChain = CreateSwapChain(dx12Factory, dx12CommandQueue, G_FRAME_COUNT, hWnd, width, height);

        m_RTVHeap = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, G_FRAME_COUNT);
        m_RTVDescriptorSize = m_Device->GetNativeDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        CreateBuffers();
	}

    void DX12SwapChain::Shutdown()
    {
        for (uint32 i = 0; i < G_FRAME_COUNT; ++i)
        {
            m_renderTargets[i]->Shutdown();
        }

        m_RTVHeap->Release();
        m_SwapChain->Release();
    }

    void DX12SwapChain::Present()
    {
        DXCHECK(m_SwapChain->Present(1, 0));
        m_FrameIndex = (m_FrameIndex + 1) % G_FRAME_COUNT;
    }

    D3D12_CPU_DESCRIPTOR_HANDLE DX12SwapChain::GetRTVHandle()
    {
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_RTVHeap->GetCPUDescriptorHandleForHeapStart();
        rtvHandle.ptr += (size_t)m_FrameIndex * m_RTVDescriptorSize;
        return rtvHandle;
    }

    ComPtr<IDXGISwapChain4> DX12SwapChain::CreateSwapChain(
        TShared<DX12Factory> factory, TShared<DX12CommandQueue> commandQueue,
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

    void DX12SwapChain::CreateBuffers()
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

            TShared<DX12Resource> createdResource = MakeShared<DX12Resource>();
            createdResource->Initialize(d3d12Resource);
            m_renderTargets[i] = createdResource;
        }
    }

    ComPtr<ID3D12DescriptorHeap> DX12SwapChain::CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 numDescriptors)
    {
        ComPtr<ID3D12DescriptorHeap> descriptorHeap;

        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.NumDescriptors = numDescriptors;
        desc.Type = type;

        DXCHECK(m_Device->GetNativeDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descriptorHeap)));

        return descriptorHeap;
    }
}
