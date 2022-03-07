#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "utils/argsetup.h"
#include "utils/models/server.h"
#include "utils/models/client.h"
#include "utils/stats/ACK.h"

static int CheckARGV(char *argv[]);

int main(int argc, char *argv[])
{
	BUILD_BUG_OR_ZERO(BUF_SIZE < NAME_SIZE_MAX);
	BUILD_BUG_OR_ZERO(BUF_SIZE < ACK_LEN);

	/* main function command line argument error check */
	if (argc < ARGC_MIN)
	{
		fprintf(stderr, "usage: ./server <protocol> <action> <ip> <port> [<file>]\n");
		exit(EXIT_FAILURE);
	}

	if (CheckARGV(argv) < 0)
	{
		fprintf(stderr, "[error] argument format error.");
		exit(EXIT_FAILURE);
	}

	/* send means client */
	if (tolower(argv[2][0]) == 's')
	{
		if (argc != 6)
		{
			fprintf(stderr, "[error] <file> input missing.");
			exit(EXIT_FAILURE);
		}

		ClientStartUp(argv[1], argv[3], argv[4], argv[5]);
	}
	/* receive means server */
	else
		ServerStartUp(argv[1], argv[3], argv[4], NULL);

	return 0;
}

static int CheckARGV(char *argv[])
{
	struct sockaddr_storage test;

	if (strcmp(argv[1], "tcp") != 0 && strcmp(argv[1], "TCP") != 0 && strcmp(argv[1], "udp") != 0 && strcmp(argv[1], "UDP") != 0)
	{
		fprintf(stderr, "[error] <protocol> options: tcp | TCP | udp | UDP\n");
		return -1;
	}
	else if (strcmp(argv[2], "send") != 0 && strcmp(argv[2], "recv") != 0)
	{
		fprintf(stderr, "[error] <action> options: send | recv\n");
		return -1;
	}
	else if (inet_pton(AF_INET, argv[3], &test) <= 0 && inet_pton(AF_INET6, argv[3], &test) <= 0)
	{
		fprintf(stderr, "[error] invalid <ip> format.\n");
		return -1;
	}
	else if (atoi(argv[4]) < 0 || atoi(argv[4]) > 65536)
	{
		fprintf(stderr, "[error] <port> range: 0~65535\n");
		return -1;
	}
	else
		return 0;
}
