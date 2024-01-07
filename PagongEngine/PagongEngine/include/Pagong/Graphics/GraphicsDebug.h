#pragma once
#include "Pagong/Graphics/GraphicsApi.h"

namespace Pagong::Graphics
{
	class GraphicsDebug
	{
	public:
		static TUnique<GraphicsDebug> Create(GraphicsApi graphicsApi);

	public:
		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;
	};
}
