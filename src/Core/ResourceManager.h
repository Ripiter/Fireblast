#pragma once
#include "Manager.h"
#include "Graphics/Api/Texture.h"
#include "Graphics/Api/Shader.h"

#include <unordered_map>

namespace Fireblast
{
	class ResourceManager : public Manager
	{
	private:
		std::unordered_map<std::string, Texture*> m_Textures;
		std::unordered_map<std::string, Shader*> m_Shaders;
	public:
		ResourceManager();
		~ResourceManager();

		void LoadTexture(const std::string name, const std::string path);
		void LoadShader(const std::string name, const std::string vertexPath, const std::string fragmentPath);

		Texture* GetTexture(const std::string name) const;
	protected:
		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnDraw() override;
	};

}

