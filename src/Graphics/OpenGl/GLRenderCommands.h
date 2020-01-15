#pragma once
#include "Graphics/Api/RenderCommands.h"
#include "Graphics/Api/RenderProperties.h"


namespace Fireblast {
	namespace OpenGL {
		
		class GLRenderCommands : public Fireblast::RenderCommands
		{
		public:
			virtual bool Init() override;


			virtual void SetViewport(int _width, int _height) override;

			virtual void Clear() override;

			virtual void ClearColor(float r, float g, float b, float a) override;

			virtual void SetBlend(bool _enable) override;

			virtual VertexArray* CreateVertexArray() override;

			virtual VertexBuffer* CreateVertexBuffer(const unsigned int size) override;

			virtual VertexBuffer* CreateVertexBuffer(void* data) override;

			virtual IndexBuffer* CreateIndexBuffer(const unsigned int size) override;

			virtual Shader* CreateShader(const std::string vertexPath, const std::string fragmentPath) override;

			virtual Shader* CreateShader(const char* vertexSource, const char* fragmentSource) override;

			// Textures
			virtual Texture* CreateTexture(const std::string path) override;
			virtual Texture* CreateTexture(const void* data, const unsigned int width, const unsigned int height) override;

		public:
			static inline const unsigned int PropertyToOpengl(const Fireblast::BufferUsage usage) 
			{
				switch (usage) 
				{
				case BufferUsage::Static_Draw:
					return 0x88E4;
					break;
				case BufferUsage::Dynamic_Draw:
					return 0x88E8;
					break;
				}
			}

			static inline const unsigned int PropertyToOpengl(const Fireblast::RenderPrimitives primitives) 
			{
				switch (primitives)
				{
				case RenderPrimitives::Quads:
					return 0x0007;
					break;
				case RenderPrimitives::Traingles_Strip:
					return 0x0005;
					break;
				case RenderPrimitives::Triangles:
					return 0x0004;
					break;
				}
			}

			static inline const unsigned int PropertyToOpengl(const Fireblast::ShaderType type)
			{
				switch (type)
				{
				case ShaderType::Float:
					return 0x1406;
					break;
				case ShaderType::Int:
					return 0x1404;
					break;
				}
			}

		};

	}
};