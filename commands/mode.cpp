#include "../srcs/Includes.hpp"

std::pair<std::string, std::string> splitString(const std::string& str)
{
    std::pair<std::string, std::string> result;
    std::string::size_type pos = str.find('_');
    if (pos == std::string::npos) {
        // El delimitador no fue encontrado
        result.first = str;
        result.second = "";
    } else {
        result.first = str.substr(0, pos);
        result.second = str.substr(pos + 1);
    }
    return result;
}

// m->params[0] == channel ou nick
// m->params[1] == mode to set
void			Client::mode(Message *m)
{
	std::cout << FC(GREEN, ">\tmode function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	if (m->params.empty())
	{
		sendReply(461, m->command, "", "", "");
		return;
	}
	if (m->params[0].at(0) == '#') //->channel
	{
		Channel		*ch = _server->getChannel((m->params[0]));
		if (ch == NULL)//no existe canal -> MODE #spadposa ?????
			return (sendReply(403, m->params[0], "", "", ""));
		std::string ch_name = ch->getName();
		if (!ch->hasClient(this))//no estoy en el canal
			// sendReply(442, ch_name, "", "", "");
			return (sendReply(441, _nickname, ch_name, "", ""));
		else if (m->params.size() == 1)//devuelvo modos del canal
			return (sendReply(324, ch_name, ch->getModes(), "", ""));
		else if (!ch->isOperator(this))//no soy operador
			return (sendReply(482, ch_name, "", "", ""));
		
		std::string set = m->params[1];
		if (set == "b")
			return ;
		if (set.empty() || (set[0] != '+' && set[0] != '-'))
		{
			std::string err;
			err = set.at(0);
			return (sendReply(472, err, ch_name, "", ""));
		}
		std::pair<std::string, std::string> ret;
		ret = splitString(ch->setModes(set));
		std::cout << FC(MAGENTA, "Set = ") << set << std::endl;
		std::cout << FC(RED, "First = ") <<ret.first << std::endl;
		std::cout << FC(RED, "Second = ") <<ret.second << std::endl;
		if (!ret.first.empty())// hay modo a agregar
		{
			std::string msg = formatMsgsUsers();
			msg.append("MODE " + ch_name + " :" + set[0] + ret.first + END_CHARACTERS);
			// :pepi!~raul@freenode-s3k.srb.vrebei.IP MODE #pitusa :-si 
			sendMsgChannel(msg, ch);
			sendMsg(msg);
		}
		if (!ret.second.empty())//error encontrado
		{
			std::string err;
			err = ret.second.at(0);
			return (sendReply(472, err, "", "", ""));
		}
		// [ server : 6667 ] :*.freenode.net 472 pepi q :is not a recognised channel mode. 
	}
	else if (m->params[0] == _nickname)
	{
		std::string msg;
		if (!m->params[1].compare("+i"))	
		{
			_hostname = "IP";
			_hostname += ".hosted-by-42lausanne.ch";
			msg = formatMsgsUsers();
			msg.append("MODE " + getNickname() + " " + m->params[1] + END_CHARACTERS);
		}
		else if(!m->params[1].compare("-i"))	
		{
			_hostname = _ip;
			_hostname += ".hosted-by-42lausanne.ch";
			msg = formatMsgsUsers();
			msg.append("MODE " + getNickname() + " " + m->params[1] + END_CHARACTERS);
		}
		sendMsg(msg);
	}
	else if (m->params.size() == 1)
		return (sendReply(502, "view", "modes", "", "")); //Can't view modes for other users 
	else if (m->params.size() == 2)
		return (sendReply(502, "change", "mode", "", "")); //Can't change mode for other users 
}
//  [ client : 9000 ] MODE #anime b 
//  [ server : 6667 ] :ChanServ!services@services.freenode.net NOTICE raul_ :[#anime] Welcome to freenode #anime IRC! Be aware conversations can be slow at times, so if you don't get a response immediately, please do stick around ☺ 
//  [ server : 6667 ] :*.freenode.net 367 raul_ #anime *!*@freenode/user/antifascist elon.hub :1676764361 
//  [ server : 6667 ] :*.freenode.net 367 raul_ #anime *!~technet@* elon.hub :1676764361 
//  [ server : 6667 ] :*.freenode.net 367 raul_ #anime *!~simon@* elon.hub :1676764361 
//  [ server : 6667 ] :*.freenode.net 367 raul_ #anime *!*@freenode-frpvje.rlp1.7tn1.4hb93e.IP elon.hub :1676764361 
//  [ server : 6667 ] :*.freenode.net 368 raul_ #anime :End of channel ban list 

// [ client : 8000 ] MODE raul +i 
// [ server : 6667 ] MODE raul +i 

//  [ client : 8000 ] MODE #usa 
//  [ server : 6667 ] :*.42irc.net 324 raul #usa :+nt 

//hay que bannear a algien me imagino para que pase a modo +b
//  [ client : 8000 ] MODE #usa +b 
//  [ server : 6667 ] :*.42irc.net 324 raul #usa :+b

//  [ client : 8000 ] MODE #usa -i 
//  [ server : 6667 ] :*.42irc.net 324 raul #usa :-i 


//  [ client : 9000 ] MODE #pitusa -sizpqwe 
//  [ server : 6667 ] :pepi!~raul@freenode-s3k.srb.vrebei.IP MODE #pitusa :-si 
//  [ server : 6667 ] :*.freenode.net 472 pepi q :is not a recognised channel mode. 
//  [ server : 6667 ] :pepi!~raul@freenode-s3k.srb.vrebei.IP MODE #pitusa :-si 

//  [ client : 9000 ] MODE #pitusa +si 
//a todo los del canal
//  [ server : 6667 ] :pepi!~raul@freenode-s3k.srb.vrebei.IP MODE #pitusa :+si 

// // MODE +i (invite_only channel)
// // MODE +t (Change the channel topic in a mode +t channel)
//  n - no messages to channel from clients on the outside;
	// }
//  c-> MODE raul 
//  s-> :*.freenode.net 502 raul_ :Can't view modes for other users 
//  c-> MODE raul -i 
//  s-> :*.freenode.net 502 glingla :Can't change mode for other users 


// ERR472   ERR_UNKNOWNMODE(char, channel) (char + " :is unknown mode char to me for " + channel)
// RPL325    
// # define RPL_UNIQOPIS(channel, nickname) (channel + " " + nickname)
// RPL346    
// # define RPL_INVITELIST(channel, invitemask) (channel + " " + invitemask)
// RPL347    
// # define RPL_ENDOFINVITELIST(channel) (channel + " :End of channel invite list")

//  [ client : 8000 ] MODE Rony +i
//  [ server : 6667 ] :Rony!raul@127.0.0.1 MODE Rony +i

// 3.2.3 Channel mode message

//       Command: MODE
//    Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

//    The MODE command is provided so that users may query and change the
//    characteristics of a channel.  For more details on available modes
//    and their uses, see "Internet Relay Chat: Channel Management" [IRC-
//    CHAN].  Note that there is a maximum limit of three (3) changes per
//    command for modes that take a parameter.

//    Numeric Replies:

// ERR 461
// #define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")
//    477    ERR_NOCHANMODES              "<channel> :Channel doesn't support modes" no se usa mepa

//ERR 482
// # define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator")

// ERR 441    
// # define ERR_USERNOTINCHANNEL(nick, channel) (nick + " " + channel + " :They aren't on that channel")

// 324
// # define RPL_CHANNELMODEIS(channel, mode) (channel + " :" + mode)
// :*server_name 324 nick #CHANNEL :+nt
// :DESKTOP-MQD5OHQ 324 Rony #people [+n]  ccomis
 

// // ERR467    
// # define ERR_KEYSET(channel) (channel + " :Channel key already set")

// // ERR472    
// # define ERR_UNKNOWNMODE(char, channel) (char + " :is unknown mode char to me for " + channel)

// // RPL325    
// # define RPL_UNIQOPIS(channel, nickname) (channel + " " + nickname)

// // RPL346    
// # define RPL_INVITELIST(channel, invitemask) (channel + " " + invitemask)

// // RPL347    
// # define RPL_ENDOFINVITELIST(channel) (channel + " :End of channel invite list")

//    The following examples are given to help understanding the syntax of
//    the MODE command, but refer to modes defined in "Internet Relay Chat:
//    Channel Management" [IRC-CHAN].
