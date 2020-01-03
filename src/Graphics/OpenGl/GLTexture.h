#pragma once
#include "Graphics/Api/Texture.h"

namespace Fireblast { namespace OpenGL {

	class GLTexture : public Texture
	{
	public:
		GLTexture();

		virtual void ActivateTexture(const unsigned int slot) override;
		virtual void SetData(const unsigned char* data, const unsigned int width, const unsigned int height) override;
		virtual void Bind() override;
		virtual void Delete() override;
	private:
		void SetFiltering();
	};
}}