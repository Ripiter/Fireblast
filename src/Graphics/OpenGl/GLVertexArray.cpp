#include "fbpch.h"
#include "GLVertexArray.h"
#include "glad/glad.h"

namespace Fireblast {
	namespace OpenGL {

		GLVertexArray::GLVertexArray() : m_Id(0)
		{
			glGenVertexArrays(1, &m_Id);
		}

		void GLVertexArray::Bind()
		{
			glBindVertexArray(m_Id);
		}

		void GLVertexArray::Delete()
		{
			glDeleteVertexArrays(1, &m_Id);
		}

		void GLVertexArray::SetAttribDivider(unsigned int index, unsigned int divider)
		{
			glVertexAttribDivisor(index, divider);
		}
	}
}

