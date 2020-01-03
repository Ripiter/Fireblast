#include "fbpch.h"
#include "GLTexture.h"
#include "glad/glad.h"


namespace Fireblast { namespace OpenGL {

	GLTexture::GLTexture()
	{
		glGenTextures(1, &m_Id);
	}

	void GLTexture::ActivateTexture(const unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	void GLTexture::SetData(const unsigned char* data, const unsigned int width, const unsigned int height)
	{
		SetFiltering();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	}

	void GLTexture::SetFiltering() 
	{
		glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void GLTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

	void GLTexture::Delete()
	{
		glDeleteTextures(1, &m_Id);
	}

}}