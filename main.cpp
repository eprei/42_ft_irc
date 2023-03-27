#include "Includes.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

// void	signal_handler1(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_server_is_on = FALSE;
// 		std::cout << "You have decided to terminate the server with " << RED << "SIGINT" << RESET << std::endl;
// 	}
// 	if (sig == SIGKILL)
// 	{
// 		g_server_is_on = FALSE;
// 		std::cout << "You have decided to terminate the server with " << RED << "SIGKILL" << RESET << std::endl;
// 	}
// }

int main(int argc, char **argv)
{
	Server servIrc;

	// signal(SIGINT, signal_handler1);
	if (servIrc.checkArgs(argc, argv))
		return (EXIT_FAILURE);
	if (servIrc.launchServ())
		return (EXIT_FAILURE);
	// TO DO: free all mallocs Clients, may be we can do at Server::~Server()
	return EXIT_SUCCESS;
}
