#pragma once
#include <vector>

namespace Fireblast 
{
	struct VertexBufferElement 
	{
	public:
		unsigned int Index;
		unsigned int Size;
		Fireblast::ShaderType Type;
		bool Normalised;
		void* DataPointer;
	public:
		VertexBufferElement() = default;

		VertexBufferElement(const unsigned int index, const unsigned int size, const Fireblast::ShaderType type, const bool normalised)
			: Index(index), Size(size), Type(type), Normalised(normalised), DataPointer(0) {}
	};

	class VertexBufferLayout 
	{
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride = 0;

	public:
		VertexBufferLayout() {}

		VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements) : m_Elements(elements)
		{
			CalculateStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

		std::vector<VertexBufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexBufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<VertexBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<VertexBufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:

		inline void CalculateStride()
		{
			unsigned long offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements )
			{
				element.DataPointer = (void*)m_Stride;
				m_Stride += element.Size * sizeof(float);
			}
		}
	};
}