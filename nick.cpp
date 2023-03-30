#include "Client.hpp"
#include "Server.hpp"
#include <cstring>
// 3.1.2 Nick message
//       Command: NICK  Parameters: <nickname>

//    NICK command is used to give user a nickname or change the existing one.

//    Numeric Replies:
//            ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//            ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
//            ERR_UNAVAILRESOURCE             ERR_RESTRICTED

//    Examples:
//    NICK Wiz                ; Introducing new nick "Wiz" if session is
//                            still unregistered, or user changing his
//                            nickname to "Wiz"

//    :WiZ!jto@tolsun.oulu.fi NICK Kilroy
//                            ; Server telling that WiZ changed his
//                            nickname to Kilroy.

//HACER (en principio no usado)??
// #define ERR_NICKCOLLISION(nick,user, host) nick + " :Nickname collision KILL from "+ user + "@" + host//436    
//          - Returned by a server to a client when it detects a
//            nickname collision (registered of a NICK that
//            already exists by another server).

// #define ERR_UNAVAILRESOURCE(resource) resource + "<nick/channel> :Nick/channel is temporarily unavailable" //437
//          - Returned by a server to a user trying to join a channel
//            currently blocked by the channel delay mechanism.

//          - Returned by a server to a user trying to change nickname
//            when the desired nickname is blocked by the nick delay
//            mechanism.

// #define ERR_RESTRICTED ":Your connection is restricted!" //484    
// //          - Sent by the server to a user upon connection to indicate
// //            the restricted nature of the connection (user mode "+r").

# define NICKNAME_VALID_CHAR "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_[]{}\\`|"

bool	validNickName(std::string nickname)
{
	if (nickname.length() > 9)
		return false;
	for (size_t i = 0; i < nickname.length(); i++)
	{
		if (!std::strchr(NICKNAME_VALID_CHAR, nickname[i]))
			return false;
	}
	return true;
}

void	Client::nick(Message *m)
{
	std::cout << GREEN << ">\tnick function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
	if (_server->isNickUsed(m->params[0]))
		send_reply(433, this, _server, "", "", "", "");
	if (m->params[0].empty())
		send_reply(431, this, _server, _nickname, "", "", "");
	if (!validNickName(m->params[0]))
		send_reply(432, this, _server, _nickname, "", "", "");
	else // "the nick is OK"
	{
		this->setNickname(m->params[0]);
		std::string msg = formatMsgsUsers(_nickname, _username, getHostname());
		msg.append("NICK " + _nickname + "\r\n");
		
		std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
		if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
	}
}
// :raul!~u@fpgxjxgh98zbk.oragono NICK patata47\r\n'
// :nick!user@client_host_name? NICK patata47\r\n'

// send(it->first, it->second.c_str(), std::strlen(it->second.c_str()), MSG_NOSIGNAL);
// void    cmd_nick( IrcServer *serv, user	*currentUser, std::string & args )
// {
// 	std::string		msg_nick;
// 	std::string		old_nick = currentUser->getNickName();
// 	if (check_args(serv, currentUser, args) == true)
// 	{
// 		msg_nick = formatMsgsUsers(currentUser->getNickName(), currentUser->getUserName(), currentUser->getHostNameUser());
// 		currentUser->setNickName(args);
// 		serv->sendToAllUsersInServ(msg_nick + "NICK " + args + "\r\n");
// 	}
// }