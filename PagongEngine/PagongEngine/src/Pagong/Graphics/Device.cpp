#include "pch.h"
#include "Pagong/Graphics/Device.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Device.h"

namespace Pagong::Graphics
{
    TUnique<Device> Device::Create(GraphicsApi graphicsApi)
    {
        switch (graphicsApi)
        {
        case GraphicsApi::D3D12:
            return MakeUnique<D3D12::D3D12Device>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
    }
}
