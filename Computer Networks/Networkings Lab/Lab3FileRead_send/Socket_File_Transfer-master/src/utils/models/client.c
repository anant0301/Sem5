#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "client.h"
#include "../argsetup.h"
#include "../protocols/TCP.h"
#include "../protocols/UDP.h"

extern void ClientStartUp(char Protocol[], char IP[], char Port[], char Filename[])
{
	int serv_sock_fd;			/* server socket file descriptor */
	int status;					/* function return status */
	struct addrinfo hints;		/* getaddrinfo setup */
	struct addrinfo *serv_info; /* server address information */
	struct addrinfo *p;			/* helper for server information */

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;												  /* either IPv4 or IPv6 */
	hints.ai_socktype = (tolower(Protocol[0]) == 't' ? SOCK_STREAM : SOCK_DGRAM); /* TCP/UDP stream socket */

	/* get server address information */
	status = getaddrinfo(IP, Port, &hints, &serv_info);

	/* getaddrinfo function error check */
	if (status != 0)
	{
		fprintf(stderr, "[error] on function getaddrinfo: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}

	/* loop through all the results and connect tot the first we can */
	for (p = serv_info; p != NULL; p = p->ai_next)
	{
		/* get socket file descriptor */
		serv_sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		/* socket function error check */
		if (serv_sock_fd < 0)
		{
			perror("[error] on function socket: ");
			continue;
		}

		/* TCP:receive */
		if (tolower(Protocol[0]) == 't')
		{
			/* connect to server socket */
			status = connect(serv_sock_fd, p->ai_addr, p->ai_addrlen);

			/* connect function error check */
			if (status < 0)
			{
				perror("[error] on function connect: ");
				close(serv_sock_fd);
				continue;
			}

#ifdef DEBUG
			/* IPv4 */
			if (p->ai_family == AF_INET)
			{
				if (inet_ntop(p->ai_family, &(((struct sockaddr_in *)p->ai_addr)->sin_addr), IP, strlen(IP)) != NULL)
				{
					printf("[client] server IPv4 address: %s\n", IP);
					printf("[client] port: %d\n", ntohs(((struct sockaddr_in *)p->ai_addr)->sin_port));
				}
				else
				{
					fprintf(stderr, "[error] on conver IPv4 address.\n");
					close(serv_sock_fd);
					exit(EXIT_FAILURE);
				}
			}
			/* IPv6 */
			else
			{
				if (inet_ntop(p->ai_family, &(((struct sockaddr_in6 *)p->ai_addr)->sin6_addr), IP, strlen(IP)) != NULL)
				{
					printf("[client] server IPv4 address: %s\n", IP);
					printf("[client] port: %d\n", ntohs(((struct sockaddr_in6 *)p->ai_addr)->sin6_port));
				}
				else
				{
					fprintf(stderr, "[error] on conver IPv6 address.\n");
					close(serv_sock_fd);
					exit(EXIT_FAILURE);
				}
			}
#endif

			break;
		}
		/* UDP:receive */
		else
			break;
	}

	/* failed to connnect */
	if (p == NULL)
	{
		fprintf(stderr, "[error] failed to connect\n");
		exit(EXIT_FAILURE);
	}

	/* TCP:send */
	if (tolower(Protocol[0]) == 't')
		TCPS(Filename, serv_sock_fd);
	/* UDP:send */
	else
		UDPS(Filename, serv_sock_fd, p);

	/* all done with this structure */
	freeaddrinfo(serv_info);

	status = close(serv_sock_fd);

	if (status < 0)
	{
		perror("[error] on client socket close: ");
		exit(EXIT_FAILURE);
	}

	return;
}
