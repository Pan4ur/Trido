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
		template <class O, class M>
		Window(O* object, M* render, M* input, M* event);
		void (*Render)() = nullptr;
		void (*Input)(GLFWwindow* window) = nullptr; 
		void (*Event)() = nullptr;
		// permit to receive input from lower windows
		bool LockInput = false;
	};
}