#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>

#include "server.h"
#include "../argsetup.h"
#include "../protocols/TCP.h"
#include "../protocols/UDP.h"

#ifdef DEBUG
static void sigchld_handler(int s);
#endif

extern void ServerStartUp(char Protocol[], char IP[], char Port[], char Filename[])
{
	int serv_sock_fd;				   /* server socket file descriptor */
	int clie_sock_fd;				   /* client socket file descriptor */
	int status;						   /* function return status */
	struct addrinfo hints;			   /* helper for constructing server information */
	struct addrinfo *p;				   /* helper for finding valid socket */
	struct addrinfo *serv_info;		   /* server socket information */
	struct sockaddr_storage clie_info; /* client socket information */
	socklen_t addrlen;				   /* client socket information size */
	int yes = 1;					   /* don't know what is this */
	struct sigaction sa;			   /* signal.h relative */

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;												  /* either IPv4 or IPv6 */
	hints.ai_socktype = (tolower(Protocol[0]) == 't' ? SOCK_STREAM : SOCK_DGRAM); /* TCP or UDP socket stream */
	hints.ai_flags = AI_PASSIVE;												  /* automatically fill in IP */

	status = getaddrinfo(NULL, Port, &hints, &serv_info);

	/* getaddrinfo function error check */
	if (status != 0)
	{
		fprintf(stderr, "[error] on function getaddrinfo: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}

	/* loop through all the results and bind to the first we can */
	for (p = serv_info; p != NULL; p = p->ai_next)
	{
		/* get socket fild descriptor */
		serv_sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		/* socket function error check */
		if (serv_sock_fd < 0)
		{
			perror("[error] on function socket: ");
			continue;
		}

		/* avoid the error message: "address already in use" */
		//status = setsockopt(serv_sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		/* sersockopt function error check */
		if (status < 0)
		{
			perror("[error] on function setsockopt: ");
			exit(EXIT_FAILURE);
		}

		/* bind socket to PORT */
		status = bind(serv_sock_fd, p->ai_addr, p->ai_addrlen);

		/* bind function error check */
		if (status < 0)
		{
			close(serv_sock_fd);
			perror("[error] on function bind: ");
			continue;
		}

		break;
	}

	if (p == NULL)
	{
		fprintf(stderr, "[error] failed to bind.\n");
		exit(EXIT_FAILURE);
	}

	/* all done with this structure */
	freeaddrinfo(serv_info);

	/* TCP receive */
	if (tolower(Protocol[0]) == 't')
	{
		/* listening request */
		status = listen(serv_sock_fd, BACKLOG);

		/* listen function error check */
		if (status < 0)
		{
			perror("[error] on listen: ");
			exit(EXIT_FAILURE);
		}

#ifdef DEBUG
		sa.sa_handler = sigchld_handler; /* reap all dead processes */
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;

		if (sigaction(SIGCHLD, &sa, NULL) == -1)
		{
			perror("[error] on function sigaction: ");
			exit(EXIT_FAILURE);
		}
#endif

		printf("[server] waiting for connections by TCP...\n");

		/* accept connection */
		addrlen = sizeof(struct sockaddr_storage);
		clie_sock_fd = accept(serv_sock_fd, (struct sockaddr *)&clie_info, &addrlen);

		/* accept function error check */
		if (clie_sock_fd < 0)
		{
			perror("[error] on function accept: ");
			close(serv_sock_fd);
			exit(EXIT_FAILURE);
		}

#ifdef DEBUG
		/* Display the client's address */
		/* IPv4 version */
		if (clie_info.ss_family == AF_INET)
		{
			if (inet_ntop(AF_INET, &(((struct sockaddr_in *)&clie_info)->sin_addr), IP, strlen(IP)) != NULL)
			{
				printf("[server] got connect from IPv4 address: %s\n", IP);
				printf("[server] port: %d\n", ntohs(((struct sockaddr_in *)&clie_info)->sin_port));
			}
			else
			{
				fprintf(stderr, "[error] on convert IPv4 address.\n");
				close(clie_sock_fd);
				close(serv_sock_fd);
				exit(EXIT_FAILURE);
			}
		}
		/* IPv6 version */
		else
		{
			if (inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)&clie_info)->sin6_addr), IP, strlen(IP)) != NULL)
			{
				printf("[server] got connect from IPv6 address: %s\n", IP);
				printf("[server] port: %d\n", ntohs(((struct sockaddr_in6 *)&clie_info)->sin6_port));
			}
			else
			{
				fprintf(stderr, "[error] on convert IPv6 address.\n");
				close(clie_sock_fd);
				close(serv_sock_fd);
				exit(EXIT_FAILURE);
			}
		}
#endif
		TCPR(clie_sock_fd);

		status = close(clie_sock_fd);

		if (status < 0)
		{
			perror("[error] on client socket close: ");
			close(serv_sock_fd);
			exit(EXIT_FAILURE);
		}
	}
	/* end TCP receive */
	/* UDP receive */
	else
	{
		printf("[server] waiting for connections by UDP...\n");

		UDPR(serv_sock_fd);
	}
	/* end UDP receive */

	status = close(serv_sock_fd);

	if (status < 0)
	{
		perror("[error] on server socket close: ");
		exit(EXIT_FAILURE);
	}
}

#ifdef DEBUG
static void sigchld_handler(int s)
{
	/* waitpid() might overwrite errno, so we save and restore it. */
	int saved_errno = errno;

	while (waitpid(-1, NULL, WNOHANG) > 0)
		;

	errno = saved_errno;
}
#endif
