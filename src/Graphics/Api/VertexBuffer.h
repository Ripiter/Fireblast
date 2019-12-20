#pragma once
namespace Fireblast {
	class VertexBuffer {
	public:
		virtual void Init() = 0;
		virtual void Bind() = 0;
		virtual void Delete() = 0;
		virtual void ReplaceData(const float *data) = 0;
	};
}