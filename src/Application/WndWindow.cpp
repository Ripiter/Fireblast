#include "fbpch.h"
#include "WndWindow.h"

#include "Utils/Performance.h"

namespace Fireblast {

	WndWindow::WndWindow() : m_WindowHandle(NULL), m_Data()
	{
		m_Data.Width = 800;
		m_Data.Height = 600;
		m_Data.Title = "Fireblast Engine";
		m_Data.VsyncEnabled = false;
	}
	
	WndWindow::~WndWindow() 
	{
		glfwDestroyWindow(m_WindowHandle);
		delete m_WindowHandle;
	}

	bool WndWindow::Init() {
		FB_PERFORMANCE_PROFILE();

		if (!glfwInit())
			return false;

		m_WindowHandle = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		if (!m_WindowHandle)
			return false;


		SetVSync(false);

		glfwSetWindowUserPointer(m_WindowHandle, &m_Data);
		SetEvents();

		return true;
	}

	bool WndWindow::IsWindowAlive() 
	{
		return !glfwWindowShouldClose(m_WindowHandle);
	}

	void WndWindow::SwapBuffers() 
	{
		FB_PERFORMANCE_PROFILE();

		glfwSwapBuffers(m_WindowHandle);
	}

	void WndWindow::SetVSync(bool enabled) {
		FB_PERFORMANCE_PROFILE();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VsyncEnabled = enabled;
	}

	void WndWindow::PollWindowEvents() {
		FB_PERFORMANCE_PROFILE();

		glfwPollEvents();
	}

	void WndWindow::TerminateWindows()
	{
		glfwTerminate();
	}

	void WndWindow::MakeCurrent() {
		glfwMakeContextCurrent(m_WindowHandle);
	}

	float WndWindow::GetTime() {
		return (float)glfwGetTime();
	}

	void WndWindow::SetEvents() 
	{
		FB_PERFORMANCE_PROFILE();

		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* wnd, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(wnd);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* wnd) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(wnd);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetWindowFocusCallback(m_WindowHandle, [](GLFWwindow* wnd, int focused) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(wnd);
			
			WindowFocusEvent event((bool)focused);
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* wnd, int key, int scancode, int action, int mods){
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(wnd);
			
			switch (action)
			{
				case 1: // press
				{
					KeyPressedEvent event(static_cast<KeyCodes>(key), scancode, mods);
					data.EventCallback(event);
					break;
				}
				case 0: // Release
				{
					KeyReleasedEvent event(static_cast<KeyCodes>(key), scancode, mods);
					data.EventCallback(event);
					break;
				}
				case 2: // Repeat;
				{
					KeyRepeatEvent event(static_cast<KeyCodes>(key), scancode, mods);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* wnd, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(wnd);
			
			switch (action)
			{
				case 1: // press
				{
					MousePressedEvent event(static_cast<MouseButtons>(button), mods);
					data.EventCallback(event);
					break;
				}
				case 0: // Release
				{
					MouseReleasedEvent event(static_cast<MouseButtons>(button), mods);
					data.EventCallback(event);
					break;
				}
				case 2: // Repeat;
				{
					MouseRepeatEvent event(static_cast<MouseButtons>(button), mods);
					data.EventCallback(event);
					break;
				}
			}
		});
	}

	void WndWindow::SetEventHandler(std::function<void(Event&)> eventFunc) {
		m_Data.EventCallback = eventFunc;
	}
}