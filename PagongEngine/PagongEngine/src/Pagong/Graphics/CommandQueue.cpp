#include "pch.h"
#include "Pagong/Graphics/CommandQueue.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12CommandQueue.h"

namespace Pagong::Graphics
{
    TShared<CommandQueue> CommandQueue::Create(GraphicsApi graphicsApi)
    {
        switch (graphicsApi)
        {
        case GraphicsApi::D3D12:
            return MakeShared<D3D12::D3D12CommandQueue>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
    }
}
