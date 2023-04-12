#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Includes.hpp"

class Client;

class Channel
{
	private:

	    Client *_oper;
		std::string	_name;
		std::string _topic;
		std::string _modes;
	    std::vector<Client*> _members;
		std::vector<Client*> _invited;
	    // std::vector<Client*> oper;

	public:

		Channel(Client &owner, std::string name);
		Channel(Channel &other);
		Channel &operator=(Channel &other);
		~Channel();

  		std::string				getName() const;
		std::string				getMembersNicks();
		std::vector<Client*>	getMembers() const;
		void	addClient(Client *client);
		void	removeClient(Client *client);
		bool	hasClient(Client *client) const;
		bool	isEmpty() const;
		bool	isOperator(Client *client) const;


		void		setTopic(std::string topic);
		std::string	getTopic() const;
		std::string	setModes(std::string to_add);
		std::string	getModes() const;
		bool		hasModes(std::string m) const;
		bool		isInvited(Client *client) const;
		void		addInvited(Client* client);
};

std::ostream		&operator<<(std::ostream & o, Channel const & rhs );

#endif

