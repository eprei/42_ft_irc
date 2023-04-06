#include "../srcs/Includes.hpp"

void			Client::privmsg(Message *m){
	(void)m;
	std::cout << FC(GREEN, ">\tprivmsg function executed ") <<"by client id: " << _id << "\t<" << std::endl;
}
