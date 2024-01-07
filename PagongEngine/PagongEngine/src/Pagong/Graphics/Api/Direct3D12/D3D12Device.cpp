#include "pch.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Device.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Common.h"

namespace Pagong::Graphics::D3D12
{
    D3D12Device::D3D12Device()
        : m_WindowHandle(nullptr), m_Width(0), m_Height(0)
    { }

	void D3D12Device::Initialize(uint32 width, uint32 height, void* windowHandle)
	{
        m_Width = width;
        m_Height = height;
        m_WindowHandle = (HWND)windowHandle;
        
        m_Device = CreateDevice();
        m_Device->SetName(L"Pagong Device");
	}

    void D3D12Device::Shutdown()
    {
        m_Device->Release();
    }

    Microsoft::WRL::ComPtr<ID3D12Device2> D3D12Device::GetD3D12Device()
    {
        return m_Device;
    }

    ComPtr<ID3D12Device2> D3D12Device::CreateDevice()
    {
        ComPtr<ID3D12Device2> device;
        DXCHECK(D3D12CreateDevice(nullptr, MIN_FEATURE_LEVEL, IID_PPV_ARGS(&device)));
        return device;
    }
}
