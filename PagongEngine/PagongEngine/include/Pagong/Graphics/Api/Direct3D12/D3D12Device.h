#pragma once
#include "Pagong/Graphics/Device.h"
#include "Pagong/Graphics/CommandQueue.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12CommandQueue.h"

namespace Pagong::Graphics::D3D12
{
	class D3D12Device : public Device
	{
	public:
		D3D12Device();

#pragma region Device Virtuals
		void Initialize(Adapter* adapter, uint32 width, uint32 height, void* windowHandle) override;
		void Shutdown() override;
#pragma endregion Device Virtuals

		Microsoft::WRL::ComPtr<ID3D12Device2> GetNativeDevice();

	private:
		Microsoft::WRL::ComPtr<ID3D12Device2> CreateDevice(ComPtr<IDXGIAdapter1> adapter);

	private:
		Microsoft::WRL::ComPtr<ID3D12Device2> m_Device;

		uint32 m_Width;
		uint32 m_Height;
		HWND m_WindowHandle;
	};
}
