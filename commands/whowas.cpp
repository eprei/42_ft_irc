#include "../srcs/Includes.hpp"

// made by: epresa-c

// TO CONSIDER TO DO: difference between ask four your own name and the others name.
//			When you ask for yourself you have the real hostname, otherway you have the masked hostname

void			Client::whowas(Message *m){
	std::cout << GREEN << ">\twhowas function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
	int found = false;

	for (size_t i = _nicksHistory.size() - 1; i > 0 ; i--)
	{
		if (_nicksHistory[i].nick == m->params[0])
		{
			send_reply(314, this, _server, _nicksHistory[i].nick, _nicksHistory[i].user, _nicksHistory[i].host, _nicksHistory[i].realname);
			send_reply(312, this, _server, _nicksHistory[i].nick, _nicksHistory[i].server, _nicksHistory[i].serverInfo, "");
 			found = true;
			std::cout << "found = " << std::boolalpha << found << std::endl;
		}
	}
	if (found == false)
		send_reply(406, this, _server, m->params[0], "", "", "");
	send_reply(369, this, _server, m->params[0], "", "", "");
}

// 4.5.3 Whowas

//       Command: WHOWAS
//    Parameters: <nickname> [<count> [<server>]]

//    Whowas asks for information about a nickname which no longer exists.
//    This may either be due to a nickname change or the user leaving IRC.
//    In response to this query, the server searches through its nickname
//    history, looking for any nicks which are lexically the same (no wild
//    card matching here).  The history is searched backward, returning the
//    most recent entry first.  If there are multiple entries, up to
//    <count> replies will be returned (or all of them if no <count>
//    parameter is given).  If a non-positive number is passed as being
//    <count>, then a full search is done.

//    Numeric Replies:

//            ERR_NONICKNAMEGIVEN             ERR_WASNOSUCHNICK
//            RPL_WHOWASUSER                  RPL_WHOISSERVER
//            RPL_ENDOFWHOWAS

//    Examples:

//    WHOWAS Wiz                      ; return all information in the nick
//                                    history about nick "WiZ";

//    WHOWAS Mermaid 9                ; return at most, the 9 most recent
//                                    entries in the nick history for
//                                    "Mermaid";

//    WHOWAS Trillian 1 *.edu         ; return the most recent history for
//                                    "Trillian" from the first server found
//                                    to match "*.edu".
