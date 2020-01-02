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
				glVertexAttribPointer(element.Index, element.Size, GLRenderCommands::PropertyToOpengl(element.Type), element.Normalised, layout.GetStride(), element.DataPointer);
				glEnableVertexAttribArray(element.Index);
			}
		}

		void GLVertexArray::SetIndexBuffer(IndexBuffer* const indexBuffer)
		{
			indexBuffer->Bind();
		}

		void GLVertexArray::DrawArrays(const Fireblast::RenderPrimitives primitive, const unsigned int offset, const unsigned int count)
		{
			glDrawArrays(GLRenderCommands::PropertyToOpengl(primitive), offset, count);
		}

		void GLVertexArray::DrawIndicies(const Fireblast::RenderPrimitives primitive, const unsigned int count)
		{
			glDrawElements(GLRenderCommands::PropertyToOpengl(primitive), count, GL_UNSIGNED_INT, NULL);
		}


	}
}

