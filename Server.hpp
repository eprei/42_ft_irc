#ifndef SERVER_HPP
# define SERVER_HPP

# include "Includes.hpp"
# include <iostream>
# include "Client.hpp"
# include <vector>

class Server
{
	public:

		Server();
		Server(Server &other);
		Server &operator=(Server &other);
		~Server();

		bool checkArgs(int argc, char **argv);
		bool printCorrectUse() const;
		void printHelp() const; // TO DO: print all possible commands to be used by the Client in our Server

		void loop();

	private:

		std::string				_password;
		int						_port;
		std::vector<Client *>	_clientsList;
};

#endif
