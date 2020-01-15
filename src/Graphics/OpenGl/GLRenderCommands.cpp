#include "fbpch.h"
#include "Application/Log.h"
#include "Core/Core.h"
#include "GLRenderCommands.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Graphics/OpenGl/GLShader.h"
#include "Graphics/OpenGl/GLVertexArray.h"
#include "Graphics/OpenGl/GLVertexBuffer.h"
#include "Graphics/OpenGl/GLIndexBuffer.h"
#include "Graphics/OpenGl/GLTexture.h"
#include "Utils/FileUtils.h"

namespace Fireblast {
	namespace OpenGL {

		void OpenGLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:         FB_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       FB_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          FB_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: FB_CORE_TRACE(message); return;
			}
		}

		bool GLRenderCommands::Init()
		{
			// Load all opengl functions
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				return false;
			}

			FB_CORE_INFO("Opengl: [{0}]", glGetString(GL_VERSION));
			FB_CORE_INFO("Glsl: [{0}]", glGetString(GL_SHADING_LANGUAGE_VERSION));
			FB_CORE_INFO("Vendor: [{0}]", glGetString(GL_VENDOR));
			FB_CORE_INFO("Renderer: [{0}]", glGetString(GL_RENDERER));

#if FB_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

			return true;
		}

		void GLRenderCommands::SetViewport(int _width, int _height)
		{
			glViewport(0, 0, _width, _height);
		}

		void GLRenderCommands::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void GLRenderCommands::ClearColor(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a);
		}

		void GLRenderCommands::SetBlend(bool _enable)
		{
			if (_enable) 
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else 
			{
				glDisable(GL_BLEND);
			}
		}

		VertexArray* GLRenderCommands::CreateVertexArray() 
		{
			return new GLVertexArray();
		}

		VertexBuffer* GLRenderCommands::CreateVertexBuffer(const unsigned int size)
		{
			GLVertexBuffer* _p = new GLVertexBuffer();
			_p->Bind();
			_p->SetBufferData(size, NULL, Fireblast::BufferUsage::Dynamic_Draw);
			return _p;
		}

		VertexBuffer* GLRenderCommands::CreateVertexBuffer(void* data)
		{
			GLVertexBuffer* _p = new GLVertexBuffer();
			_p->Bind();
			_p->SetBufferData(sizeof(data), data, Fireblast::BufferUsage::Static_Draw);
			return _p;
		}

		IndexBuffer* GLRenderCommands::CreateIndexBuffer(const unsigned int size)
		{
			return new GLIndexBuffer(size);
		}

		Shader* GLRenderCommands::CreateShader(const std::string vertexPath, const std::string fragmentPath)
		{
			std::string vShaderText = Fireblast::FileUtils::ReadFileContent(vertexPath);
			std::string fShaderText = Fireblast::FileUtils::ReadFileContent(fragmentPath);

			return new GLShader(vShaderText.c_str(), fShaderText.c_str());
		}

		Shader* GLRenderCommands::CreateShader(const char* vertexSource, const char* fragmentSource)
		{
			return new GLShader(vertexSource, fragmentSource);
		}

		Texture* GLRenderCommands::CreateTexture(const std::string path)
		{
			unsigned int width, height;

			unsigned char* data = Fireblast::FileUtils::ReadImageData(path, &width, &height);

			Texture* text = new GLTexture();
			text->Bind();
			text->SetData(data, width, height);

			delete[] data;
			return text;
		}

		Texture* GLRenderCommands::CreateTexture(const void* data, const unsigned int width, const unsigned int height)
		{
			Texture* text = new GLTexture();
			text->Bind();
			text->SetData((unsigned char*)data, width, height);

			return text;
		}

	}
};
