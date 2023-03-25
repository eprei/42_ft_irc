// RPL 001
# define RPL_WELCOME(nick, user, host) (":Welcome to the Internet Relay Network " \
               + nick + "!" + user + "@" + host + "\r\n")

// RPL 002
# define RPL_YOURHOST(servername, ver) (":Your host is " + servername + ", running version " + ver + "\r\n")

// RPL 003
# define RPL_CREATED() (":This server was created 01/06/2022\r\n")

// RPL 004
# define RPL_MYINFO(servername, version, userModes, channelModes) (":" + servername + \
                    " " + version + " " + userModes + " " + channelModes + "\r\n")

// inline void Server::numeric_reply(Client *c, std::string code, std::string arg1, std::string arg2, std::string arg3) 
// {
// 	std::string txt;
// 	char	*ptr;
// 	txt.append(":");
// 	txt.append(hostname);
// 	txt.append(" ");
// 	txt.append(code);
// 	txt.append(" ");
// 	txt.append(u->getNickName()); 
// 	txt.append(" ");
// 	txt.append(choose_msg(std::strtol(code.c_str(), &ptr, 10), u, arg1, arg2, arg3));
// 	txt.append("\r\n");

// 	out(FG2("Server Reply to be sent:") << code);
// 	out(txt.c_str());
// 	if (send(u->socket_descriptor, txt.c_str(), txt.length(), 0) < 0)
// 	{
// 		perror("SEND FAILED");
// 	}
// }