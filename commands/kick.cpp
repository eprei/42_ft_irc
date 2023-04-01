#include "../srcs/Includes.hpp"

void			Client::kick(Message *m){
	(void)m;
	std::cout << GREEN << ">\tkick function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}