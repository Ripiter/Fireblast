#pragma once
#include "fbpch.h"

namespace Fireblast {
	class Event {
	public:
		bool Handled = false;
		virtual const char* GetName() const = 0;

		virtual std::string ToString() const { return GetName(); }
	};
}