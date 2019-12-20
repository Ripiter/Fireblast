#pragma once

namespace Fireblast {

	class VertexArray {
	public:
		virtual void Bind() = 0;
		virtual void Delete() = 0;
		virtual void SetAttribDivider(unsigned int index, unsigned int divider) = 0;
	};
}