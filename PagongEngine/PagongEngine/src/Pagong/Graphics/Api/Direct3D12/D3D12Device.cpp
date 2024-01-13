#include "pch.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Device.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Common.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Adapter.h"

namespace Pagong::Graphics::D3D12
{
    D3D12Device::D3D12Device()
        : m_WindowHandle(nullptr), m_Width(0), m_Height(0)
    { }

	void D3D12Device::Initialize(Adapter* adapter, uint32 width, uint32 height, void* windowHandle)
	{
        D3D12Adapter* d3d12Adapter = (D3D12Adapter*)(adapter);
        m_Width = width;
        m_Height = height;
        m_WindowHandle = (HWND)windowHandle;
        
        m_Device = CreateDevice(d3d12Adapter->GetNativeAdapter());
        m_Device->SetName(L"PagongDevice");
	}

    void D3D12Device::Shutdown()
    {
        m_Device->Release();
    }

    Microsoft::WRL::ComPtr<ID3D12Device2> D3D12Device::GetNativeDevice()
    {
        return m_Device;
    }

    ComPtr<ID3D12Device2> D3D12Device::CreateDevice(ComPtr<IDXGIAdapter1> adapter)
    {
        ComPtr<ID3D12Device2> device;
        DXCHECK(D3D12CreateDevice(adapter.Get(), MIN_FEATURE_LEVEL, IID_PPV_ARGS(&device)));
        return device;
    }
}
