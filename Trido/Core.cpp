#include "Core.h"

namespace Core
{
	Core::Core()
	{
		glfwInit();
		logger.print(Log_type::INFO, "Core run");
		GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
		glfwGetMonitorContentScale(primary_monitor, &sysdata.monitor_scaleX, &sysdata.monitor_scaleY);
		settings.monitory_scaleX = sysdata.monitor_scaleX;
		settings.monitory_scaleY= sysdata.monitor_scaleY;

		sysdata.video_mode = glfwGetVideoMode(primary_monitor);
		settings.video_mode = sysdata.video_mode;

		window = glfwCreateWindow(settings.video_mode->width, settings.video_mode->height, "Trido", NULL, NULL);
		glfwMakeContextCurrent(window);

	}
	void Core::Loop()
	{
		while (!glfwWindowShouldClose(window))
			Pipeline();
	}
	void Core::Pipeline()
	{
		
	}
}