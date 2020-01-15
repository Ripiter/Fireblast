#include "fbpch.h"
#include "GLTexture.h"
#include "glad/glad.h"


namespace Fireblast { namespace OpenGL {

	GLTexture::GLTexture()
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
	}

	void GLTexture::ActivateTexture(const unsigned int slot)
	{
		glBindTextureUnit(slot, m_Id);
	}

	void GLTexture::SetData(const unsigned char* data, const unsigned int width, const unsigned int height)
	{
		glTextureStorage2D(m_Id, 1, GL_RGBA8, width, height);
		SetFiltering();
		glTextureSubImage2D(m_Id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
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