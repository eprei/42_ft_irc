#include "Includes.hpp"

int main(int argc, char **argv)
{
	Server server;

	if (server.checkArgs(argc, argv))
		return (-1);
	server.loop();
	return 0;
}
