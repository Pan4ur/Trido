#include "UI.h"

namespace UI
{
	using Render = std::function<void()>;
	using Input = std::function<void(GLFWwindow*)>;
	using Event = std::function<void()>;
	Window::Window(Render renderFunc, Input inputFunc, Event eventFunc)
		: RenderCallback(renderFunc), InputCallback(inputFunc), EventCallback(eventFunc) {
	}
	template<class Object, class Method>
	GUI_Element::GUI_Element(glm::vec2 point1, glm::vec2 point2, Object* OnMouseHoverObj, Method onMouseHoverMethod,
		Object* LeftMouseButtonPressedObj, Method LeftMouseButtonPressedMethod,
		Object* RightMouseButtonPressedObj, Method RightMouseButtonPressedMethod) {
		OnMouseHover = std::bind(OnMouseHoverMethod, OnMouseHoverObj);
		LeftMouseButtonPressed = std::bind(LeftMouseButtonPressedMethod, LeftMouseButtonPressedObj);
		RightMouseButtonPressed = std::bind(RightMouseButtonPressedMethod, RightMouseButtonPressedObj);
	}
	bool GUI_Element::IsInBounds(glm::vec2)
	{
		// надо проверить какие координаты при клике, чтобы понимать откуда считать координаты, а потом писать логику
		return true;
	}
}