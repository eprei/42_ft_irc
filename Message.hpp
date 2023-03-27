#ifdef MESSAGE_HPP
# define MESSAGE_HPP

//C'est une idee ( a voir si c'est util ou pas)

// Message: Esta clase representaría un mensaje enviado por un cliente.
// Sería responsable de analizar el mensaje para determinar el comando y los argumentos,
// y ejecutar la acción correspondiente (por ejemplo, unirse a un canal o enviar un mensaje).
// (PARSER)

# include <string>
# include <ctime>

// class Message {
// private:
// 	std::string _sender;
// 	std::string _content;
// 	std::time_t timestamp;
// public:
// 	Message(std::string content, std::string author) {
//     	this->content = content;
//     	this->author = author;
//     	this->timestamp = std::time(NULL);
//   }
// 	Message(std::string sender, std::string content) :
//         _sender(sender), _content(content) {}

// 	std::string getSender() const { return _sender; }
// 	std::string getContent() const { return _content; }
// 	std::time_t getTimestamp() const { return timestamp; }
// 	parseMsg();
// };

std::string	numeric_reply(const int code, Client *client, Server *serv, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
void	send_reply(const int code, Client *client, Server *serv, std::string arg1, std::string arg2, std::string arg3, std::string arg4)

#endif