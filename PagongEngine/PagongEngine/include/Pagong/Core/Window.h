#pragma once
#include "Pagong/Core/Aliases.h"

namespace Pagong
{
	struct WindowInitInfo
	{
		string ClassName;
		string Title;
		Math::uivec2 Size;
		Math::ivec2 Pos;

		WindowInitInfo() = default;
		WindowInitInfo(const string& className, const string& title, const Math::uivec2& size = { 1280, 720 }, const Math::ivec2& pos = {100, 100} )
			: ClassName(className), Title(title), Size(size), Pos(pos)
		{ }
	};

	class PAGONG_API Window
	{
	public:
		static TUnique<Window> Create(const WindowInitInfo& windowProps);
	
	public:
		virtual bool ProcessMessage() = 0;
		virtual void Close() = 0;
		virtual const Math::uivec2 GetSize() const = 0;
		virtual void SetSize(const Math::uivec2& size) = 0;
		virtual const Math::ivec2 GetPos() const = 0;
		virtual void SetPos(const Math::ivec2& pos) = 0;
	};
}
