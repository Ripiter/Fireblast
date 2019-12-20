#pragma once
#include "Graphics/Api/Shader.h"

namespace Fireblast {
	namespace OpenGL {
		class GLShader : public Shader
		{
		private:
			unsigned int m_Id;
			const char* m_VSource;
			const char* m_FSource;
		public:
			GLShader(const char* vertexSource, const char* fragmentSource);
		public:
			virtual void Bind() override;
			virtual void Delete() override;
		protected:
			virtual void GetUniformLocation(const char* name) override;

		private:
			unsigned int Compile();
		};
	}
}


