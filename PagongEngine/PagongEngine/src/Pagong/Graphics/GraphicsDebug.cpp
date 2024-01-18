#include "pch.h"
#include "Pagong/Graphics/GraphicsDebug.h"
#include "Pagong/Graphics/Api/DX12/DX12Debug.h"

namespace Pagong::Graphics
{
	TUnique<GraphicsDebug> GraphicsDebug::Create(GraphicsApi graphicsApi)
	{
		switch (graphicsApi)
		{
		case GraphicsApi::DX12:
			return MakeUnique<DX12::DX12Debug>();

		case GraphicsApi::None:
		default:
			PG_ASSERT(false, "Graphics Api not supported!");
			return nullptr;
		}
	}
}
