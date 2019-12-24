#pragma once
#include "Graphics/Api/VertexBuffer.h"

namespace Fireblast {
	namespace OpenGL {
		
		class GLVertexBuffer : public VertexBuffer
		{
		private:
			unsigned int m_Id;
			VertexBufferLayout m_BufferLayout;
		public:
			GLVertexBuffer();

			virtual void Bind() override;
			virtual void Delete() override;
			void SetBufferData(const int size, const void* data, const BufferUsage usage) override;
			virtual void SetLayout(const VertexBufferLayout& layout) override;

		public:
			inline virtual const VertexBufferLayout& GetLayout() const override 
			{
				return m_BufferLayout;
			}

		public:
			void SetAttribPointer(const int index, const int size, const bool normalised, const int verticeSize, const void* pointer);
			void EnableAttribPointer(const int index);		

			
		};
	}
}

