#include "pch.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12CommandList.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Common.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Device.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Resource.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12SwapChain.h"

namespace Pagong::Graphics::D3D12
{
	void D3D12CommandList::Initialize(Device* device)
	{
		m_Device = (D3D12Device*)device;

		m_CommandAllocator = CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT);
		m_CommandList = CreateCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT);
	}

	void D3D12CommandList::Shutdown()
	{
		m_CommandList->Release();
		m_CommandAllocator->Release();
	}

	void D3D12CommandList::Reset()
	{
		DXCHECK(m_CommandAllocator->Reset());
		DXCHECK(m_CommandList->Reset(m_CommandAllocator.Get(), 0));
	}

	void D3D12CommandList::TransitionBarrier(TShared<Resource> resource, uint32 stateBefore, uint32 stateAfter)
	{
		TShared<D3D12Resource> d3d12Resource = std::dynamic_pointer_cast<D3D12Resource>(resource);
		CD3DX12_RESOURCE_BARRIER resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
			d3d12Resource->GetD3D12Resource().Get(), (D3D12_RESOURCE_STATES)stateBefore, (D3D12_RESOURCE_STATES)stateAfter
		);
		m_CommandList->ResourceBarrier(1, &resourceBarrier);
	}

	void D3D12CommandList::ClearRenderTargetView(TShared<SwapChain> swapChain, const Math::vec4& color)
	{
		TShared<D3D12SwapChain> d3d12SwapChain = std::dynamic_pointer_cast<D3D12SwapChain>(swapChain);
		float* pColor = (float*)(&color);
		ClearRenderTargetView_Impl(d3d12SwapChain->GetRTVHandle(), pColor);
	}

	void D3D12CommandList::Close()
	{
		DXCHECK(m_CommandList->Close());
	}

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> D3D12CommandList::GetD3D12CommandList()
	{
		return m_CommandList;
	}

	void D3D12CommandList::ClearRenderTargetView_Impl(D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle, const float* color)
	{
		m_CommandList->ClearRenderTargetView(descriptorHandle, color, 0, nullptr);
	}

	ComPtr<ID3D12GraphicsCommandList> D3D12CommandList::CreateCommandList(D3D12_COMMAND_LIST_TYPE type)
	{
		ComPtr<ID3D12GraphicsCommandList> commandList;
		DXCHECK(m_Device->GetD3D12Device()->CreateCommandList(0, type, m_CommandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));
		DXCHECK(commandList->Close());
		return commandList;
	}

	ComPtr<ID3D12CommandAllocator> D3D12CommandList::CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type)
	{
		ComPtr<ID3D12CommandAllocator> commandAllocator;
		DXCHECK(m_Device->GetD3D12Device()->CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator)));
		return commandAllocator;
	}
}
