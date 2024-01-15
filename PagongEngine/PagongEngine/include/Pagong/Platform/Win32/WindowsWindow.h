#pragma once
#include "Pagong/Core/CoreTypes.h"

namespace Pagong::Win32
{
	class WindowsWindow : public Window
	{
	private:
		using WindowHandle = HWND;
		struct WindowInfo
		{
			WindowHandle Handle;
			wstring ClassName;
			wstring Title;
			Math::ivec2 Pos;
			Math::uivec2 Size;

			WindowInfo()
				: Handle(nullptr), ClassName(L""), Title(L""), Pos({0, 0}), Size({200, 200})
			{ }

			WindowInfo(
				WindowHandle handle, const wstring& className, const wstring& title,
				int32 x, int32 y, uint32 width = 1280, uint32 height = 720)
				: Handle(handle), ClassName(className), Title(title), Pos({x,y}), Size({width,height})
			{ }
		};

	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		WindowsWindow(const WindowInitInfo& windowInitInfo);
		~WindowsWindow();

#pragma region Window Virtuals
		void* GetHandle() const override;
		bool ProcessMessage() override;
		void Close() override;
		const Math::uivec2 GetSize() const override;
		void SetSize(const Math::uivec2& size) override;
		const uint32 GetWidth() const override;
		const uint32 GetHeight() const override;
		const Math::ivec2 GetPos() const override;
		void SetPos(const Math::ivec2& pos) override;
		void SetTitle(const string& title) override;
#pragma endregion Window Virtuals

	private:
		string GetLastErrorString();
		WNDCLASSEX InitializeWindow(const WindowInitInfo& windowInitInfo);
		HWND CreateWindow(const WindowInitInfo& windowInitInfo, const WNDCLASSEX& windowClass);


	private:
		WindowInfo m_Info;
		WNDCLASSEX m_Class;
		HWND m_Handle;
	};
}
