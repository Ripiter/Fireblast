#include "fbpch.h"
#include "GLVertexBuffer.h"
#include "glad/glad.h"

namespace Fireblast {
	namespace OpenGL {

		GLVertexBuffer::GLVertexBuffer() : m_Id(0)
		{
			glGenBuffers(1, &m_Id);
		}

		void GLVertexBuffer::Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		}

		void GLVertexBuffer::Delete()
		{
			glDeleteBuffers(1, &m_Id);
		}

		void GLVertexBuffer::ReplaceData(const float *data)
		{
		}

		void GLVertexBuffer::Init() {

		}


	}
}