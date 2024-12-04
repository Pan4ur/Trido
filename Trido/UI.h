#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
		bool LockInput = false;
	};
}