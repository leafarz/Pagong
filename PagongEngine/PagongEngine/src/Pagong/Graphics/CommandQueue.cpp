#include "pch.h"
#include "Pagong/Graphics/CommandQueue.h"
#include "Pagong/Graphics/Api/DX12/DX12CommandQueue.h"

namespace Pagong::Graphics
{
    TShared<CommandQueue> CommandQueue::Create(GraphicsApi graphicsApi)
    {
        switch (graphicsApi)
        {
        case GraphicsApi::DX12:
            return MakeShared<DX12::DX12CommandQueue>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
    }
}
