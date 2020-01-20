#include "fbpch.h"
#include "ResourceManager.h"
#include "Utils/Performance.h"

#include "Graphics/Api/RenderAPI.h"

namespace Fireblast
{
	ResourceManager::ResourceManager()
		: m_Textures(), m_Shaders() {}

	ResourceManager::~ResourceManager()
	{
		for (auto _ : m_Textures)
			delete _.second;

		for (auto _ : m_Shaders)
			delete _.second;
	}

	void ResourceManager::LoadTexture(const std::string name, const std::string path)
	{
		FB_PERFORMANCE_PROFILE();

		if (!m_Textures.insert({ name, RenderAPI::GetApi()->CreateTexture(path) }).second)
			FB_CORE_ERROR("Could not load texture, name already exists!");

	}

	void ResourceManager::LoadTexture(const std::string name, int width, int height, void* data)
	{
		FB_PERFORMANCE_PROFILE();

		if (!m_Textures.insert({ name, RenderAPI::GetApi()->CreateTexture(data, width, height) }).second)
			FB_CORE_ERROR("Could not load texture, name already exists!");

	}

	Texture* ResourceManager::GetTexture(const std::string name) const
	{
		FB_PERFORMANCE_PROFILE();

		auto& _pair = m_Textures.find(name);

		if (_pair->second)
			return _pair->second;
		else
			return nullptr;

	}

	Shader* ResourceManager::GetShader(const std::string name) const
	{
		FB_PERFORMANCE_PROFILE();

		auto& _pair = m_Shaders.find(name);

		if (_pair->second)
			return _pair->second;
		else
			return nullptr;

	}

	// TODO: Change this when the shader will be custom.
	void ResourceManager::LoadShader(const std::string name, const std::string vertexPath, const std::string fragmentPath)
	{
		FB_PERFORMANCE_PROFILE();

		if (!m_Shaders.insert({ name, RenderAPI::GetApi()->CreateShader(vertexPath, fragmentPath) }).second)
			FB_CORE_ERROR("Could not load shader, name already exists!");

	}

	void ResourceManager::LoadShader(const std::string& name, const char* vertexSource, const char* fragmentSource)
	{
		FB_PERFORMANCE_PROFILE();

		if (!m_Shaders.insert({ name, RenderAPI::GetApi()->CreateShader(vertexSource, fragmentSource) }).second)
			FB_CORE_ERROR("Could not load shader, name already exists!");

	}

	void ResourceManager::LoadDefaultResources()
	{
		FB_PERFORMANCE_PROFILE();

		uint32_t whiteTexture = 0xffffffff;
		LoadTexture("DefaultTexture", 1, 1, &whiteTexture);

		const char* default2DVertexSource =
			"#version 330 core\n"
			"layout(location = 0) in vec3 pos;\n"
			"layout(location = 1) in vec4 color;\n"
			"layout(location = 2) in vec2 Uv;\n"
			"layout(location = 3) in float TextureId;\n"

			"out vec4 outColor;\n"
			"out vec2 outUv;\n"
			"out float outTextureId;\n"

			"uniform mat4 projView;\n"

			"void main()\n"
			"{\n"
			"gl_Position = projView * vec4(pos, 1.0);\n"
			"outColor = color;\n"
			"outUv = Uv;\n"
			"outTextureId = TextureId;\n"
			"}\n";

		const char* default2DFragmentSource =
			"#version 330 core\n"

			"in vec4 outColor;\n"
			"in vec2 outUv;\n"
			"in float outTextureId;\n"

			"out vec4 FragColor;\n"

			"uniform sampler2D[32] textures;\n"

			"void main()\n"
			"{\n"
			"int tid = int(outTextureId);\n"
			"FragColor = texture(textures[tid], outUv) * outColor;\n"
			"}\n";

		LoadShader("Default2DShader", default2DVertexSource, default2DFragmentSource);

	}


	void ResourceManager::OnStart()
	{
		LoadDefaultResources();
	}

	void ResourceManager::OnUpdate()
	{
	}

	void ResourceManager::OnDraw()
	{
	}
}