#pragma once
#include "Graphics/Api/VertexArray.h"

namespace Fireblast {
	namespace OpenGL {
		class GLVertexArray : public VertexArray
		{
		private:
			unsigned int m_Id;
		public:
			GLVertexArray();

			// Inherited via VertexArray
			virtual void Bind() override;
			virtual void Delete() override;
			virtual void SetAttribDivider(unsigned int index, unsigned int divider) override;
		};
	}
}

