#include "pch.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Common.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Debug.h"

namespace Pagong::Graphics::D3D12
{
	void D3D12Debug::Initialize()
	{
		EnableDebugLayer();
		EnableLeakTrackingForThread();
	}

	void D3D12Debug::Shutdown()
	{
		ReportLiveObjects();
	}

	void D3D12Debug::EnableDebugLayer()
	{
#ifdef _DEBUG
		ComPtr<ID3D12Debug6> debugController;
		DXCHECK(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
#endif
	}

	void D3D12Debug::EnableLeakTrackingForThread()
	{
#ifdef _DEBUG
		ComPtr<IDXGIDebug1> dxgiDebug;
		DXCHECK(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug)));
		dxgiDebug->EnableLeakTrackingForThread();
#endif
	}

	void D3D12Debug::ReportLiveObjects()
	{
#ifdef _DEBUG
		ComPtr<IDXGIDebug1> dxgiDebug;
		DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug));
		dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_IGNORE_INTERNAL);
		dxgiDebug->Release();
#endif
	}
}
