#pragma once
#include "Graphics/Api/VertexArray.h"

namespace Fireblast {
	namespace OpenGL {

		class GLVertexArray : public VertexArray
		{
		private:
			unsigned int m_Id;
			VertexBuffer* m_VertexBuffer;
		public:
			GLVertexArray();

			// Inherited via VertexArray
			virtual void Bind() override;
			virtual void Delete() override;

			virtual void SetVertexBuffer(const VertexBuffer* vertexBuffer) override;

			virtual void DrawArrays(const Fireblast::RenderPrimitives primitive, const unsigned int offset, const unsigned int count) override;

		};
	}
}

