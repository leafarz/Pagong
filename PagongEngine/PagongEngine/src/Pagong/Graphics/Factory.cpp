#include "pch.h"
#include "Pagong/Graphics/Factory.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Factory.h"

namespace Pagong::Graphics
{
    TShared<Factory> Factory::Create(GraphicsApi graphicsApi)
    {
        switch (graphicsApi)
        {
        case GraphicsApi::D3D12:
            return MakeShared<D3D12::D3D12Factory>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
    }
}
