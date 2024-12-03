#pragma once

#include "UI.h"
#include <string>
#include <GL/freeglut.h>
#include <rapidxml.hpp>
#include <lua.hpp>
#include <functional>
#include <vector>

#include "IO.h"
#include "StateManager.h"
#include "EventManager.h"
#include "CmdManager.h"
#include "Logger.h"

using namespace IO;
using namespace StateManager;
using namespace EventManager;
using namespace CmdManager;
using namespace UI;

namespace Core
{
	unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	unsigned int compileShader(unsigned int type, const char* source);

	class Settings
	{
	public:
		float monitory_scaleX = 0;
		float monitory_scaleY = 0;
		const GLFWvidmode* video_mode;
	};
	struct Resources
	{
		Resources();
		struct Texture
		{
			int width;
			int height;
			int channels;
			GLuint tex_id = 0;
		};
		void Load();
		bool LoadTextureFromFile(const char* filename, Texture* texture);
		std::vector<Texture>textures;
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
		void Render();
		void Exit();
		std::string getVersion() { return version; }
		void Input(GLFWwindow* window);

		Logger logger;
		GLFWwindow* gl_window = nullptr;
		Settings settings;
		Resources res;
		System sysdata;
		std::vector<Window> windows;

		static void RenderMainWindow();
		static void InputMainWindow(GLFWwindow* window);
		static void EventMainWindow();
		
	private:
		std::string version = "0.0.1pa";
	};
}