#include "fbpch.h"
#include "glad/glad.h"
#include "GLIndexBuffer.h"


namespace Fireblast { namespace OpenGL {

	GLIndexBuffer::GLIndexBuffer(const unsigned int size) 
		: m_Id(0)
	{
		glGenBuffers(1, &m_Id);

		unsigned int* _indPtr = new unsigned int[size];

		int32_t offset = 0;

		for (int32_t i = 0; i < size; i += 6)
		{
			_indPtr[0 + i] = offset + 0;
			_indPtr[1 + i] = offset + 1;
			_indPtr[2 + i] = offset + 2;

			_indPtr[3 + i] = offset + 2;
			_indPtr[4 + i] = offset + 3;
			_indPtr[5 + i] = offset + 0;

			offset += 4;
		}

		Bind();
		SetIndicies(_indPtr);

		delete[] _indPtr;
	}

	GLIndexBuffer::GLIndexBuffer(unsigned int* const indicies)
		: m_Id(0)
	{
		glGenBuffers(1, &m_Id);

		SetIndicies(indicies);
	}

	void GLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}

	void GLIndexBuffer::Delete()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void GLIndexBuffer::SetIndicies(unsigned int* const indicies)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies) * 6 * sizeof(int), indicies, GL_STATIC_DRAW);
	}

}}
