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
#include "Utils/FileUtils.h"

namespace Fireblast {
	namespace OpenGL {
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

		void GLRenderCommands::GetRendererErrors()
		{
			FB_ASSERT(glGetError() == GL_NO_ERROR, "Opengl error: " + glGetError());
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

		VertexBuffer* GLRenderCommands::CreateVertexBuffer()
		{
			return new GLVertexBuffer();
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

	}
};
