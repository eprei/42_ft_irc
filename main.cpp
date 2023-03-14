#include "Includes.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

int main(int argc, char **argv)
{
	Server servIrc;

	if (servIrc.checkArgs(argc, argv))
		return (EXIT_FAILURE);
	if (servIrc.launchServ())
		return (EXIT_FAILURE);
	return EXIT_SUCCESS;
}
