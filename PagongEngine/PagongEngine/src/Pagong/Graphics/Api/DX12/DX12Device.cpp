#include "pch.h"
#include "Pagong/Graphics/Api/DX12/DX12Device.h"
#include "Pagong/Graphics/Api/DX12/DX12Common.h"
#include "Pagong/Graphics/Api/DX12/DX12Adapter.h"

namespace Pagong::Graphics::DX12
{
    DX12Device::DX12Device()
        : m_WindowHandle(nullptr), m_Width(0), m_Height(0)
    { }

	void DX12Device::Initialize(Adapter* adapter, uint32 width, uint32 height, void* windowHandle)
	{
        DX12Adapter* dx12Adapter = (DX12Adapter*)(adapter);
        m_Width = width;
        m_Height = height;
        m_WindowHandle = (HWND)windowHandle;
        
        m_Device = CreateDevice(dx12Adapter->GetNativeAdapter());
        m_Device->SetName(L"PagongDevice");
	}

    void DX12Device::Shutdown()
    {
        m_Device->Release();
    }

    Microsoft::WRL::ComPtr<ID3D12Device2> DX12Device::GetNativeDevice()
    {
        return m_Device;
    }

    ComPtr<ID3D12Device2> DX12Device::CreateDevice(ComPtr<IDXGIAdapter1> adapter)
    {
        ComPtr<ID3D12Device2> device;
        DXCHECK(D3D12CreateDevice(adapter.Get(), MIN_FEATURE_LEVEL, IID_PPV_ARGS(&device)));
        return device;
    }
}
