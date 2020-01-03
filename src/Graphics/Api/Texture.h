#pragma once

namespace Fireblast {

	class Texture
	{
	protected:
		unsigned int m_Id;
		unsigned int m_Width;
		unsigned int m_Height;
	public:
		virtual void ActivateTexture(const unsigned int slot) = 0;
		virtual void SetData(const unsigned char* data, const unsigned int width, const unsigned int height) = 0;
		virtual void Bind() = 0;
		virtual void Delete() = 0;

		inline const unsigned int GetWidth() const { return m_Width; }
		inline const unsigned int GetHeight() const { return m_Height; }
	};
}