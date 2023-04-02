#include "Server.hpp"
#include "Client.hpp"
#include "Includes.hpp"
// map (string, string)
// #define MSG_001 ":Welcome to the Internet Relay Network" + client->getNickname() + "!" + client->getUsername() + "@" + _name

// RPL 001
# define RPL_WELCOME(nick, user, host) (":Welcome to the Internet Relay Network PAPA!" \
			+ nick + "!" + user + "@" + host + "\r\n")

// RPL 002
# define RPL_YOURHOST(servername, ver) (":Your host is " + servername + ", running version " + ver + "\r\n")

// RPL 003
# define RPL_CREATED() (":This server was created 25/03/2023\r\n")

// RPL 004
# define RPL_MYINFO(servername, version, userModes, channelModes) (":" + servername + \
				" " + version + " " + userModes + " " + channelModes + "\r\n")
// RPL 311
# define RPL_WHOISUSER(nickname, user, servername, real_name) (nickname + \
				" " + user + " " + servername + " * :" + real_name + "\r\n")
// RPL 312
# define RPL_WHOISSERVER(nick, server) (nick + \
				" " + server + " :42Lausanne IRC Server" + "\r\n")
// RPL 313
# define RPL_WHOISOPERATOR(nick, privileges) (nick + \
				" :" + privileges + "\r\n")
// RPL 317
# define RPL_WHOISIDLE(nick, seconds) (nick + \
				" " + seconds + " :seconds idle" + "\r\n")
// RPL 318
# define RPL_ENDOFWHOIS(nick) (nick + \
				" :End of /WHOIS list.\r\n")
// RPL 401
# define ERR_NOSUCHNICK(nick) (": 401" + nick + \
				" is not registered on this server" + "\r\n")
// RPL 461
#define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")
// RPL 462
#define ERR_ALREADYREGISTERED "462 :Unauthorized command (already registered)"
// RPL 464
#define ERR_PASSWDMISMATCH	"464 * :Password incorrect"

// RPL 431
#define ERR_NONICKNAMEGIVEN ":No nickname given" //431
// - Returned when a nickname parameter expected for a command and isn't found.

// RPL 432
// #define ERR_ERRONEUSNICKNAME "<nick> :Erroneous nickname" //432
#define ERR_ERRONEUSNICKNAME(nick) nick + " :Erroneous nickname" //432
//          - Returned after receiving a NICK message which contains
//            characters which do not fall in the defined set.  See
//            section 2.3.1 for details on valid nicknames.

// RPL 433
# define ERR_NICKNAMEINUSE(nick) nick + " :Nickname is already in use" //433
//          - Returned when a NICK message is processed that results
//            in an attempt to change to a currently existing
//            nickname..

std::string	ft_to_string(int value)
{
	std::string output;
	std::string sign;
	char		nb[2];

	if (value < 0)
	{
		sign + "-";
		value = -value;
	}
	nb[1] = '\0';
	while (output.empty() || (value > 0))
	{
		nb[0] = value % 10 + '0';
		output.insert(0, std::string(nb));
		value /= 10;
	}
	return (sign + output);
}

std::string	numeric_reply(const int code, Client *client, Server *serv, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
	std::string		reply = ":";

	reply.append(serv->getName());
	reply.append(" ");
	if (code < 10)
		reply.append("00");
	else if (code < 100)
		reply.append("0");
	reply.append(ft_to_string(code));
	reply.append(" ");
	if (client->getNickname() == "")
		reply.append("*");
	else
		reply.append(client->getNickname());
	reply.append(" ");
	switch(code)
	{
		case 1:
			return (reply + RPL_WELCOME(arg1, arg2, arg3));
		case 2:
			return (reply + RPL_YOURHOST(arg1, arg2));
		case 3:
			return (reply + RPL_CREATED());
		case 4:
			return (reply + RPL_MYINFO(arg1, arg2, arg3, arg4));
		// whois
		case 311:
			return (reply + RPL_WHOISUSER(arg1, arg2, serv->getName(), arg4));
		case 312:
			return (reply + RPL_WHOISSERVER(client->getNickname(), serv->getName()));
		case 313:
			return (reply + RPL_WHOISOPERATOR(client->getNickname(), serv->isOper(client)));
		case 317:
			return (reply + RPL_WHOISIDLE(client->getNickname(), "123")); // TO DO: CALL IDLE FUNCTION AS THE SECOND ARGUMENT
		case 318:
			return (reply + RPL_ENDOFWHOIS(client->getNickname()));
		case 401:
			return (reply + ERR_NOSUCHNICK(client->getNickname()));
		// nick
		case 431:
			return (reply + ERR_NONICKNAMEGIVEN);
		case 432:
			return (reply + ERR_ERRONEUSNICKNAME(arg1));
		case 433:
			return (reply + ERR_NICKNAMEINUSE(arg1));

		case 461:
			return reply + ERR_NEEDMOREPARAMS(arg1);
		case 462:
			return reply + ERR_ALREADYREGISTERED;
		case 464:
			return reply + ERR_PASSWDMISMATCH;
	}
	return (reply);
}

// inline void Server::numeric_reply(Client *c, std::string code, std::string arg1, std::string arg2, std::string arg3)
// void	Server::numeric_reply(Client *c, std::string ) //RPL_WELCOME
void	send_reply(const int code, Client *client, Server *serv, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
	std::string reply = numeric_reply(code, client, serv, arg1, arg2, arg3, arg4);
	std::cout << FC(YELLOW, "Server Reply to be sent:\n") << reply << std::endl;
	if (send(client->getSocket(), reply.c_str(), reply.length(), 0) < 0)
		perror("SEND FAILED");
}

std::string	formatMsgsUsers(const std::string & nickname, const std::string & username, const std::string & hostname)
{
	std::string		msg;

	msg.append(":");
	msg.append(nickname);
	msg.append("!");
	msg.append(username);
	msg.append("@");
	msg.append(hostname);
	msg.append(" ");
	return (msg);
}

