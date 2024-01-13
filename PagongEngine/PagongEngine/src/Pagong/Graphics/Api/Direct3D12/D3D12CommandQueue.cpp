#include "pch.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12CommandQueue.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Common.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12CommandList.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Device.h"

namespace Pagong::Graphics::D3D12
{
	void D3D12CommandQueue::Initialize(Device* device, uint32 type)
	{
        m_Device = (D3D12Device*)device;
        m_Type = (D3D12_COMMAND_LIST_TYPE)type;
        m_Fence = CreateFence();
        m_CommandQueue = CreateCommandQueue();
	}

    void D3D12CommandQueue::Shutdown()
    {
        ClearQueue();
        m_Fence->Release();
        m_CommandQueue->Release();
    }

    uint64 D3D12CommandQueue::Execute(TShared<CommandList> commandList)
    {
        TShared<D3D12CommandList> d3d12CommandList = std::dynamic_pointer_cast<D3D12CommandList>(commandList);
        m_CommandQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)d3d12CommandList->GetNativeCommandList().GetAddressOf());
        m_CommandQueue->Signal(m_Fence.Get(), m_FenceValue);
        return m_FenceValue;
    }

    void D3D12CommandQueue::ClearQueue()
    {
        for (uint32 i = 0; i < G_FRAME_COUNT; ++i)
        {
            m_CommandQueue->Signal(m_Fence.Get(), m_FenceValue + i);
        }
    }

    void D3D12CommandQueue::WaitForFence()
    {
        if (m_Fence->GetCompletedValue() < m_FenceValue)
        {
            DXCHECK(m_Fence->SetEventOnCompletion(m_FenceValue, m_FenceEvent));
            WaitForSingleObject(m_FenceEvent, INFINITE);
        }
        ++m_FenceValue;
    }

    Microsoft::WRL::ComPtr<ID3D12CommandQueue> D3D12CommandQueue::GetNativeCommandQueue()
    {
        return m_CommandQueue;
    }

    Microsoft::WRL::ComPtr<ID3D12CommandQueue> D3D12CommandQueue::CreateCommandQueue()
    {
        ComPtr<ID3D12CommandQueue> d3d12CommandQueue;

        D3D12_COMMAND_QUEUE_DESC desc;
        desc.Type = m_Type;
        desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
        desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        desc.NodeMask = 0;

        DXCHECK(m_Device->GetNativeDevice()->CreateCommandQueue(&desc, IID_PPV_ARGS(&d3d12CommandQueue)));

        switch (m_Type)
        {
        case D3D12_COMMAND_LIST_TYPE_COPY:
            d3d12CommandQueue->SetName(L"Copy Command Queue");
            break;
        case D3D12_COMMAND_LIST_TYPE_COMPUTE:
            d3d12CommandQueue->SetName(L"Compute Command Queue");
            break;
        case D3D12_COMMAND_LIST_TYPE_DIRECT:
            d3d12CommandQueue->SetName(L"Direct Command Queue");
            break;
        }

        return d3d12CommandQueue;
    }

    ComPtr<ID3D12Fence> D3D12CommandQueue::CreateFence()
    {
        ComPtr<ID3D12Fence> fence;
        DXCHECK(m_Device->GetNativeDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));
        return fence;
    }
}
