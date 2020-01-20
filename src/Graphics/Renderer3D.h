#pragma once
#include "Core/System.h"

namespace Fireblast
{
	class Renderer3D : public System
	{
	private:
		void InitRenderer();

	protected:
		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnDraw() override;
	};
}

