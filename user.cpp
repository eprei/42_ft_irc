#include "Client.hpp"
#include "Server.hpp"

void			Client::user(Message *m){
	(void)m;

	std::cout << GREEN << ">\tuser function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}