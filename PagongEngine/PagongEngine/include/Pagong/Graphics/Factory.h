#pragma once

namespace Pagong::Graphics
{
	class Factory
	{
	public:
		static TShared<Factory> Create(GraphicsApi graphicsApi);

		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;
	};
}