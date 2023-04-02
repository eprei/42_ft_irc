#include "../srcs/Includes.hpp"

void			Client::mode(Message *m){
	(void)m;
	std::cout << GREEN << ">\tmode function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}
