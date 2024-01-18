#include "pch.h"
#include "Pagong/Graphics/Adapter.h"
#include "Pagong/Graphics/Api/DX12/DX12Adapter.h"

namespace Pagong::Graphics
{
	TUnique<Adapter> Adapter::Create(GraphicsApi graphicsApi)
	{
        switch (graphicsApi)
        {
        case GraphicsApi::DX12:
            return MakeUnique<DX12::DX12Adapter>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
	}
}
