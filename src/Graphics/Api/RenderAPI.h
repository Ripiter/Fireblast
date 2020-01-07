#pragma once
#include "Graphics/Api/RenderCommands.h"
#include "Graphics/OpenGl/GLRenderCommands.h"
#include "Application/Log.h"
#include <memory>

namespace Fireblast {

	enum class RenderVendor {
		none,
		Opengl,
		DirectX
	};

	class RenderAPI {
	private:
		static std::shared_ptr<RenderCommands> m_RenderApi;
	public:
		inline static void Create(const RenderVendor api) {
			switch (api) {
			case RenderVendor::none:
			case RenderVendor::DirectX:
				FB_CORE_ERROR("{0} is not supported!", api);
				break;
			case RenderVendor::Opengl:
				RenderAPI::m_RenderApi = std::make_shared<OpenGL::GLRenderCommands>();
				break;
			}
		}
	public:
		inline static std::shared_ptr<RenderCommands>& GetApi() { return m_RenderApi; }

	};
}