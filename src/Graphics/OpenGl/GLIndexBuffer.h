#pragma once
#include "Graphics/Api/IndexBuffer.h"

namespace Fireblast { namespace OpenGL {
	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(const unsigned int size);
		GLIndexBuffer(unsigned int* const indicies);
	public:
		virtual void Bind() override;
		virtual void Delete() override;

	private:
		void SetIndicies(unsigned int* const indicies);
	private:
		unsigned int m_Id;
	};
}}

