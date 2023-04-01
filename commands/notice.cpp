#include "../srcs/Includes.hpp"

void			Client::notice(Message *m){
	(void)m;
	std::cout << GREEN << ">\tnotice function executed " << RESET <<"by client id: " << _id << "\t<" << std::endl;
}