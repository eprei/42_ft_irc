#include "../srcs/Includes.hpp"

std::string to_string(double value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

// made by: epresa-c
void			Client::whois(Message *m){
	std::cout << FC(GREEN, ">\twhois function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	Client *ptr;

	for (size_t i = 0; i < m->params.size(); i++)
	{
		if ((ptr = _server->getClient(m->params[i])) != NULL)
		{
			sendReply(311, ptr->getNickname(), ptr->getUsername(), ptr->getHostname(), ptr->getRealname());
			if ( ptr->getNickname() == _nickname)
				sendReply(378, ptr->getUsername(), ptr->getHostname(), "", "");
			sendReply(312,  m->params[i], _server->getName(), ctime(_server->getStartTime()), "");
			// sendReply(313, m->params[i], "", "", ""); // is operator
			// sendReply(317, m->params[i], to_string(ptr->getIdle()), "", ""); // last connection
		}
		else
			sendReply(401, m->params[0], "", "", "");
	}
	sendReply(318,  m->params[0], "", "", "");
}


// 4.5.2 Whois query

//       Command: WHOIS
//    Parameters: [<server>] <nickmask>[,<nickmask>[,...]]

//    This message is used to query information about particular user.  The
//    server will answer this message with several numeric messages
//    indicating different statuses of each user which matches the nickmask
//    (if you are entitled to see them).  If no wildcard is present in the
//    <nickmask>, any information about that nick which you are allowed to
//    see is presented.  A comma (',') separated list of nicknames may be
//    given.

//    The latter version sends the query to a specific server.  It is
//    useful if you want to know how long the user in question has been
//    idle as only local server (ie. the server the user is directly
//    connected to) knows that information, while everything else is
//    globally known.

//    Numeric Replies:

//            ERR_NOSUCHSERVER                ERR_NONICKNAMEGIVEN
//            RPL_WHOISUSER                   RPL_WHOISCHANNELS
//            RPL_WHOISCHANNELS               RPL_WHOISSERVER
//            RPL_AWAY                        RPL_WHOISOPERATOR
//            RPL_WHOISIDLE                   ERR_NOSUCHNICK
//            RPL_ENDOFWHOIS

//    Examples:

//    WHOIS wiz                       ; return available user information
//                                    about nick WiZ

//    WHOIS eff.org trillian          ; ask server eff.org for user
//                                    information about trillian


//         311     RPL_WHOISUSER
//                         "<nick> <user> <host> * :<real name>"

