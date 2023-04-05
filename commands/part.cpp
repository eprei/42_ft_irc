#include "../srcs/Includes.hpp"

// made by: mpons

// 442
// # define ERR_NOTONCHANNEL(channel) channel + " :You're not on that channel"

// 403
// # define ERR_NOSUCHCHANNEL(channel_name) (channel_name + " :No such channel")

// m->params[0] = channel or list of channels
// m->params[1] = part message

void			Client::part(Message *m){
	std::cout << GREEN << ">\tpart function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
	if (m->params.empty())
	{
		send_reply(461, this, _server, m->command, "", "", "");
		return;
	}

	Channel *target = _server->getChannel((m->params[0]));
	if (target == NULL)
		send_reply(403, this, _server, target->getName(), "", "", "");
	else if (!target->hasClient(this))
		send_reply(442, this, _server, target->getName(), "", "", "");
	else {
	// 	// for (size_t i(0); i < m->params.size(); i++)
		_server->removeClientFromChannel(this, target->getName());

		std::string msg = formatMsgsUsers(_nickname, _username, getHostname());
		std::string part_msg = "";

	// 	if (!m->params[1].empty())//no PART_MSG not_defined
		if (m->params.size() == 1)//no PART_MSG not_defined
			part_msg = "\"hasta la vista Baby\"";
		else
			part_msg = "\"" + m->params[1] + "\"";
			// PART :#PATATA\r\n'
			// PART #PATATA :"me voy"\r\n'
			// PART #USA :"hasta la vista Baby"\r\n'

		msg.append("PART " + m->params[0] + " :" + part_msg + END_CHARACTERS);
		// std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
		if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
// [ client : 8000 ] b'PART #PATATA\r\n'
//  [ server : 6667 ] b':raul_!~raul@freenode-b8j.srb.vrebei.IP PART :#PATATA\r\n'
// [ client : 8000 ] b'PART #PATATA :me voy\r\n'
//  [ server : 6667 ] b':raul_!~raul@freenode-b8j.srb.vrebei.IP PART #PATATA :"me voy"\r\n'
	}
}

// 3.2.2 Part message

//       Command: PART
//    Parameters: <channel> *( "," <channel> ) [ <Part Message> ]

//    The PART command causes the user sending the message to be removed
//    from the list of active members for all given channels listed in the
//    parameter string.  If a "Part Message" is given, this will be sent
//    instead of the default message, the nickname.  This request is always
//    granted by the server.

//    Servers MUST be able to parse arguments in the form of a list of
//    target, but SHOULD NOT use lists when sending PART messages to
//    clients.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//            ERR_NOTONCHANNEL

//    Examples:

//    PART #twilight_zone             ; Command to leave channel
//                                    "#twilight_zone"

//    PART #oz-ops,&group5            ; Command to leave both channels
//                                    "&group5" and "#oz-ops".

//    :WiZ!jto@tolsun.oulu.fi PART #playzone :I lost
//                                    ; User WiZ leaving channel
//                                    "#playzone" with the message "I
//                                    lost".

