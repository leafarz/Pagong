#include "pch.h"
#include "Pagong/Graphics/Factory.h"
#include "Pagong/Graphics/Api/DX12/DX12Factory.h"

namespace Pagong::Graphics
{
    TShared<Factory> Factory::Create(GraphicsApi graphicsApi)
    {
        switch (graphicsApi)
        {
        case GraphicsApi::DX12:
            return MakeShared<DX12::DX12Factory>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
    }
}
