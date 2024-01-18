#include "pch.h"
#include "Pagong/Graphics/Api/DX12/DX12Common.h"
#include "Pagong/Graphics/Api/DX12/DX12Debug.h"

namespace Pagong::Graphics::DX12
{
	void DX12Debug::Initialize()
	{
		EnableDebugLayer();
		EnableLeakTrackingForThread();
	}

	void DX12Debug::Shutdown()
	{
		ReportLiveObjects();
	}

	void DX12Debug::EnableDebugLayer()
	{
#ifdef _DEBUG
		ComPtr<ID3D12Debug6> debugController;
		DXCHECK(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
#endif
	}

	void DX12Debug::EnableLeakTrackingForThread()
	{
#ifdef _DEBUG
		ComPtr<IDXGIDebug1> dxgiDebug;
		DXCHECK(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug)));
		dxgiDebug->EnableLeakTrackingForThread();
#endif
	}

	void DX12Debug::ReportLiveObjects()
	{
#ifdef _DEBUG
		ComPtr<IDXGIDebug1> dxgiDebug;
		DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug));
		dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_IGNORE_INTERNAL);
		dxgiDebug->Release();
#endif
	}
}
