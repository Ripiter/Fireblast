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
		void LoadTexture(const std::string name, int width, int height, void* data);

		void LoadShader(const std::string name, const std::string vertexPath, const std::string fragmentPath);
		void LoadShader(const std::string& name, const char* vertexSource, const char* fragmentSource);

		Texture* GetTexture(const std::string name) const;
		Shader* GetShader(const std::string name) const;

	private:
		void LoadDefaultResources();

	protected:
		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnDraw() override;
	};

}

