#include "fbpch.h"
#include "application/Application.h"
#include "Core/Core.h"
#include "Graphics/Api/RenderAPI.h"
#include "Graphics/Renderer2D.h"

namespace Fireblast {

	Application::Application() : m_IsRunning(false)
	{
		m_WindowInstance = new WndWindow();
	}

	void Application::Run()
	{
		// Start
		Log::Init();
		OnStart();

		// Create window
		m_IsRunning = m_WindowInstance->Init();
		FB_CORE_ASSERT(m_IsRunning, "Couldn't Create Window");
		FB_CORE_INFO("Created window [{0}x{1}] '{2}'", m_WindowInstance->GetWidth(), m_WindowInstance->GetHeight(), m_WindowInstance->GetTitle());
		m_WindowInstance->SetEventHandler(std::bind(&Application::OnApplicationEvent, this, std::placeholders::_1)); // bind to eventhandler
		Input::SetWindow(m_WindowInstance->GetWindowHandle());

		m_WindowInstance->MakeCurrent();

		// init render API
		RenderAPI::Create(RenderVendor::Opengl); // TODO: Let the user decide
		FB_CORE_ASSERT(RenderAPI::GetApi()->Init(), "Render Api failed to init!");
		OnAfterStart();

		float t1, t2;
		t1 = t2 = WndWindow::GetTime();

		Fireblast::Renderer2D::s_Renderer->Onstart();

		// Update loop
		while (m_IsRunning) {

			// Calculate delta time
			t2 = WndWindow::GetTime();
			Time::SetDeltaTime(t2 - t1);
			t1 = t2;

			Fireblast::Renderer2D::s_Renderer->BeginSubmit();
			OnUpdate();
			Fireblast::Renderer2D::s_Renderer->OnUpdate();

			// Clear
			RenderAPI::GetApi()->ClearColor(0.f, 0.f, 1.f, 1.f);
			RenderAPI::GetApi()->Clear();

			// Draw to screen
			OnDraw();
			Fireblast::Renderer2D::s_Renderer->EndSubmit();
			Fireblast::Renderer2D::s_Renderer->OnDraw();

			// Window event handling
			m_WindowInstance->SwapBuffers();
			WndWindow::PollWindowEvents();
			m_IsRunning = m_WindowInstance->IsWindowAlive();

			// Check for render api errors
			RenderAPI::GetApi()->GetRendererErrors();
		}

		// Shutdown
		WndWindow::TerminateWindows();

	};

	void Application::OnApplicationEvent(Event& event) 
	{
	}

	Application::~Application() 
	{

	}
};