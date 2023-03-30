#include "Client.hpp"
#include "Server.hpp"

void	Client::nick(Message *m){
	(void)m;

	std::cout << GREEN << ">\tnick function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
	if (_server->isNickUsed(m->params[0]))
	{
		std::cout << "the nick is already used" << std::endl;
		return;
	}
	std::cout << "the nick is available" << std::endl;
	this->setNickname(m->params[0]);

}

// bool	checkValidNickName(std::string nickname)
// {
// 	if (nickname.length() > 9)
// 		return false;
// 	for (size_t i = 0; i < nickname.length(); i++)
// 	{
// 		if (!std::strchr(NICKNAME_VALID_CHAR, nickname[i]))
// 			return false;
// 	}
// 	return true;
// }
