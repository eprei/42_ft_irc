#include "Includes.hpp"

std::string	Client::formatMsgsUsers()
{
	std::string		msg;

	msg.append(":");
	msg.append(_nickname);
	msg.append("!");
	// msg.append("~");
	msg.append(_username);
	msg.append("@");
	msg.append(getHostname());
	msg.append(" ");
	return (msg);
}

std::string	Client::formatMsgsReply(const int code)
{
	std::string	r;

	r.append(":");
	r.append(_server->getName());
	r.append(" ");		
	if (code < 10)
		r.append("00");
	else if (code < 100)
		r.append("0");
	r.append(to_string(code));	//:hostname 025
	r.append(" ");		
	if (getNickname() == "")
		r.append("*"); 			//:hostname 025 *
	else
		r.append(_nickname);	//:hostname 025 nick
	r.append(" ");
	return (r);
}

std::string	Client::numericReply(const int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
	switch(code)
	{
		case 1:
			return (RPL_WELCOME(arg1, arg2, arg3));
		case 2:
			return (RPL_YOURHOST(arg1, arg2));
		case 3:
			return (RPL_CREATED(arg1));
		case 4:
			return (RPL_MYINFO(arg1, arg2, arg3, arg4));
		// whois
		case 311:
			return (RPL_WHOISUSER(arg1, arg2, arg3, arg4));
		case 312:
			return (RPL_WHOISSERVER(arg1, arg2, arg3));
		case 313:
			return (RPL_WHOISOPERATOR(arg1, _server->isOper(this)));
		case 314:
			return (RPL_WHOWASUSER(arg1, arg2, arg3, arg4));
		case 317:
			return (RPL_WHOISIDLE(arg1, arg2)); // TO DO: CALL IDLE FUNCTION AS THE SECOND ARGUMENT
		case 318:
			return (RPL_ENDOFWHOIS(arg1));
		case 401:
			return (ERR_NOSUCHNICK(arg1));
		case 406:
			return (ERR_WASNOSUCHNICK(arg1));
		// nick
		case 353:
			return (RPL_NAMREPLY(arg1, arg2));
		case 366:
			return (RPL_ENDOFNAMES(arg1));
		//whowas
		case 369:
			return (RPL_ENDOFWHOWAS(arg1));
		case 378:
			return (RPL_BANEXPIRED(arg1, arg2, getIp()));
		// part
		case 403:
			return (ERR_NOSUCHCHANNEL(arg1));
		case 442:
			return (ERR_NOTONCHANNEL(arg1));
		case 431:
			return (ERR_NONICKNAMEGIVEN);
		case 432:
			return (ERR_ERRONEUSNICKNAME(arg1));
		case 433:
			return (ERR_NICKNAMEINUSE(arg1));
		case 461:
			return (ERR_NEEDMOREPARAMS(arg1));
		case 462:
			return (ERR_ALREADYREGISTERED);
		case 464:
			return (ERR_PASSWDMISMATCH);
		case 324:
			return (RPL_CHANNELMODEIS(arg1, arg2));
	}
	return ("");
}

void	Client::sendReply(const int code, std::string arg1, std::string arg2,\
										 std::string arg3, std::string arg4)
{
	std::string reply;

	reply = formatMsgsReply(code);
	reply += numericReply(code, arg1, arg2, arg3, arg4);
	reply += END_CHARACTERS;

	sendMsg(reply);
}

void	Client::sendMsg(std::string msg)
{
	std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
	if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
}
