#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <functional>

// id means z-index in context of windows, higher id is upper
typedef unsigned int id;

namespace UI
{
	class Window
	{
	public:
		using Render = std::function<void()>;
		using Input = std::function<void(GLFWwindow*)>;
		using Event = std::function<void()>;
		Window(Render renderFunc, Input inputFunc, Event eventFunc);
		Render RenderCallback;
		Input InputCallback;
		Event EventCallback;
		// permit to receive input from lower windows
		enum InputRule { ALLOW_ALL, ALLOW_MOUSE, FORBID_ALL }LockInput = FORBID_ALL;
	};
	class GUI_Element
	{
		// ivec set mouse button click borders
		glm::vec2 point1;
		glm::vec2 point2;

		// check if point is in borders of gui object
		virtual bool IsInBounds(glm::vec2);
		
		using CallBack = std::function<void()>;

		CallBack OnMouseHover;
		CallBack LeftMouseButtonPressed;
		CallBack RightMouseButtonPressed;

		template<class Object, class Method>
		GUI_Element(glm::vec2 point1, glm::vec2 point2, Object* OnMouseHoverObj, Method onMouseHoverMethod, 
			Object* LeftMouseButtonPressedObj, Method LeftMouseButtonPressedMethod, 
			Object* RightMouseButtonPressedObj, Method RightMouseButtonPressedMethod);
	};
	class Button : public GUI_Element
	{
		
	};
}