#pragma once
#include "Pagong/Graphics/Adapter.h"

namespace Pagong::Graphics::D3D12
{
	class D3D12Adapter : public Adapter
	{
	public:
#pragma region Adapter Virtuals
		void Initialize(TShared<Factory> factory) override;
		void Shutdown() override;
		const wchar* GetDescription() override;
		uint64 GetDedicatedVideoMemory() override;
		uint64 GetSharedSystemMemory() override;
#pragma endregion Adapter Virtuals

		Microsoft::WRL::ComPtr<IDXGIAdapter1> GetNativeAdapter();

	private:
		ComPtr<IDXGIAdapter1> GetHardwareAdapter(ComPtr<IDXGIFactory4> factory);

	private:
		Microsoft::WRL::ComPtr<IDXGIAdapter1> m_Adapter;
		DXGI_ADAPTER_DESC1 m_Desc;
	};
}
