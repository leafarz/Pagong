#include "pch.h"
#include "Pagong/Graphics/Adapter.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Adapter.h"

namespace Pagong::Graphics
{
	TUnique<Adapter> Adapter::Create(GraphicsApi graphicsApi)
	{
        switch (graphicsApi)
        {
        case GraphicsApi::D3D12:
            return MakeUnique<D3D12::D3D12Adapter>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
	}
}
