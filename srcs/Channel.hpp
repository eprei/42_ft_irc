#ifndef CHANNEL_HPP
# define CHANNEL_HPP

// # include <iostream>
// # include <vector>
// # include <string>
# include "Includes.hpp"

//   Channel: Esta clase representaría a un canal de chat en el servidor.
//   Sería responsable de mantener una lista de clientes que se han unido al canal,
//   enviar mensajes a todos los clientes en el canal,
//   y gestionar las restricciones de acceso al canal.
//   atributo _private: es privado o no el canal??

class Client;

class Channel
{
	private:

	    Client *_oper;
		std::string	_name;
		std::string _topic;
		std::string _modes;
	    std::vector<Client*> _members;
	    // std::vector<Client*> oper;

	public:

		Channel(Client &owner, std::string name);
		Channel(Channel &other);
		Channel &operator=(Channel &other);
		~Channel();

  		std::string				getName() const;
		std::vector<Client*>	getMembers() const;
		void	addClient(Client *client);
		void	removeClient(Client *client);
		bool	hasClient(Client *client) const;
		bool	isEmpty() const;

		bool	isOperator(Client *client) const;
		// void	addOperator(Client *to_add);
		// void	removeOperator(Client *to_del);

		void		setTopic(std::string topic);
		std::string	getTopic() const;
		std::string	getModes() const;


};

#endif
