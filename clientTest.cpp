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
    #define PORT 6667    /* Le port où le client se connectera */

    #define MAXDATASIZE 100 /* Tampon d'entrée */

    int main(int argc, char *argv[])
    {
		(void)argv;
		(void)argc;
        int sockfd, numbytes;
        // char buf[MAXDATASIZE];
        // struct hostent *he;
        struct sockaddr_in their_addr; /* Adresse de celui qui se connecte */

        // if (argc != 2) {
        //     fprintf(stderr,"usage: client hostname\n");
        //     exit(1);
        // }

        // if ((he=gethostbyname(argv[1])) == NULL) {  /* Info de l'hôte */
        //     herror("gethostbyname");
        //     exit(1);
        // }

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }

        their_addr.sin_family = AF_INET;      /* host byte order */
        their_addr.sin_port = htons(PORT);    /* short, network byte order */
        // their_addr.sin_addr = *((struct in_addr *)he->h_addr);
        their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	    bzero(&(their_addr.sin_zero), 8);     /* zero pour le reste de struct */

        if (connect(sockfd, (struct sockaddr *)&their_addr, \
                                              sizeof(struct sockaddr)) == -1) {
            perror("connect");
            exit(1);
        }

        // if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
        //     perror("recv");
        //     exit(1);
        // }

		char buff[50] = "this is a test message send by the client";

        if ((numbytes=send(sockfd, buff, MAXDATASIZE, 0)) == -1) {
            perror("send");
            exit(1);
        }
		std::cout << "the message has been sent" << std::endl;
        // buf[numbytes] = '\0';

        // printf("Reçu: %s",buf);

        // close(sockfd);

        return 0;
    }
