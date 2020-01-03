#pragma once

#include "Graphics/Api/Shader.h"
#include "Graphics/Api/VertexArray.h"
#include "Graphics/Api/VertexBuffer.h"
#include "Graphics/Api/Texture.h"


namespace Fireblast {

	class RenderCommands {
	public:
		virtual bool Init() = 0;
		virtual void SetViewport(int _width, int _height) = 0;
		virtual void Clear() = 0;
		virtual void ClearColor(float r, float g, float b, float a) = 0;
		virtual void GetRendererErrors() = 0;
		virtual void SetBlend(bool _enable) = 0;
		
		// Buffers
		virtual VertexArray* CreateVertexArray() = 0;
		virtual VertexBuffer* CreateVertexBuffer(const unsigned int size) = 0;
		virtual VertexBuffer* CreateVertexBuffer(void* data) = 0;
		virtual IndexBuffer* CreateIndexBuffer(const unsigned int size) = 0;

		// Create Shader
		virtual Shader* CreateShader(const std::string vertexPath, const std::string fragmentPath) = 0;
		virtual Shader* CreateShader(const char* vertexSource, const char* fragmentSource) = 0;


		// Textures
		virtual Texture* CreateTexture(const std::string path) = 0;
		virtual Texture* CreateTexture(const void* data, const unsigned int width, const unsigned int height) = 0;
	};
}