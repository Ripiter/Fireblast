#pragma once
#include "Graphics/Api/VertexBuffer.h"

namespace Fireblast {
	namespace OpenGL {
		
		class GLVertexBuffer : public VertexBuffer
		{
		private:
			unsigned int m_Id;

		public:
			GLVertexBuffer();

			// Inherited via VertexBuffer
			virtual void Init() override;
			virtual void Bind() override;
			virtual void Delete() override;
			virtual void ReplaceData(const float* data) override;
		};
	}
}

