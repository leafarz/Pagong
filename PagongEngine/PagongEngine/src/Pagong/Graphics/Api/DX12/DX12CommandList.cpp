#include "pch.h"
#include "Pagong/Graphics/Api/DX12/DX12CommandList.h"
#include "Pagong/Graphics/Api/DX12/DX12Common.h"
#include "Pagong/Graphics/Api/DX12/DX12Device.h"
#include "Pagong/Graphics/Api/DX12/DX12Resource.h"
#include "Pagong/Graphics/Api/DX12/DX12SwapChain.h"

namespace Pagong::Graphics::DX12
{
	void DX12CommandList::Initialize(Device* device)
	{
		m_Device = (DX12Device*)device;

		m_CommandAllocator = CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT);
		m_CommandList = CreateCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT);
	}

	void DX12CommandList::Shutdown()
	{
		m_CommandList->Release();
		m_CommandAllocator->Release();
	}

	void DX12CommandList::Reset()
	{
		DXCHECK(m_CommandAllocator->Reset());
		DXCHECK(m_CommandList->Reset(m_CommandAllocator.Get(), 0));
	}

	void DX12CommandList::TransitionBarrier(TShared<Resource> resource, uint32 stateBefore, uint32 stateAfter)
	{
		TShared<DX12Resource> dx12Resource = std::dynamic_pointer_cast<DX12Resource>(resource);
		CD3DX12_RESOURCE_BARRIER resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
			dx12Resource->GetNativeResource().Get(), (D3D12_RESOURCE_STATES)stateBefore, (D3D12_RESOURCE_STATES)stateAfter
		);
		m_CommandList->ResourceBarrier(1, &resourceBarrier);
	}

	void DX12CommandList::ClearRenderTargetView(TShared<SwapChain> swapChain, const Math::vec4& color)
	{
		TShared<DX12SwapChain> dx12SwapChain = std::dynamic_pointer_cast<DX12SwapChain>(swapChain);
		float* pColor = (float*)(&color);
		ClearRenderTargetView_Impl(dx12SwapChain->GetRTVHandle(), pColor);
	}

	void DX12CommandList::Close()
	{
		DXCHECK(m_CommandList->Close());
	}

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> DX12CommandList::GetNativeCommandList()
	{
		return m_CommandList;
	}

	void DX12CommandList::ClearRenderTargetView_Impl(D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle, const float* color)
	{
		m_CommandList->ClearRenderTargetView(descriptorHandle, color, 0, nullptr);
	}

	ComPtr<ID3D12GraphicsCommandList> DX12CommandList::CreateCommandList(D3D12_COMMAND_LIST_TYPE type)
	{
		ComPtr<ID3D12GraphicsCommandList> commandList;
		DXCHECK(m_Device->GetNativeDevice()->CreateCommandList(0, type, m_CommandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));
		DXCHECK(commandList->Close());
		return commandList;
	}

	ComPtr<ID3D12CommandAllocator> DX12CommandList::CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type)
	{
		ComPtr<ID3D12CommandAllocator> commandAllocator;
		DXCHECK(m_Device->GetNativeDevice()->CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator)));
		return commandAllocator;
	}
}
