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

		/*void GLVertexArray::SetAttribPointer<T>(const int index, const int size, bool normalised, int primateSize, const void* pointer)
		{
			glVertexAttribPointer(index, size, GL_FLOAT, normalised, primateSize * sizeof(T), (void*)0);
		}*/

		void GLVertexArray::EnableAttribPointer(const int index)
		{
			glEnableVertexAttribArray(index);
		}
	}
}

