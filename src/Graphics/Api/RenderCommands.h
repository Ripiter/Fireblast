#pragma once

#include "Graphics/Api/Shader.h"

namespace Fireblast {

	class RenderCommands {
	public:
		virtual bool Init() = 0;
		virtual void SetViewport(int _width, int _height) = 0;
		virtual void Clear() = 0;
		virtual void ClearColor(float r, float g, float b, float a) = 0;
		virtual void GetRendererErrors() = 0;
		virtual void SetBlend(bool _enable) = 0;
		
		// Create VAO
		// Create VBO
		// Create Shader
		virtual Shader* CreateShader(const std::string vertexPath, const std::string fragmentPath) = 0;
		virtual Shader* CreateShader(const char* vertexSource, const char* fragmentSource) = 0;
		// Draw with vaos
		// Draw with indicies
		// Draw indicies instanced

	};
}