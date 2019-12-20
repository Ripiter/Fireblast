#pragma once
#include "Graphics/Api/RenderCommands.h"


namespace Fireblast {
	namespace OpenGL {
		
		class GLRenderCommands : public Fireblast::RenderCommands
		{
		public:
			virtual bool Init() override;


			virtual void SetViewport(int _width, int _height) override;

			virtual void Clear() override;

			virtual void ClearColor(float r, float g, float b, float a) override;

			virtual void GetRendererErrors() override;

			virtual void SetBlend(bool _enable) override;


			// Inherited via RenderCommands
			virtual Shader* CreateShader(const std::string vertexPath, const std::string fragmentPath) override;

			virtual Shader* CreateShader(const char* vertexSource, const char* fragmentSource) override;

		};

	}
};