#include "../srcs/Includes.hpp"
void			Client::list(Message *m){
	(void)m;
	std::cout << GREEN << ">\tlist function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}
