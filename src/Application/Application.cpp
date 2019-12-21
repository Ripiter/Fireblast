#include "fbpch.h"

#include "glad/glad.h"
#include "Graphics/OpenGl/GLVertexArray.h"

#include "Core/Core.h"
#include "application/Application.h"
#include "Application/Log.h"
#include "Application/Time.h"
#include "Graphics/Api/RenderAPI.h"

namespace Fireblast {

	Application::Application() : m_IsRunning(false)
	{
		m_WindowInstance = new WndWindow();
	}

	Fireblast::OpenGL::GLVertexArray* vao;
	unsigned int vaoId;
	unsigned int vboId;

	float _t[3 * 3];

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

		// Render test
		_t[0] = 0.f; _t[1] = 0.5f; _t[2] = 1.f;
		_t[3] = -0.5f; _t[4] = -0.5f; _t[5] = 1.f;
		_t[6] = 0.5f; _t[7] = -0.5f; _t[8] = 1.f;

		/*vao = new Fireblast::OpenGL::GLVertexArray();*/

		glGenVertexArrays(1, &vaoId);
		glGenBuffers(1, &vboId);

		/*vao->Bind();*/
		glBindVertexArray(vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);

		glBufferData(GL_ARRAY_BUFFER, sizeof(_t), &_t, GL_STATIC_DRAW);

		/*vao->SetAttribPointer<float>(0, 3, false, 3, (void*)0);
		vao->EnableAttribPointer(0);*/
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		Fireblast::Shader* _shader = Fireblast::RenderAPI::GetApi()->CreateShader
		(
			std::string("C:/Users/Emil/source/repos/Fireblast/src/vFlatShader.txt"), 
			std::string("C:/Users/Emil/source/repos/Fireblast/src/fFlatShader.txt")
		);

		// Update loop
		while (m_IsRunning) {

			// Calculate delta time
			t2 = WndWindow::GetTime();
			Time::SetDeltaTime(t2 - t1);
			t1 = t2;

			OnUpdate();

			// Clear
			RenderAPI::GetApi()->ClearColor(0.f, 0.f, 1.f, 1.f);
			RenderAPI::GetApi()->Clear();

			// Draw to screen
			OnDraw();

			_shader->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);

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

	void Application::OnApplicationEvent(Event& event) {
	}

	Application::~Application() {

	}
};