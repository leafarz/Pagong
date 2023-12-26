#pragma once
#include "Pagong/Core/CoreTypes.h"
#include "Pagong/Graphics/GraphicsApi.h"

namespace Pagong
{
	class PAGONG_API ProjectSettings : public TSingleton<ProjectSettings>
	{
	public:
		const string& GetGameTitle() const;
		const void SetGameTitle(const string& gameTitle);

		const Math::uivec2& GetWindowSize() const;
		const void SetWindowSize(const Math::uivec2& windowSize);

		const Math::ivec2& GetWindowPos() const;
		const void SetWindowPos(const Math::ivec2& windowPos);

		const Graphics::GraphicsApi GetGraphicsApi() const;
		const void SetGraphicsApi(Graphics::GraphicsApi graphicsApi);

	private:
		string m_GameTitle;
		Math::uivec2 m_WindowSize = Math::uivec2{400, 400};
		Math::ivec2 m_WindowPos = Math::ivec2{ 100, 100 };
		Graphics::GraphicsApi m_GraphicsApi = Graphics::GraphicsApi::D3D12;
	};
}
