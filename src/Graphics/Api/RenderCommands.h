#pragma once

#include "Graphics/Api/Shader.h"
#include "Graphics/Api/VertexArray.h"
#include "Graphics/Api/VertexBuffer.h"

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
		virtual VertexArray* CreateVertexArray() = 0;
		virtual VertexBuffer* CreateVertexBuffer() = 0;
		virtual IndexBuffer* CreateIndexBuffer(const unsigned int size) = 0;

		// Create VBO
		// Create Shader
		virtual Shader* CreateShader(const std::string vertexPath, const std::string fragmentPath) = 0;
		virtual Shader* CreateShader(const char* vertexSource, const char* fragmentSource) = 0;

	};
}