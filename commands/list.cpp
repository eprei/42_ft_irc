#include "../srcs/Includes.hpp"
void			Client::list(Message *m){
	(void)m;
	std::cout << FC(GREEN, ">\tlist function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
}
