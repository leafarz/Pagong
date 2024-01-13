#pragma once
#include "Pagong/Graphics/Resource.h"

namespace Pagong::Graphics::D3D12
{
	class D3D12Resource : public Resource
	{
	public:
		void Initialize(Microsoft::WRL::ComPtr<ID3D12Resource> resource);

		Microsoft::WRL::ComPtr<ID3D12Resource> GetNativeResource();

#pragma region Resource Virtuals
		void Shutdown() override;
#pragma endregion Resource Virtuals

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> m_Resource;
	};
}
