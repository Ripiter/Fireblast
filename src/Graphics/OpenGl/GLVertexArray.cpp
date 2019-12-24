#include "fbpch.h"
#include "GLVertexArray.h"
#include "Graphics/Api/VertexBuffer.h"
#include "Graphics/OpenGl/GLRenderCommands.h"
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

		void GLVertexArray::SetVertexBuffer(const VertexBuffer* vertexBuffer) 
		{
			const auto& layout = vertexBuffer->GetLayout();

			for (const auto& element : layout)
			{
				glVertexAttribPointer(element.Index, element.Size, element.Type, element.Normalised, element.Stride, element.DataPointer);
				glEnableVertexAttribArray(element.Index);
			}
		}

		void GLVertexArray::DrawArrays(const Fireblast::RenderPrimitives primitive, const unsigned int offset, const unsigned int count)
		{
			glDrawArrays(GLRenderCommands::PropertyToOpengl(primitive), offset, count);
		}


	}
}

