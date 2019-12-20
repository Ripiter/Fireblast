#pragma once
#include "Event/Event.h"
#include <sstream>

namespace Fireblast {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		// Inherited via Event
		inline virtual const char* GetName() const override {
			return std::string("WindowCloseEvent").c_str();
		};
	};

	class WindowResizeEvent : public Event 
	{
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) 
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << "x" << m_Height;
			return ss.str();
		}

		// Inherited via Event
		inline virtual const char* GetName() const override {
			return std::string("WindowResizeEvent").c_str();
		};
	};

	class WindowFocusEvent : public Event {
	private:
		bool m_Focused;
	public:
		inline bool IsFocused() const { return m_Focused; }
	public:
		WindowFocusEvent(bool _focused) : m_Focused(_focused) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowFocusEvent: Focused: " << m_Focused;
			return ss.str();
		}

		// Inherited via Event
		inline virtual const char* GetName() const override {
			return std::string("WindowFocusEvent").c_str();
		};
	};
}