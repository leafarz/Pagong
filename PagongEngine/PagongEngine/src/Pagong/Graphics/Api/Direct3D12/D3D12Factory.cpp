#include "pch.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Factory.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Common.h"

namespace Pagong::Graphics::D3D12
{
	void D3D12Factory::Initialize()
	{
		uint32 dxgiFactoryFlags = 0;
#ifdef _DEBUG
		dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
		DXCHECK(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&m_Factory)));
	}

	void D3D12Factory::Shutdown()
	{
		m_Factory->Release();
	}

	Microsoft::WRL::ComPtr<IDXGIFactory4> D3D12Factory::GetD3D12Factory()
	{
		return m_Factory;
	}
}
