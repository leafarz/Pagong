#pragma once
#include "Pagong/Graphics/Factory.h"

namespace Pagong::Graphics::D3D12
{
	class D3D12Factory : public Factory
	{
	public:
#pragma region Factory Virtuals
		void Initialize() override;
		void Shutdown() override;
#pragma endregion Factory Virtuals

		Microsoft::WRL::ComPtr<IDXGIFactory4> GetNativeFactory();

	private:
		Microsoft::WRL::ComPtr<IDXGIFactory4> m_Factory;

	};
}
