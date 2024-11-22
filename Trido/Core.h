#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>

// internal headers
#include "IO.h"
#include "StateManager.h"
#include "EventManager.h"
#include "CmdManager.h"
#include "UI.h"
#include "Logger.h"

using namespace IO;
using namespace StateManager;
using namespace EventManager;
using namespace CmdManager;
using namespace UI;

namespace Core
{
	class Settings
	{
	public:
		float monitory_scaleX = 0;
		float monitory_scaleY = 0;
		const GLFWvidmode* video_mode;
	};
	class Resources
	{

	};
	class System
	{
	public:
		float monitor_scaleX = 0;
		float monitor_scaleY = 0;
		const GLFWvidmode* video_mode;
	};
	class Core
	{
	public:
		Core();
		void Loop();
		void Pipeline();
		std::string getVersion() { return version; }

		Logger logger;
		GLFWwindow* window = nullptr;
		Settings settings;
		Resources resources;
		System sysdata;
		
	private:
		std::string version = "0.0.1pa";
	};
}