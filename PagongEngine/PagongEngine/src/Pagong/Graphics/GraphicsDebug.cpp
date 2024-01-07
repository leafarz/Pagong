#include "pch.h"
#include "Pagong/Graphics/GraphicsDebug.h"
#include "Pagong/Graphics/Api/Direct3D12/D3D12Debug.h"

namespace Pagong::Graphics
{
	TUnique<GraphicsDebug> GraphicsDebug::Create(GraphicsApi graphicsApi)
	{
		switch (graphicsApi)
		{
		case GraphicsApi::D3D12:
			return MakeUnique<D3D12::D3D12Debug>();

		case GraphicsApi::None:
		default:
			PG_ASSERT(false, "Graphics Api not supported!");
			return nullptr;
		}
	}
}
