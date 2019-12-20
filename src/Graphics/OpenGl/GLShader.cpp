#include "fbpch.h"
#include "glad/glad.h"
#include "GLShader.h"
#include <Application\Log.h>


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

		void Fireblast::OpenGL::GLShader::GetUniformLocation(const char* name)
		{
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

	}
}
