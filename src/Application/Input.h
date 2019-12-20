#pragma once
#include "GLFW/glfw3.h"
#include "Application/KeyCodes.h"
#include "Application/MouseButtons.h"
#include <utility>

namespace Fireblast {

	class Input {
	private:
		static GLFWwindow* s_Window;

	public:
		inline static bool IsKeyPressed(KeyCodes key) {
			auto state = glfwGetKey(s_Window, static_cast<int32_t>(key));
			return (state == 1 || state == 2);
		}

		inline static bool IsMousePressed(MouseButtons button) {
			auto state = glfwGetMouseButton(s_Window, static_cast<int32_t>(button));
			return (state == 1 || state == 2);
		}

		inline static std::pair<float, float> GetMousePosition() {
			double x;
			double y;

			glfwGetCursorPos(s_Window, &x, &y);

			return { (float)x, (float)y };
		}

		inline static void SetWindow(void* window) { s_Window = static_cast<GLFWwindow*>(window); }
	};
}