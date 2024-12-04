#include "UI.h"

namespace UI
{
	using Render = std::function<void()>;
	using Input = std::function<void(GLFWwindow*)>;
	using Event = std::function<void()>;
	Window::Window(Render renderFunc, Input inputFunc, Event eventFunc)
		: RenderCallback(renderFunc), InputCallback(inputFunc), EventCallback(eventFunc) {
	}
}