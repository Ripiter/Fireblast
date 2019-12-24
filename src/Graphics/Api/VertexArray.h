#pragma once

#include "Graphics/Api/RenderProperties.h"
#include "Graphics/Api/VertexBuffer.h"

namespace Fireblast {

	class VertexArray {
	public:
		virtual void Bind() = 0;
		virtual void Delete() = 0;

		virtual void SetVertexBuffer(const VertexBuffer* vertexBuffer) = 0;

		virtual void DrawArrays(RenderPrimitives primitive, const unsigned int offset, const unsigned int count) = 0;
	};
}