#include "fbpch.h"
#include "Core/SManager.h"

namespace Fireblast
{
	std::shared_ptr<SManager> SManager::s_Instance = std::make_shared<SManager>();
	
	SManager::SManager()
	{

	}

	SManager::~SManager()
	{
		for (auto _ : m_Managers)
			delete _;

		m_Managers.clear();
	}
}