#pragma once
#include "Application/KeyCodes.h"
#include "Event/Event.h"
#include <sstream>

namespace Fireblast {

	class KeyPressedEvent : public Event {
	private:
		KeyCodes m_Key;
		int m_ScanCode;
		int m_Mods;
	public:
		KeyPressedEvent(KeyCodes key, int scancode, int mods)
			: m_Key(key), m_ScanCode(scancode), m_Mods(mods) {};
	public:
		inline virtual const char* GetName() const override
		{
			return std::string("KeyPressedEvent").c_str();
		}

		inline virtual std::string ToString() const override {
			std::stringstream ss;

			ss << "KeyPressedEvent " << m_Key;

			return ss.str();
		}
	};

	class KeyReleasedEvent : public Event {
	private:
		KeyCodes m_Key;
		int m_ScanCode;
		int m_Mods;
	public:
		KeyReleasedEvent(KeyCodes key, int scancode, int mods)
			: m_Key(key), m_ScanCode(scancode), m_Mods(mods) {};
	public:
		inline virtual const char* GetName() const override
		{
			return std::string("KeyReleasedEvent").c_str();
		}

		inline virtual std::string ToString() const override {
			std::stringstream ss;

			ss << "KeyReleasedEvent " << m_Key;

			return ss.str();
		}
	};

	class KeyRepeatEvent : public Event {
	private:
		KeyCodes m_Key;
		int m_ScanCode;
		int m_Mods;
	public:
		KeyRepeatEvent(KeyCodes key, int scancode, int mods)
			: m_Key(key), m_ScanCode(scancode), m_Mods(mods) {};
	public:
		inline virtual const char* GetName() const override
		{
			return std::string("KeyRepeatEvent").c_str();
		}

		inline virtual std::string ToString() const override {
			std::stringstream ss;

			ss << "KeyRepeatEvent " << m_Key;

			return ss.str();
		}
	};

}