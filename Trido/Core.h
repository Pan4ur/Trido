#pragma once

#include <string>

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
	class Core
	{
	public:
		Core();
		std::string getVersion() { return version; }

		Logger logger;
	private:
		std::string version = "0.0.1pa";
	};
}