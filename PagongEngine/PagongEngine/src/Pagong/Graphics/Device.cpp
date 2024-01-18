#include "pch.h"
#include "Pagong/Graphics/Device.h"
#include "Pagong/Graphics/Api/DX12/DX12Device.h"

namespace Pagong::Graphics
{
    TUnique<Device> Device::Create(GraphicsApi graphicsApi)
    {
        switch (graphicsApi)
        {
        case GraphicsApi::DX12:
            return MakeUnique<DX12::DX12Device>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
    }
}
