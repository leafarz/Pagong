#include "pch.h"
#include "Pagong/Graphics/Api/DX12/DX12Adapter.h"
#include "Pagong/Graphics/Api/DX12/DX12Common.h"
#include "Pagong/Graphics/Api/DX12/DX12Device.h"
#include "Pagong/Graphics/Api/DX12/DX12Factory.h"

namespace Pagong::Graphics::DX12
{
	void DX12Adapter::Initialize(TShared<Factory> factory)
	{
        TShared<DX12Factory> dx12Factory = std::dynamic_pointer_cast<DX12Factory>(factory);
        m_Adapter = GetHardwareAdapter(dx12Factory->GetNativeFactory());
	}

    void DX12Adapter::Shutdown()
    {
        m_Adapter->Release();
    }

    const wchar* DX12Adapter::GetDescription()
    {
        return m_Desc.Description;
    }

    uint64 DX12Adapter::GetDedicatedVideoMemory()
    {
        return m_Desc.DedicatedVideoMemory;
    }

    uint64 DX12Adapter::GetSharedSystemMemory()
    {
        return m_Desc.SharedSystemMemory;
    }

    ComPtr<IDXGIAdapter1> DX12Adapter::GetNativeAdapter()
    {
        return m_Adapter;
    }

    ComPtr<IDXGIAdapter1> DX12Adapter::GetHardwareAdapter(ComPtr<IDXGIFactory4> factory)
    {
        ComPtr<IDXGIAdapter1> adapter;
        ComPtr<IDXGIFactory6> factory6;
        if (SUCCEEDED(factory->QueryInterface(IID_PPV_ARGS(&factory6))))
        {
            for (
                uint32 i = 0
                ; SUCCEEDED(factory6->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)))
                ; ++i)
            {
                DXGI_ADAPTER_DESC1 desc;
                adapter->GetDesc1(&desc);

                if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                {
                    continue;
                }

                if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), MIN_FEATURE_LEVEL, _uuidof(ID3D12Device), nullptr)))
                {
                    m_Desc = desc;
                    break;
                }
            }
        }
        return adapter;
    }
}
