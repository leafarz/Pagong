#include "pch.h"
#include "Pagong/Setting/ProjectSettings.h"

namespace Pagong
{
    const string& ProjectSettings::GetGameTitle() const
    {
        return m_GameTitle;
    }

    const void ProjectSettings::SetGameTitle(const string& gameTitle)
    {
        m_GameTitle = gameTitle;
    }

    const Math::uivec2& ProjectSettings::GetWindowSize() const
    {
        return m_WindowSize;
    }

    const void ProjectSettings::SetWindowSize(const Math::uivec2& windowSize)
    {
        m_WindowSize = windowSize;
    }

    const Math::ivec2& ProjectSettings::GetWindowPos() const
    {
        return m_WindowPos;
    }

    const void ProjectSettings::SetWindowPos(const Math::ivec2& windowPos)
    {
        m_WindowPos = windowPos;
    }

    const Graphics::GraphicsApi ProjectSettings::GetGraphicsApi() const
    {
        return m_GraphicsApi;
    }

    const void ProjectSettings::SetGraphicsApi(Graphics::GraphicsApi graphicsApi)
    {
        m_GraphicsApi = graphicsApi;
    }
}
