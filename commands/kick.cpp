#include "../srcs/Includes.hpp"

void			Client::kick(Message *m){
	(void)m;
	std::cout << FC(GREEN, ">\tkick function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
}
