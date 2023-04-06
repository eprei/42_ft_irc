#include "Includes.hpp"
// #define MSG_001 ":Welcome to the Internet Relay Network" + client->getNickname() + "!" + client->getUsername() + "@" + _name

// RPL 001
# define RPL_WELCOME(nick, user, host) (":Welcome to the Internet Relay Network " \
			+ nick + "!" + user + "@" + host + END_CHARACTERS)

// RPL 002
# define RPL_YOURHOST(servername, ver) (":Your host is " + servername + ", running version " + ver)

// RPL 003
# define RPL_CREATED(_startTime) (":This server was created " + _startTime + END_CHARACTERS)

// RPL 004
# define RPL_MYINFO(servername, version, userModes, channelModes) (":" + servername + \
				" " + version + " " + userModes + " " + channelModes + END_CHARACTERS)
// RPL 311
# define RPL_WHOISUSER(nickwhoask, nickaskedfor, servername, real_name) (nickwhoask + \
				" ~" + nickaskedfor + " " + servername + " * :" + real_name + END_CHARACTERS)
// RPL 312
# define RPL_WHOISSERVER(nick, server, serverinfo) (nick + \
				" " + server + " :" + serverinfo + END_CHARACTERS)
// RPL 313
# define RPL_WHOISOPERATOR(nick, privileges) (nick + \
				" :" + privileges + END_CHARACTERS)
// RPL 314
# define RPL_WHOWASUSER(nick, user, host, realname) (nick + \
				" " + user + " " + host + " * :" + realname + END_CHARACTERS)
// RPL 317
# define RPL_WHOISIDLE(nick, seconds) (nick + \
				" " + seconds + " :seconds idle" + END_CHARACTERS)
// RPL 318
# define RPL_ENDOFWHOIS(nick) (nick + \
				" :End of /WHOIS list.\r\n")
// RPL 369
# define RPL_ENDOFWHOWAS(nick) (nick + \
				" :End of WHOWAS\r\n")
// RPL 378
# define RPL_BANEXPIRED(nick, hostname, ip) (nick + \
				" :is connecting from ~"  + nick + "@"+ hostname + " " \
				+ ip + END_CHARACTERS)
// RPL 401
# define ERR_NOSUCHNICK(nick) (nick + " :No such nick\r\n")
// RPL 406
# define ERR_WASNOSUCHNICK(nick) (nick + " :There was no such nickname\r\n")
// PASS COMMAND
// RPL 461
#define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")
// ERR 462
#define ERR_ALREADYREGISTERED "462 :Unauthorized command (already registered)"
// ERR 464
// #define ERR_PASSWDMISMATCH	"464 * :Password incorrect"
#define ERR_PASSWDMISMATCH	"* :Password incorrect"

// NICK COMMAND
// ERR 431
#define ERR_NONICKNAMEGIVEN ":No nickname given" //431
// - Returned when a nickname parameter expected for a command and isn't found.

// ERR 432
// #define ERR_ERRONEUSNICKNAME "<nick> :Erroneous nickname" //432
#define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname") //432
//          - Returned after receiving a NICK message which contains
//            characters which do not fall in the defined set.  See
//            section 2.3.1 for details on valid nicknames.

// ERR 433
# define ERR_NICKNAMEINUSE(arg1) (arg1 + " :Nickname is already in use") //433
//          - Returned when a NICK message is processed that results
//            in an attempt to change to a currently existing
//            nickname..
//  [ server : 6667 ] :*.freenode.net 433 * epresa-c :Nickname is already in use.
//join
//353
# define RPL_NAMREPLY(channel, nick) "= " + channel + " :@" + nick
// = #lol :@Guest36096 mikeWpit\r\n
//"( "=" / "*" / "@" ) <channel>
//:[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )

//- "@" is used for secret channels, "*" for private channels,
//  and "=" for others (public channels).

//366
# define RPL_ENDOFNAMES(channel) channel + " :End of NAMES list"

//part
// 403
# define ERR_NOSUCHCHANNEL(channel_name) (channel_name + " :No such channel")

