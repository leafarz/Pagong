#include "pch.h"
#include "Pagong/Graphics/Api/DX12/DX12Factory.h"
#include "Pagong/Graphics/Api/DX12/DX12Common.h"

namespace Pagong::Graphics::DX12
{
	void DX12Factory::Initialize()
	{
		uint32 dxgiFactoryFlags = 0;
#ifdef _DEBUG
		dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
		DXCHECK(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&m_Factory)));
	}

	void DX12Factory::Shutdown()
	{
		m_Factory->Release();
	}

	Microsoft::WRL::ComPtr<IDXGIFactory4> DX12Factory::GetNativeFactory()
	{
		return m_Factory;
	}
}
