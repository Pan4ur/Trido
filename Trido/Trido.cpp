#include "io.h"
#include "logger.h"
#include "lua.h"

int main(int argc, char** argv)
{
	Logger logger;
	logger.print(Log_type::INFO, "Program successfully started");
	return 0;
}