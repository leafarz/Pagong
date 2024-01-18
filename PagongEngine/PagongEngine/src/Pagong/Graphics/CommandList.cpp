#include "pch.h"
#include "Pagong/Graphics/CommandList.h"
#include "Pagong/Graphics/Api/DX12/DX12CommandList.h"

namespace Pagong::Graphics
{
    TShared<CommandList> CommandList::Create(GraphicsApi graphicsApi)
	{
        switch (graphicsApi)
        {
        case GraphicsApi::DX12:
            return MakeShared<DX12::DX12CommandList>();

        case GraphicsApi::None:
        default:
            PG_ASSERT(false, "Graphics Api not supported!");
            return nullptr;
        }
	}


}
