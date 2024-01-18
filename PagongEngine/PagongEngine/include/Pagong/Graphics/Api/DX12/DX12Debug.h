#pragma once
#include "Pagong/Graphics/GraphicsDebug.h"

namespace Pagong::Graphics::DX12
{
	class DX12Debug : public GraphicsDebug
	{
	public:
#pragma region GraphicsDebug virtuals
		void Initialize() override;
		void Shutdown() override;
#pragma endregion GraphicsDebug virtuals

	private:
		void EnableDebugLayer();
		void EnableLeakTrackingForThread();
		void ReportLiveObjects();
	};
}
