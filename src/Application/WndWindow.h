#pragma once
#include "GLFW/glfw3.h"
#include "Event/WindowEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

#include <functional>
#include <string>

namespace Fireblast {
	class WndWindow
	{
	private:
		struct WindowData {
			int Width;
			int Height;
			std::string Title;
			bool VsyncEnabled;

			std::function<void(Event&)> EventCallback;
		};

		GLFWwindow* m_WindowHandle;
		WindowData m_Data;

	public:
		WndWindow();
		~WndWindow();

		bool Init();
		bool IsWindowAlive();
		void SwapBuffers();
		void MakeCurrent();
		void SetEventHandler(std::function<void(Event&)> eventFunc);
		void SetVSync(bool enabled);
	public:
		inline int GetWidth() const { return m_Data.Width; }
		inline int GetHeight() const { return m_Data.Height; }
		inline std::string GetTitle() const { return m_Data.Title; }
		inline bool IsVsyncEnabled() const { return m_Data.VsyncEnabled; }
		inline void* GetWindowHandle() const { return m_WindowHandle; }
	public:
		static void PollWindowEvents();
		static void TerminateWindows();
		static float GetTime();
	private:
		void SetEvents();
	};

}

