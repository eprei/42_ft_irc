#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <ctime>
# include <netinet/in.h>

class Client
{
	public:

		Client();
		Client(Client &other);
		Client &operator=(Client &other);
		~Client();

	private:

		int					_id;
		std::string 		_nickname;
		std::string 		_username;
		std::string 		_hostname;
		bool				_operator;
		std::time_t			_lastCommunication;
		int 				_socket;
		struct sockaddr_in	_address;
	};

#endif
