#include "pch.h"
#include "Pagong/Graphics/SwapChain.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12SwapChain.h"

namespace Pagong::Graphics
{
	TShared<SwapChain> SwapChain::Create(GraphicsApi graphicsApi)
	{
        switch (graphicsApi)
        {
        case GraphicsApi::D3D12:
            return MakeShared<D3D12::D3D12SwapChain>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
	}
}
