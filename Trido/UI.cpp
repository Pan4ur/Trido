#include "UI.h"

namespace UI
{
	template <class O, class M>
	Window::Window(O* object, M* render, M* input, M* event)
	{
		this->Render = std::bind(method, object);
		this->Input = std::bind(method, object);
		this->Event = std::bind(method, object);
	}
}