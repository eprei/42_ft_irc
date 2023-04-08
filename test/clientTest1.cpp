#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include "../srcs/Includes.hpp"

#define TEST_MESSAGE "Hello, i'm client 1"
#define TEST_MESSAGE_LENGTH 23
#define PORT 6667

int main(int argc, char *argv[])
{
	(void)argv;
	(void)argc;
	int sockfd, numbytes;
	struct sockaddr_in servaddr;
	// char buff[TEST_MESSAGE_LENGTH] = TEST_MESSAGE;
	std::string acceptableCommands[NUMBER_OF_CMD] = {
		"PASS asd\r\n"				,\
		"NICK pepito\r\n"			,\
		"USER John\r\n"				,\
		"JOIN #LOL\r\n" 			,\
		"JOIN &foo fubar\r\n"		,\
		// Command to join channel &foo using key "fubar".
		"JOIN #foo,&bar fubar\r\n"		,\
		//  ; Command to join channel #foo using key "fubar" and &bar using no key.
		"JOIN #foo,#bar fubar,foobar\r\n"	,\
		// ; Command to join channel #foo using key "fubar", and channel #bar using key "foobar".
		"JOIN #foo,#bar\r\n",\
		"JOIN 0\r\n"		,\
		"PING\r\n"			,\
		"KICK\r\n"			,\
		"CAP LS\r\n"		,\
		"NOTICE\r\n"		,\
		"QUIT\r\n" 			\
		};
		/*
		; Command to join channels #foo and #bar.
		  ; Leave all currently joined channels.
		"LIST\r\n" 			,\
		"MODE\r\n"			,\
		"PART\r\n" 			,\
		"WHOIS raul\r\n"	,\
		"PRIVMSG\r\n"		,\
		*/
	int i = 0;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	// bzero(&servaddr, sizeof(servaddr));     /* zero struct */
	servaddr.sin_family = AF_INET;      /* host byte order */
	servaddr.sin_port = htons(PORT);    /* short, network byte order */
	// servaddr.sin_addr = *((struct in_addr *)he->h_addr);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(&(servaddr.sin_zero), 8);     /* zero pour le reste de struct */

	if (connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
		perror("connect");
		exit(1);
	}

	// if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
	//     perror("recv");
	//     exit(1);
	// }

	while (1)
	{
		if ((numbytes=send(sockfd, acceptableCommands[i % NUMBER_OF_CMD].c_str(), acceptableCommands[i % NUMBER_OF_CMD].length(), 0)) < 0) {
			perror("send");
			exit(1);
		}
		// if (numbytes != (int)sizeof(acceptableCommands[i % NUMBER_OF_CMD].length()))
		std::cout << "string length = " << (int)(acceptableCommands[i % NUMBER_OF_CMD].length()) << std::endl;
		if (numbytes != (int)(acceptableCommands[i % NUMBER_OF_CMD].length()))
			std::cout << "numbytes sended = " << numbytes << "the test message has been partially sent" << std::endl;
		else
			std::cout << "the message has been completely sent" << std::endl;
		sleep (4);
		i++;
	}
	// buf[numbytes] = '\0';

	// printf("Reçu: %s",buf);

	// close(sockfd);

	return 0;
}
