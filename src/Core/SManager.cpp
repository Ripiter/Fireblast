#include "fbpch.h"
#include "Core/SManager.h"

namespace Fireblast
{
	std::shared_ptr<SManager> SManager::s_Instance = std::make_shared<SManager>();
}