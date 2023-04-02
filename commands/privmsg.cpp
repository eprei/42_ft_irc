#include "../srcs/Includes.hpp"

void			Client::privmsg(Message *m){
	(void)m;
	std::cout << GREEN << ">\tprivmsg function executed " << RESET <<"by client id: " << _id << "\t<" << std::endl;
}
