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
#include "Includes.hpp"

#define PORT 6667    /* Le port où le client se connectera */

#define MAXDATASIZE 100 /* Tampon d'entrée */

int main(int argc, char *argv[])
{
	(void)argv;
	(void)argc;
	int sockfd, numbytes;
	// char buf[MAXDATASIZE];
	// struct hostent *he;
	struct sockaddr_in servaddr; /* Adresse de celui qui se connecte */

	// if (argc != 2) {
	//     fprintf(stderr,"usage: client hostname\n");
	//     exit(1);
	// }

	// if ((he=gethostbyname(argv[1])) == NULL) {  /* Info de l'hôte */
	//     herror("gethostbyname");
	//     exit(1);
	// }

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	else
		std::cout << "Socket created" << std::endl;

	// bzero(&servaddr, sizeof(servaddr));     /* zero struct */
	servaddr.sin_family = AF_INET;      /* host byte order */
	servaddr.sin_port = htons(PORT);    /* short, network byte order */
	// servaddr.sin_addr = *((struct in_addr *)he->h_addr);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(&(servaddr.sin_zero), 8);     /* zero pour le reste de struct */
	std::cout << "set up address" << std::endl;

	// convert the text representation of the ip address
	// into a binary representation of the address
	// if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0){
		// perror("inet_pton");
		// exit(1);
	// }

	if (connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
		perror("connect");
		exit(1);
	}
	else
		std::cout << "Conection esablished" << std::endl;

	// if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
	//     perror("recv");
	//     exit(1);
	// }

	char buff[23] = "this is a test message";
	buff[23] = '\0';
	printf("buffsize = %ld\n, buff lengh = %ld\n", sizeof(buff), strlen(buff));
	while (1)
	{
		std::cout << "start loop" << std::endl;
		if ((numbytes=send(sockfd, buff, sizeof(buff), 0)) < 0) {
			perror("send");
			exit(1);
		}
		if (numbytes != (int)sizeof(buff))
			std::cout << "the message has been partially sent" << std::endl;
		else
			std::cout << "the message has been completely sent" << std::endl;

	sleep(2);
	}

	// buf[numbytes] = '\0';

	// printf("Reçu: %s",buf);

	// close(sockfd);

	return 0;
}
