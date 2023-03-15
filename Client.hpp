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

		void				setId(int id);
		void				setNickname(std::string nickname);
		void				setUsername(std::string username);
		void				setHostname(std::string hostname);
		void				setOperator(bool isOperator);
		void				setLastCommunication(std::time_t lastCommunication);
		void				setSocket(int socket);
		void				setAddress(struct sockaddr_in address);
		void				setBuf(std::string buf);

		int					getId( void ) const;
		std::string			getNickname( void ) const;
		std::string			getUsername( void ) const;
		std::string			getHostname( void ) const;
		bool				getOperator( void ) const;
		std::time_t			getlastCommunication( void ) const;
		int					getSocket( void ) const;
		struct sockaddr_in	getAddress( void ) const;
		std::string			getBuf( void ) const;

	private:

		int					_id;
		std::string 		_nickname;
		std::string 		_username;
		std::string 		_hostname;
		bool				_operator;
		std::time_t			_lastCommunication;
		int 				_socket;
		struct sockaddr_in	_address;
		std::string			_buf;

		static int			_maxId;

};

std::ostream	&operator<<( std::ostream & o, Client const & rhs );

#endif
