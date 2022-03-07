#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "TCP.h"
#include "../argsetup.h"
#include "../stats/log.h"

static unsigned long long int getFileSize(FILE *fptr);

extern void TCPS(char filename[], int cfd)
{
	FILE *fptr;
	char buffer[BUF_SIZE], fbuffer[BUF_SIZE];
	unsigned long long int bytes_len_total;
	int bytes_send, bytes_left, buf_ptr;

	fptr = fopen(filename, "rb");

	/* fopen function error check */
	if (fptr == NULL)
	{
		perror("[error] file open failure: ");
		close(cfd);
		exit(EXIT_FAILURE);
	}

	/* send file name */
	memset(buffer, 0, BUF_SIZE);
	sprintf(buffer, "%s", filename);
	bytes_left = BUF_SIZE;
	buf_ptr = 0;
	do
	{
		bytes_send = send(cfd, buffer + buf_ptr, BUF_SIZE - buf_ptr, 0);

		if (bytes_send <= 0)
		{
			perror("[error] on sendind filename: ");
			close(cfd);
			exit(EXIT_FAILURE);
		}

		bytes_left -= bytes_send;
		buf_ptr += bytes_send;
	} while (bytes_left != 0);
	/* end send file name */

	/* send file length */
	memset(buffer, 0, BUF_SIZE);
	sprintf(buffer, "%llu", getFileSize(fptr));
	bytes_left = BUF_SIZE;
	buf_ptr = 0;
	do
	{
		bytes_send = send(cfd, buffer + buf_ptr, BUF_SIZE - buf_ptr, 0);

		if (bytes_send <= 0)
		{
			perror("[error] on sendind file length: ");
			close(cfd);
			exit(EXIT_FAILURE);
		}

		bytes_left -= bytes_send;
		buf_ptr += bytes_send;
	} while (bytes_left != 0);
	/* end send file length */

	/* send file content */
	if (getFileSize(fptr) != 0)
	{
		bytes_len_total = getFileSize(fptr);

		while (bytes_len_total != 0)
		{
			memset(buffer, 0, BUF_SIZE);
			bytes_left = (bytes_len_total > BUF_SIZE ? BUF_SIZE : bytes_len_total);
			buf_ptr = 0;

			do
			{
				buf_ptr += fread(buffer + buf_ptr, sizeof(char), bytes_left - buf_ptr, fptr);
			} while (buf_ptr != bytes_left);

			buf_ptr = 0;

			do
			{
				bytes_send = send(cfd, buffer + buf_ptr, bytes_left - buf_ptr, 0);

				if (bytes_send <= 0)
				{
					perror("[error] on sendind file content: ");
					close(cfd);
					exit(EXIT_FAILURE);
				}

				buf_ptr += bytes_send;
			} while (buf_ptr != bytes_left);

			bytes_len_total -= bytes_left;
		}
	}

	fclose(fptr);
	/* end send file connent */
}

extern void TCPR(int sfd)
{
	FILE *fptr;
	char buffer[BUF_SIZE];
	char filename[BUF_SIZE];
	char filelength[BUF_SIZE];
	unsigned long long int bytes_len_total;
	int bytes_recv, bytes_write, buf_ptr;
	unsigned long long int log_recv, log_total, log_cur;
	clock_t log_start, log_end;

	log_start = clock();

	/* receive file name first */
	buf_ptr = 0;
	memset(filename, 0, BUF_SIZE);
	do
	{
		bytes_recv = recv(sfd, filename + buf_ptr, BUF_SIZE - buf_ptr, 0);

		if (bytes_recv <= 0)
		{
			perror("[error] on receiving filename: ");
			close(sfd);
			exit(EXIT_FAILURE);
		}

		buf_ptr += bytes_recv;
	} while (buf_ptr != BUF_SIZE);
	/* end receive file name */

	printf("[server] filename received: %s\n", filename);

	fptr = fopen(filename, "wb");

	/* fopen function error check */
	if (fptr == NULL)
	{
		perror("[error] file open failure: ");
		close(sfd);
		exit(EXIT_FAILURE);
	}

	/* receive file length */
	buf_ptr = 0;
	memset(filelength, 0, BUF_SIZE);
	do
	{
		bytes_recv = recv(sfd, filelength + buf_ptr, BUF_SIZE - buf_ptr, 0);

		if (bytes_recv <= 0)
		{
			perror("[error] on receiving filename: ");
			close(sfd);
			exit(EXIT_FAILURE);
		}

		buf_ptr += bytes_recv;
	} while (buf_ptr != BUF_SIZE);
	/* end receive file length */

	bytes_len_total = strtoull(filelength, NULL, 10);

	/* log relative initialization */
	log_total = bytes_len_total;
	log_recv = 0;
	resetLog(&log_cur);
	/* end log relative initialization */

	printf("[server] file length received: %llu\n", bytes_len_total);

	/* receive file content */
	if (bytes_len_total != 0)
	{

		while (bytes_len_total != 0)
		{
			memset(buffer, 0, BUF_SIZE);
			bytes_write = (bytes_len_total >= BUF_SIZE ? BUF_SIZE : bytes_len_total);
			buf_ptr = 0;

			do
			{
				bytes_recv = recv(sfd, buffer + buf_ptr, bytes_write - buf_ptr, 0);

				if (bytes_recv <= 0)
				{
					perror("[error] on writing file: ");
					close(sfd);
					exit(EXIT_FAILURE);
				}

				buf_ptr += bytes_recv;
			} while (buf_ptr != bytes_write);

			buf_ptr = 0;

			do
			{
				buf_ptr += fwrite(buffer + buf_ptr, sizeof(char), bytes_write - buf_ptr, fptr);
				if (bytes_write <= 0)
				{
					perror("[error] on writing file: ");
					close(sfd);
					exit(EXIT_FAILURE);
				}
			} while (buf_ptr != bytes_write);

			bytes_len_total -= bytes_write;
			log_recv += bytes_write;

			printLog(log_recv, log_total, &log_cur);
		}
	}
	/* end receive file content */

	log_end = clock();

	printf("[server] file content received.\n");

	printThroughput(log_total + 2 * BUF_SIZE, log_end - log_start);

	fclose(fptr);
	/* end receive file connent */
}

static unsigned long long int getFileSize(FILE *fptr)
{
	unsigned long long int fsize = 0;
	fseek(fptr, 0L, SEEK_END);
	fsize = ftell(fptr);
	rewind(fptr);

	return fsize;
}
