#include "pch.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Resource.h"

namespace Pagong::Graphics::D3D12
{
	void D3D12Resource::Initialize(ComPtr<ID3D12Resource> resource)
	{
		m_Resource = resource;
	}

	ComPtr<ID3D12Resource> D3D12Resource::GetNativeResource()
	{
		return m_Resource;
	}

	void D3D12Resource::Shutdown()
	{
		m_Resource->Release();
	}
}
