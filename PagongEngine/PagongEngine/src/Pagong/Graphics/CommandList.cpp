#include "pch.h"
#include "Pagong/Graphics/CommandList.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12CommandList.h"

namespace Pagong::Graphics
{
    TShared<CommandList> CommandList::Create(GraphicsApi graphicsApi)
	{
        switch (graphicsApi)
        {
        case GraphicsApi::D3D12:
            return MakeShared<D3D12::D3D12CommandList>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
	}


}
