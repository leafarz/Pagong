#include "pch.h"
#include "Pagong/Graphics/SwapChain.h"
#include "Pagong/Graphics/Api/DX12/DX12SwapChain.h"

namespace Pagong::Graphics
{
	TShared<SwapChain> SwapChain::Create(GraphicsApi graphicsApi)
	{
        switch (graphicsApi)
        {
        case GraphicsApi::DX12:
            return MakeShared<DX12::DX12SwapChain>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
	}
}
