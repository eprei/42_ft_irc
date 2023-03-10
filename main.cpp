#include "Includes.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

int main(int argc, char **argv)
{
	Server servIrc;

	if (servIrc.checkArgs(argc, argv))
		return (-1);
	servIrc.launchServ();
	return 0;
}