// 442
# define ERR_NOTONCHANNEL(channel) channel + " :You're not on that channel"

// 324
# define RPL_CHANNELMODEIS(channel, mode) (channel + " :" + mode)

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

	reply.append(serv->getName());//:hostname
	reply.append(" ");
	if (code < 10)
		reply.append("00");
	else if (code < 100)
		reply.append("0");
	reply.append(ft_to_string(code));
	reply.append(" ");//:hostname 025
	if (client->getNickname() == "")
		reply.append("*"); //:hostname 025 *
	else
		reply.append(client->getNickname());//:hostname 025 nick
	reply.append(" ");
	switch(code)
	{
		case 1:
			return (reply + RPL_WELCOME(arg1, arg2, arg3));
		//:testnet.ergo.chat 001 mike :Welcome to the ErgoTestnet IRC Network mike
		case 2:
			return (reply + RPL_YOURHOST(arg1, arg2));
		case 3:
			return (reply + RPL_CREATED(arg1));
		case 4:
			return (reply + RPL_MYINFO(arg1, arg2, arg3, arg4));
		// whois
		case 311:
			return (reply + RPL_WHOISUSER(arg1, arg2, arg3, arg4));
		case 312:
			return (reply + RPL_WHOISSERVER(arg1, arg2, arg3));
		case 313:
			return (reply + RPL_WHOISOPERATOR(arg1, serv->isOper(client)));
		case 314:
			return (reply + RPL_WHOWASUSER(arg1, arg2, arg3, arg4));
		case 317:
			return (reply + RPL_WHOISIDLE(arg1, arg2)); // TO DO: CALL IDLE FUNCTION AS THE SECOND ARGUMENT
		case 318:
			return (reply + RPL_ENDOFWHOIS(arg1));
		case 401:
			return (reply + ERR_NOSUCHNICK(arg1));
		case 406:
			return (reply + ERR_WASNOSUCHNICK(arg1));
		// nick
		case 353:
			return (reply + RPL_NAMREPLY(arg1, arg2));
		case 366:
			return (reply + RPL_ENDOFNAMES(arg1));
		//whowas
		case 369:
			return (reply + RPL_ENDOFWHOWAS(arg1));
		case 378:
			return (reply + RPL_BANEXPIRED(arg1, arg2, client->getIp()));
		// part
		case 403:
			return (reply + ERR_NOSUCHCHANNEL(arg1));
		case 442:
			return (reply + ERR_NOTONCHANNEL(arg1));
		case 431:
			return (reply + ERR_NONICKNAMEGIVEN);
		case 432:
			return (reply + ERR_ERRONEUSNICKNAME(arg1));
		case 433:
			return (reply + ERR_NICKNAMEINUSE(arg1));
		case 461:
			return (reply + ERR_NEEDMOREPARAMS(arg1));
		case 462:
			return (reply + ERR_ALREADYREGISTERED);
		case 464:
			return (reply + ERR_PASSWDMISMATCH);
		case 324:
			return (reply + RPL_CHANNELMODEIS(arg1, arg2));
	}
	return (reply);
}

// void	Server::numeric_reply(Client *c, std::string ) //RPL_WELCOME
//:testnet.ergo.chat 001 mike + MACROS(arg1, arg2, arg3)
void	send_reply(const int code, Client *client, Server *serv, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
	std::string reply = numeric_reply(code, client, serv, arg1, arg2, arg3, arg4) + END_CHARACTERS;
	// std::cout << FC(YELLOW, "Server Reply to be sent:\n") << reply << std::endl;
	if (send(client->getSocket(), reply.c_str(), reply.length(), 0) < 0)
		perror("SEND FAILED");
}

std::string	formatMsgsUsers(const std::string & nickname, const std::string & username, const std::string & hostname)
{
	std::string		msg;

	msg.append(":");
	msg.append(nickname);
	msg.append("!");
	// msg.append("~");
	msg.append(username);
	msg.append("@");
	msg.append(hostname);
	msg.append(" ");
	return (msg);
}

