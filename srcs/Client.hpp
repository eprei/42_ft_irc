#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Includes.hpp"

class Server;

class Client
{
	public:

		// Client();
		Client(Server *server);
		Client(Client &other);
		Client &operator=(Client &other);
		~Client();

		void				setId(int id);
		void				setNickname(std::string nickname);
		void				setUsername(std::string username);
		void				setHostname(std::string hostname);
		void				setLastCommunication(std::time_t lastCommunication);
		void				setSocket(int socket);
		void				setAddress(struct sockaddr_in address);
		void				setBuf(std::string buf);
		int					getMaxId( void ) const ;

		int					getId( void ) const;
		std::string			getNickname( void ) const;
		std::string			getUsername( void ) const;
		std::string			getHostname( void ) const;
		std::string			getRealname( void ) const;
		std::time_t			getlastCommunication( void ) const;
		int					getSocket( void ) const;
		struct sockaddr_in	getAddress( void ) const;

		//Parsing
		std::string			getBuf( void ) const;
		void				execCmd(Message *m);
		void				process_buffer(const std::string& message);

		// CMDS
		void				nick(Message *m);
		void				user(Message *m);
		void				pass(Message *m);
		void				join(Message *m);
		void				quit(Message *m);
		void				list(Message *m);
		void				part(Message *m);
		void				privmsg(Message *m);
		void				ping(Message *m);
		void				kick(Message *m);
		void				cap(Message *m);
		void				notice(Message *m);
		void				mode(Message *m);
		void				pong(Message *m);
		void				whois(Message *m);

	private:

		int					_id;
		std::string 		_nickname;
		std::string 		_username;
		std::string 		_hostname;
		std::string 		_realname;
		bool				_isRegistered;
		std::time_t			_lastCommunication;
		int 				_socket;
		struct sockaddr_in	_address;
		std::string			_buf;
		static int			_maxId;
		Server				*_server;

};

std::ostream	&operator<<( std::ostream & o, Client const & rhs );

#endif
