#include "../srcs/Includes.hpp"

void			Client::notice(Message *m){
	(void)m;
	std::cout << FC(GREEN, ">\tnotice function executed ") <<"by client id: " << _id << "\t<" << std::endl;
}
