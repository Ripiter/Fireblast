#pragma once
#include "Event/Event.h"
#include "Application/MouseButtons.h"
#include <sstream>

namespace Fireblast {

	class MousePressedEvent : public Event
	{
	private:
		MouseButtons m_Key;
		int m_Mods;
	public:
		MousePressedEvent(MouseButtons key, int mods)
			: m_Key(key), m_Mods(mods) {};
	public:
		inline virtual const char* GetName() const override
		{
			return std::string("MousePressedEvent").c_str();
		}

		inline virtual std::string ToString() const override {
			std::stringstream ss;

			ss << "MousePressedEvent " << m_Key;

			return ss.str();
		}
	};

	class MouseReleasedEvent : public Event
	{
	private:
		MouseButtons m_Key;
		int m_Mods;
	public:
		MouseReleasedEvent(MouseButtons key, int mods)
			: m_Key(key), m_Mods(mods) {};
	public:
		inline virtual const char* GetName() const override
		{
			return std::string("MouseReleasedEvent").c_str();
		}

		inline virtual std::string ToString() const override {
			std::stringstream ss;

			ss << "MouseReleasedEvent " << m_Key;

			return ss.str();
		}
	};

	class MouseRepeatEvent : public Event
	{
	private:
		MouseButtons m_Key;
		int m_Mods;
	public:
		MouseRepeatEvent(MouseButtons key, int mods)
			: m_Key(key), m_Mods(mods) {};
	public:

		inline virtual const char* GetName() const override {
			return std::string("MouseRepeatEvent").c_str();
		};

		inline virtual std::string ToString() const override {
			std::stringstream ss;

			ss << "MouseRepeatEvent " << m_Key;

			return ss.str();
		}
	};

}