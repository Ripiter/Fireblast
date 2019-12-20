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

		public:
			/*template <typename T>
			void SetAttribPointer(const int index, const int size, bool normalised, int primateSize, const void* pointer);*/
			void EnableAttribPointer(const int index);
		};
	}
}

