#include "fbpch.h"
#include "glad/glad.h"
#include "GLShader.h"
#include "Application\Log.h"
#include "glm/gtc/type_ptr.hpp"

namespace Fireblast {
	namespace OpenGL {
		Fireblast::OpenGL::GLShader::GLShader(const char* vertexSource, const char* fragmentSource)
			: Shader(vertexSource, fragmentSource), m_Id(0), m_VSource(vertexSource), m_FSource(fragmentSource)
		{
			m_Id = Compile();
		}

		void Fireblast::OpenGL::GLShader::Bind()
		{
			glUseProgram(m_Id);
		}

		void Fireblast::OpenGL::GLShader::Delete()
		{
			glDeleteProgram(m_Id);
		}

		const int Fireblast::OpenGL::GLShader::GetUniformLocation(const char* name)
		{
			return glGetUniformLocation(m_Id, name);
		}

		unsigned int Fireblast::OpenGL::GLShader::Compile()
		{
			// Create ids 
			unsigned int _pid = glCreateProgram();
			unsigned int _vid = glCreateShader(GL_VERTEX_SHADER);
			unsigned int _fid = glCreateShader(GL_FRAGMENT_SHADER);

			// Create shaders from source
			glShaderSource(_vid, 1, &m_VSource, NULL);
			glShaderSource(_fid, 1, &m_FSource, NULL);

			// Compile shaders
			glCompileShader(_vid);
			glCompileShader(_fid);

			// Debug
			int _success;
			char infolog[512];
			glGetShaderiv(_vid, GL_COMPILE_STATUS, &_success); // Vertex
			if (!_success) {
				glGetShaderInfoLog(_vid, 512, NULL, infolog);
				FB_CORE_ERROR("Vertex Shader -> {0} ", infolog);
			}

			glGetShaderiv(_fid, GL_COMPILE_STATUS, &_success); // fragment
			if (!_success) {
				glGetShaderInfoLog(_fid, 512, NULL, infolog);
				FB_CORE_ERROR("Fragment Shader -> {0} ", infolog);
			}

			// Link Shaders
			glAttachShader(_pid, _vid);
			glAttachShader(_pid, _fid);
			glLinkProgram(_pid);

			glGetProgramiv(_pid, GL_LINK_STATUS, &_success);
			if (!_success) {
				glGetProgramInfoLog(_pid, 512, NULL, infolog);
				FB_CORE_ERROR("Shader program -> {0} ", infolog);
			}

			// delete vertex and fragment shaders
			glDeleteShader(_vid);
			glDeleteShader(_fid);

			return _pid;
		}

		void GLShader::SetInt(const std::string& name, int value)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniform1i(loc, value);
		}

		void GLShader::SetInt2(const std::string& name, int value, int value2)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniform2i(loc, value, value2);
		}

		void GLShader::SetInt3(const std::string& name, int value, int value2, int value3)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniform3i(loc, value, value2, value3);
		}

		void GLShader::SetInt4(const std::string& name, int value, int value2, int value3, int value4)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniform4i(loc, value, value2, value3, value4);
		}

		void GLShader::SetFloat(const std::string& name, float value)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniform1f(loc, value);
		}

		void GLShader::SetFloat2(const std::string& name, float value, float value2)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniform2f(loc, value, value2);
		}

		void GLShader::SetFloat3(const std::string& name, float value, float value2, float value3)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniform3f(loc, value, value2, value3);
		}

		void GLShader::SetFloat4(const std::string& name, float value, float value2, float value3, float value4)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniform4f(loc, value, value2, value3, value4);
		}

		void GLShader::SetVec2(const std::string& name, glm::vec2& vector)
		{
			SetFloat2(name, vector.x, vector.y);
		}

		void GLShader::SetVec3(const std::string& name, glm::vec3& vector)
		{
			SetFloat3(name, vector.x, vector.y, vector.z);
		}

		void GLShader::SetVec4(const std::string& name, glm::vec4& vector) 
		{
			SetFloat4(name, vector.x, vector.y, vector.z, vector.w);
		}

		void GLShader::SetMat3(const std::string& name, const glm::mat3& matrix)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniformMatrix3fv(loc, 1, false, glm::value_ptr(matrix));
		}

		void GLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
		{
			int loc = GetUniformLocation(name.c_str());
			glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
		}
	}
}
