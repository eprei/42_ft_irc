#include <iostream>
#include <string>
#include <vector>
#include "Includes.hpp"

using namespace std;

void	process_buffer(const std::string& buf)
{
    // Separar la cadena en tokens utilizando el delimitador "\r\n"
	Message	m;
    char	*token = strtok(const_cast<char*>(buf.c_str()), END_CHARACTERS);
    while (token != NULL) {
        // Convertir el token en una cadena de C++
        std::string command(token);
        std::cout << "Comando recibido: " << command << std::endl;
        // Procesar el comando aquí...
		m = parseMessage(token);
		// std::cout << FC(YELLOW, "Ascii Message :") << std::endl;
		// printAscii(_buf);
		std::cout << FC(GREEN, "Message parsed =") << std::endl;
		print_message(m);
		// execCmd(m);
        // Obtener el siguiente token
        token = strtok(NULL, END_CHARACTERS);
    }
}

//el comando llega sin \r\n
Message parseMessage(string input) {
    Message msg;

    // Parsing prefix
    if (input[0] == ':') {
        size_t prefixEnd = input.find(' ');
        if (prefixEnd != string::npos) {
            msg.prefix = input.substr(1, prefixEnd-1);
            input = input.substr(prefixEnd+1);
        } else {
            // Invalid message
            return msg;
        }
    }

    // Parsing command
    size_t commandEnd = input.find(' ');
    if (commandEnd != string::npos) {
        msg.command = input.substr(0, commandEnd);
        input = input.substr(commandEnd+1);
    } else {
        // Invalid message
        return msg;
    }

    // Parsing parameters
    while (input[0] == ' ') {
        input = input.substr(1);
    }
    while (input.length() > 0) {
        if (input[0] == ':') {
            msg.params.push_back(input.substr(1));
            break;
        } else {
            size_t paramEnd = input.find(' ');
            if (paramEnd != string::npos) {
                msg.params.push_back(input.substr(0, paramEnd));
                input = input.substr(paramEnd+1);
            } else {
                msg.params.push_back(input);
                break;
            }
        }
    }
    return msg;
}


//PRINT
void	print_message(const Message& msg)
{
    if (!msg.prefix.empty()) {
        std::cout << ":" << msg.prefix << " ";
    }
    std::cout << "msg.command =";
    std::cout << msg.command;
    std::cout << std::endl;

    std::cout << "msg.params =";
	for (std::vector<std::string>::const_iterator it = msg.params.begin(); it != msg.params.end(); ++it)
	{
        std::cout << " " << *it;
    }
    std::cout << std::endl << std::endl;
}

void printAscii(const std::string& str)
{
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
        std::cout << *it << " " << int(*it) << std::endl;
}
