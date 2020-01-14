#include "fbpch.h"
#include "application/Application.h"
#include "Core/Core.h"
#include "Graphics/Api/RenderAPI.h"
#include "Graphics/Renderer2D.h"
#include "Core/SManager.h"

namespace Fireblast {

	Application::Application() : m_IsRunning(false)
	{
		m_WindowInstance = new WndWindow();
	}

	void Application::Run()
	{
		// Start
		Log::Init();

		// Create window
		m_IsRunning = m_WindowInstance->Init();
		FB_CORE_ASSERT(m_IsRunning, "Couldn't Create Window");
		FB_CORE_INFO("Created window [{0}x{1}] '{2}'", m_WindowInstance->GetWidth(), m_WindowInstance->GetHeight(), m_WindowInstance->GetTitle());
		m_WindowInstance->SetEventHandler(std::bind(&Application::OnApplicationEvent, this, std::placeholders::_1)); // bind to eventhandler
		Input::SetWindow(m_WindowInstance->GetWindowHandle());
		m_WindowInstance->MakeCurrent();

		// init render API
		// TODO: Let the user decide what api to use
		// It could maybe be constructed in the application
		// as a virtual function which can be overriden
		// if the user wants to change api at the start
		RenderAPI::Create(RenderVendor::Opengl);
		FB_CORE_ASSERT(RenderAPI::GetApi()->Init(), "Render Api failed to init!");

		// Start systems
		SManager::Get()->Start();
		OnStart();

		float t1, t2;
		t1 = t2 = WndWindow::GetTime();
		
		// Update loop
		while (m_IsRunning) {

			// Calculate delta time
			t2 = WndWindow::GetTime();
			Time::SetDeltaTime(t2 - t1);
			t1 = t2;

			SManager::Get()->BeforeUpdate();
			OnUpdate();
			SManager::Get()->Update();

			// Clear
			RenderAPI::GetApi()->ClearColor(0.f, 0.f, 1.f, 1.f);
			RenderAPI::GetApi()->Clear();

			// Draw to screen
			OnDraw();

			SManager::Get()->Draw();

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
		delete m_WindowInstance;
	}
};