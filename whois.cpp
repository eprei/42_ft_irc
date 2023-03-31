#include "Client.hpp"
#include "Server.hpp"

// TO DO: Write the write function

void			Client::whois(Message *m){

	std::cout << GREEN << ">\twhois function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
	(void) m;
	// if (m->params[0].size() == 0)
	// {
	// 	_server->removeClient(this);
	// 	//TO DO: sendToChannel( client_nickname "has quit the channel");
	// }
	// else
	// {
	// 	_server->removeClient(this);
		//TO DO: sendToChannel( client_nickname + m->params[0] + m->params[1] ... etc );
		//TO DO: sendToChannel( client_nickname "has quit the channel");
	// }
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
