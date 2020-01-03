#pragma once
#include <string>

#include "glm/glm.hpp"

namespace Fireblast {
	class Shader 
	{
	public:
		inline Shader(const char* vertexSource, const char* fragmentSource) {};
		inline virtual ~Shader() {};
	public:
		virtual void Bind() = 0;
		virtual void Delete() = 0;

	public:
		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetInt2(const std::string& name, int value, int value2) = 0;
		virtual void SetInt3(const std::string& name, int value, int value2, int value3) = 0;
		virtual void SetInt4(const std::string& name, int value, int value2, int value3, int value4) = 0;

		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, float value, float value2) = 0;
		virtual void SetFloat3(const std::string& name, float value, float value2, float value3) = 0;
		virtual void SetFloat4(const std::string& name, float value, float value2, float value3, float value4) = 0;

		virtual void SetVec2(const std::string& name, glm::vec2& vector) = 0;
		virtual void SetVec3(const std::string& name, glm::vec3& vector) = 0;
		virtual void SetVec4(const std::string& name, glm::vec4& vector) = 0;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;
	protected:
		virtual const int GetUniformLocation(const char* name) = 0;
	};
}