#include "../srcs/Includes.hpp"

// 324
// RPL_CHANNELMODEIS(channel, mode, mode_params) "<channel> <mode> <mode params>"
// :*server_name 324 nick #CHANNEL :+nt
// :DESKTOP-MQD5OHQ 324 Rony #people [+n]  ccomis

	// std::map<char, bool> &getModes();
	// bool hasMode(char mode);

		// std::string						_mode;

void			Client::mode(Message *m)
{
	std::cout << GREEN << ">\tmode function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
	if (m->params.empty())
	{
		send_reply(461, this, _server, m->command, "", "", "");
		return;
	}
	Channel *target= _server->getChannel(m->params[0]);
	if (target) //channel param
	{
		// for (size_t i(0); i < m->params.size(); i++)
		// {
			Channel *target = _server->getChannel(m->params[0]);
			send_reply(324, this, _server, m->params[0], target->getModes(), "", "");
			// send_reply(366, this, _server, m->params[0], "", "", "");
		// }
	}
 	else //no hay respuesta
	{
		std::string msg;
		msg.append("MODE " + getNickname() + " +i" + END_CHARACTERS);
		std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
		if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
	}
//  [ client : 8000 ] MODE Rony +i 
//  [ server : 6667 ] :Rony!raul@127.0.0.1 MODE Rony +i 
}


// 329 RPL_CREATIONTIME  (pas obliger de le faire)
// :*server_name 329 nick #CHANNEL :89238923892?

//        367    RPL_BANLIST
//               "<channel> <banmask>"
//        368    RPL_ENDOFBANLIST
//               "<channel> :End of channel ban list"

//          - When listing the active 'bans' for a given channel,
//            a server is required to send the list back using the
//            RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate
//            RPL_BANLIST is sent for each active banmask.  After the
//            banmasks have been listed (or if none present) a
//            RPL_ENDOFBANLIST MUST be sent.

//    MODE &oulu +b                   ; Command to list ban masks set for
                                //    the channel "&oulu".





// 3.2.3 Channel mode message

//       Command: MODE
//    Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

//    The MODE command is provided so that users may query and change the
//    characteristics of a channel.  For more details on available modes
//    and their uses, see "Internet Relay Chat: Channel Management" [IRC-
//    CHAN].  Note that there is a maximum limit of three (3) changes per
//    command for modes that take a parameter.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_KEYSET
//            ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
//            ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
//            RPL_CHANNELMODEIS
//            RPL_BANLIST                     RPL_ENDOFBANLIST
//            RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
//            RPL_INVITELIST                  RPL_ENDOFINVITELIST
//            RPL_UNIQOPIS

//    The following examples are given to help understanding the syntax of
//    the MODE command, but refer to modes defined in "Internet Relay Chat:
//    Channel Management" [IRC-CHAN].

//    Examples:

//    MODE #Finnish +imI *!*@*.fi     ; Command to make #Finnish channel
//                                    moderated and 'invite-only' with user
//                                    with a hostname matching *.fi
//                                    automatically invited.

//    MODE #Finnish +o Kilroy         ; Command to give 'chanop' privileges
//                                    to Kilroy on channel #Finnish.

//    MODE #Finnish +v Wiz            ; Command to allow WiZ to speak on
//                                    #Finnish.

//    MODE #Fins -s                   ; Command to remove 'secret' flag
//                                    from channel #Fins.

//    MODE #42 +k oulu                ; Command to set the channel key to
//                                    "oulu".

//    MODE #42 -k oulu                ; Command to remove the "oulu"
//                                    channel key on channel "#42".




// Kalt                         Informational                     [Page 18]


// RFC 2812          Internet Relay Chat: Client Protocol        April 2000


//    MODE #eu-opers +l 10            ; Command to set the limit for the
//                                    number of users on channel
//                                    "#eu-opers" to 10.

//    :WiZ!jto@tolsun.oulu.fi MODE #eu-opers -l
//                                    ; User "WiZ" removing the limit for
//                                    the number of users on channel "#eu-
//                                    opers".

//    MODE &oulu +b                   ; Command to list ban masks set for
//                                    the channel "&oulu".

//    MODE &oulu +b *!*@*             ; Command to prevent all users from
//                                    joining.

//    MODE &oulu +b *!*@*.edu +e *!*@*.bu.edu
//                                    ; Command to prevent any user from a
//                                    hostname matching *.edu from joining,
//                                    except if matching *.bu.edu

//    MODE #bu +be *!*@*.edu *!*@*.bu.edu
//                                    ; Comment to prevent any user from a
//                                    hostname matching *.edu from joining,
//                                    except if matching *.bu.edu

//    MODE #meditation e              ; Command to list exception masks set
//                                    for the channel "#meditation".

//    MODE #meditation I              ; Command to list invitations masks
//                                    set for the channel "#meditation".

//    MODE !12345ircd O               ; Command to ask who the channel
//                                    creator for "!12345ircd" is

