#include "pch.h"
#include "Pagong/Graphics/Api/DX12/DX12Resource.h"

namespace Pagong::Graphics::DX12
{
	void DX12Resource::Initialize(ComPtr<ID3D12Resource> resource)
	{
		m_Resource = resource;
	}

	ComPtr<ID3D12Resource> DX12Resource::GetNativeResource()
	{
		return m_Resource;
	}

	void DX12Resource::Shutdown()
	{
		m_Resource->Release();
	}
}
