#include "fbpch.h"
#include "ResourceManager.h"

#include "Graphics/Api/RenderAPI.h"

namespace Fireblast
{
	ResourceManager::ResourceManager()
		: m_Textures(), m_Shaders()
	{
	}

	ResourceManager::~ResourceManager()
	{
		for (auto _ : m_Textures)
			delete _.second;

		for (auto _ : m_Shaders)
			delete _.second;
	}

	void ResourceManager::LoadTexture(const std::string name, const std::string path)
	{
		if (!m_Textures.insert({ name, RenderAPI::GetApi()->CreateTexture(path) }).second)
			FB_CORE_ERROR("Could not load texture, name already exists!");
	}

	Texture* ResourceManager::GetTexture(const std::string name) const
	{
		auto& _pair = m_Textures.find(name);

		if (_pair->second)
			return _pair->second;
		else
			return nullptr;
	}

	// TODO: Change this when the shader will be custom.
	void ResourceManager::LoadShader(const std::string name, const std::string vertexPath, const std::string fragmentPath)
	{
		if (!m_Shaders.insert({ name, RenderAPI::GetApi()->CreateShader(vertexPath, fragmentPath) }).second)
			FB_CORE_ERROR("Could not load shader, name already exists!");
	}

	void ResourceManager::OnStart()
	{
	}

	void ResourceManager::OnUpdate()
	{
	}

	void ResourceManager::OnDraw()
	{
	}
}