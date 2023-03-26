# include "Server.hpp"

// map (string, string)
// #define MSG_001 ":Welcome to the Internet Relay Network" + client->getNickname() + "!" + client->getUsername() + "@" + _name

// RPL 001
// # define RPL_WELCOME(nick, user, host) (":Welcome to the Internet Relay Network " \
            //    + nick + "!" + user + "@" + host + "\r\n")

// RPL 002
# define RPL_YOURHOST(servername, ver) (":Your host is " + servername + ", running version " + ver + "\r\n")

// RPL 003
# define RPL_CREATED() (":This server was created 25/03/2023\r\n")

// RPL 004
# define RPL_MYINFO(servername, version, userModes, channelModes) (":" + servername + \
                    " " + version + " " + userModes + " " + channelModes + "\r\n")

// inline void Server::numeric_reply(Client *c, std::string code, std::string arg1, std::string arg2, std::string arg3) 
void	Server::numeric_reply(Client *c, std::string ) //RPL_WELCOME
{
	std::cout << FC(YELLOW, "Server Reply to be sent:\n") << code << std::endl;
	if (send(c->getSocket(), code.c_str(), code.length(), 0) < 0)
		perror("SEND FAILED");
}

// std::string		send_replies(const int code, user *user, IrcServer *serv, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
// {
// 	std::string		reply = ":";

// 	reply.append(serv->_tcpServer.getHostname());
// 	reply.append(" ");
// 	if (code < 10)
// 		reply.append("00");
// 	else if (code < 100)
// 		reply.append("0");
// 	reply.append(ft_to_string(code));
// 	reply.append(" ");
// 	if (user->getNickName() == "")
// 		reply.append("*");
// 	else
// 		reply.append(user->getNickName());
// 	reply.append(" ");
// 	switch(code)
// 	{
// 		case 1:
// 			return reply + RPL_WELCOME(arg1, arg2, arg3);