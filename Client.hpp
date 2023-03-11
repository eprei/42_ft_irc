#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <ctime>

class Client
{
	public:

		Client();
		Client(Client &other);
		Client &operator=(Client &other);
		~Client();

	private:

		int			_id;
		std::string _nickname;
		std::string _realname;
		std::string _username;
		std::string _hostname;
		bool		_operator;
		std::time_t _lastCommunication;
};

#endif
