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
			virtual ~GLShader() { delete m_VSource, delete m_FSource; }
		public:
			virtual void Bind() override;
			virtual void Delete() override;
		protected:
			virtual const int GetUniformLocation(const char* name) override;

		private:
			unsigned int Compile();

		public:
			virtual void SetInt(const std::string& name, int value) override;
			virtual void SetInt2(const std::string& name, int value, int value2) override;
			virtual void SetInt3(const std::string& name, int value, int value2, int value3) override;
			virtual void SetInt4(const std::string& name, int value, int value2, int value3, int value4) override;
			virtual void SetFloat(const std::string& name, float value) override;
			virtual void SetFloat2(const std::string& name, float value, float value2) override;
			virtual void SetFloat3(const std::string& name, float value, float value2, float value3) override;
			virtual void SetFloat4(const std::string& name, float value, float value2, float value3, float value4) override;
			virtual void SetVec2(const std::string& name, glm::vec2& vector) override;
			virtual void SetVec3(const std::string& name, glm::vec3& vector) override;
			virtual void SetVec4(const std::string& name, glm::vec4& vector) override;
			virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
			virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;
		};
	}
}


