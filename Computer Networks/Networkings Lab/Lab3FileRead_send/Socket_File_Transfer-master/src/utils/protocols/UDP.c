#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "UDP.h"
#include "../argsetup.h"
#include "../stats/ACK.h"
#include "../stats/log.h"

static unsigned long long int getFileSize(FILE *fptr);

extern void UDPS(char filename[], int sfd, struct addrinfo *send_info)
{
	FILE *fptr;
	char buffer[BUF_SIZE + ACK_LEN], fbuffer[BUF_SIZE], ACKbuffer[ACK_LEN];
	unsigned long long int bytes_len_total;
	int bytes_send, bytes_recv, bytes_left, bytes_read, buf_ptr;

	unsigned long long int ACK_counter;
	int ACK_status;

	struct sockaddr recv_info;
	socklen_t addr_len;
	int log_lost, log_total;
	clock_t log_start, log_end;

	/* startup initialization */
	fptr = fopen(filename, "rb");

	/* fopen function error check */
	if (fptr == NULL)
	{
		perror("[error] file open failure: ");
		close(sfd);
		exit(EXIT_FAILURE);
	}

	ACK_init(&ACK_counter);
	addr_len = sizeof(addr_len);
	log_lost = 0;

	fcntl(sfd, F_SETFL, O_NONBLOCK); /* set socket non-blocking for polling */

	log_start = clock();
	/* end startup initialization */

	/* send file name */
	memset(buffer, 0, BUF_SIZE + ACK_LEN);
	ACK_Set(&ACK_counter, buffer, filename, strlen(filename));
	bytes_left = BUF_SIZE + ACK_LEN;
	do
	{
		buf_ptr = 0;
		do
		{
			bytes_send = sendto(sfd, buffer + buf_ptr, BUF_SIZE + ACK_LEN - buf_ptr, 0, send_info->ai_addr, send_info->ai_addrlen);
			if (bytes_send <= 0)
			{
				perror("[error] on sendind filename: ");
				close(sfd);
				exit(EXIT_FAILURE);
			}

			buf_ptr += bytes_send;
		} while (bytes_left != buf_ptr);

		usleep(UDP_USEC_SLEEP_TO_RECV); /* minimum time to wait for package arrive */
		memset(ACKbuffer, 0, ACK_LEN);

		buf_ptr = 0;
		do
		{
			bytes_recv = recvfrom(sfd, ACKbuffer + buf_ptr, ACK_LEN - buf_ptr, 0, &recv_info, &addr_len);

			if (bytes_recv <= 0)
			{
				/* doesn't get anything */
				if (errno == EWOULDBLOCK)
					break;
				else
				{
					perror("[error] on receiving filename ACK: ");
					close(sfd);
					exit(EXIT_FAILURE);
				}
			}

			buf_ptr += bytes_recv;
		} while (buf_ptr != ACK_LEN);

		if ((ACK_status = ACK_Check(&ACK_counter, ACKbuffer, NULL)) == ACK_FAIL)
		{
			fprintf(stderr, "[error] on receiving filename ACK check failed.\n");
			log_lost += ACK_LEN;
			usleep(UDP_USEC_SLEEP_TO_RESEND);
			continue;
		}
		else if (ACK_status == ACK_REPEAT)
		{
			//fprintf(stderr, "[error] on receving file content AKC check repeat.\n");
			usleep(UDP_USEC_SLEEP_TO_RESEND);
		}
	} while (ACK_status != ACK_SUCCESS);
	/* end send file name */

	printf("[client] filename sent.\n");

	/* send file length */
	memset(buffer, 0, BUF_SIZE + ACK_LEN);
	memset(fbuffer, 0, BUF_SIZE);
	memset(ACKbuffer, 0, ACK_LEN);
	sprintf(fbuffer, "%llu", getFileSize(fptr));
	ACK_Set(&ACK_counter, buffer, fbuffer, strlen(fbuffer));
	bytes_left = BUF_SIZE + ACK_LEN;
	do
	{
		buf_ptr = 0;
		do
		{
			bytes_send = sendto(sfd, buffer + buf_ptr, BUF_SIZE + ACK_LEN - buf_ptr, 0, send_info->ai_addr, send_info->ai_addrlen);

			if (bytes_send <= 0)
			{
				perror("[error] on sendind file length: ");
				close(sfd);
				exit(EXIT_FAILURE);
			}

			buf_ptr += bytes_send;
		} while (bytes_left != buf_ptr);

		usleep(UDP_USEC_SLEEP_TO_RECV); /* minimum time to wait for package arrive */
		memset(ACKbuffer, 0, ACK_LEN);
		buf_ptr = 0;

		do
		{
			bytes_recv = recvfrom(sfd, ACKbuffer + buf_ptr, ACK_LEN - buf_ptr, 0, &recv_info, &addr_len);

			if (bytes_recv <= 0)
			{
				if (errno == EWOULDBLOCK)
				{
					break;
				}
				else
				{
					perror("[error] on receiving file length ACK: ");
					close(sfd);
					exit(EXIT_FAILURE);
				}
			}
			buf_ptr += bytes_recv;
		} while (buf_ptr != ACK_LEN);

		if ((ACK_status = ACK_Check(&ACK_counter, ACKbuffer, NULL)) == ACK_FAIL)
		{
			fprintf(stderr, "[error] on receiving file length ACK check failed.\n");
			log_lost += ACK_LEN;
			usleep(UDP_USEC_SLEEP_TO_RESEND);
			continue;
		}
		else if (ACK_status == ACK_REPEAT)
		{
			//fprintf(stderr, "[error] on receving file content AKC check repeat.\n");
			usleep(UDP_USEC_SLEEP_TO_RESEND);
		}
	} while (ACK_status != ACK_SUCCESS);
	/* end send file length */

	printf("[client] file length sent.\n");

	/* send file content */
	bytes_len_total = getFileSize(fptr);
	log_total = (bytes_len_total / BUF_SIZE + (bytes_len_total % BUF_SIZE == 0 ? 0 : 1) + 2) * ACK_LEN;
	while (bytes_len_total != 0)
	{
		memset(fbuffer, 0, BUF_SIZE);
		bytes_left = (bytes_len_total >= BUF_SIZE ? BUF_SIZE : bytes_len_total);
		buf_ptr = 0;
		do
		{
			bytes_read = fread(fbuffer + buf_ptr, sizeof(char), BUF_SIZE - buf_ptr, fptr);

			if (bytes_read <= 0)
			{
				perror("[error] on reading file content: ");
				close(sfd);
				exit(EXIT_FAILURE);
			}

			buf_ptr += bytes_read;
		} while (bytes_left != buf_ptr);

		memset(buffer, 0, BUF_SIZE + ACK_LEN);
		memset(ACKbuffer, 0, ACK_LEN);
		ACK_Set(&ACK_counter, buffer, fbuffer, bytes_left);
		bytes_left += ACK_LEN;
		do
		{
			buf_ptr = 0;
			do
			{
				bytes_send = sendto(sfd, buffer + buf_ptr, bytes_left - buf_ptr, 0, send_info->ai_addr, send_info->ai_addrlen);

				if (bytes_send <= 0)
				{
					perror("[error] on sendind file content: ");
					close(sfd);
					exit(EXIT_FAILURE);
				}

				buf_ptr += bytes_send;
			} while (bytes_left != buf_ptr);

			usleep(UDP_USEC_SLEEP_TO_RECV); /* minimum time to wait for package arrive */
			memset(ACKbuffer, 0, ACK_LEN);
			buf_ptr = 0;
			do
			{
				bytes_recv = recvfrom(sfd, ACKbuffer + buf_ptr, ACK_LEN - buf_ptr, 0, &recv_info, &addr_len);

				if (bytes_recv <= 0)
				{
					if (errno == EWOULDBLOCK)
					{
						break;
					}
					else
					{
						perror("[error] on receiving file content ACK: ");
						close(sfd);
						exit(EXIT_FAILURE);
					}
				}
				buf_ptr += bytes_recv;
			} while (buf_ptr != ACK_LEN);

			if ((ACK_status = ACK_Check(&ACK_counter, ACKbuffer, NULL)) == ACK_FAIL)
			{
				fprintf(stderr, "[error] on receiving file content ACK check failed.\n");
				log_lost += ACK_LEN;
				usleep(UDP_USEC_SLEEP_TO_RESEND);
				continue;
			}
			else if (ACK_status == ACK_REPEAT)
			{
				//fprintf(stderr, "[error] on receving file content AKC check repeat.\n");
				usleep(UDP_USEC_SLEEP_TO_RESEND);
			}
		} while (ACK_status != ACK_SUCCESS);

		bytes_len_total -= (bytes_left - ACK_LEN);
	}

	log_end = clock();

	printf("[client] file content sent.\n");

	printLostRate(log_lost, log_total);
	printThroughput(log_total, log_end - log_start);

	fclose(fptr);
	/* end send file connent */
}

extern void UDPR(int sfd)
{
	FILE *fptr;
	char buffer[BUF_SIZE + ACK_LEN];
	char filename[BUF_SIZE];
	char filelength[BUF_SIZE];
	char ACKbuffer[ACK_LEN];
	unsigned long long int bytes_len_total;
	int bytes_send, bytes_recv, bytes_will_get, bytes_write, buf_ptr;
	unsigned long long int ACK_counter, ACK_bytes_len;
	int ACK_status;
	struct sockaddr recv_info;
	socklen_t addr_len;
	unsigned long long int log_recv, log_total, log_cur, log_lost;
	clock_t log_start, log_end;

	/* startup initialization */
	ACK_init(&ACK_counter);
	addr_len = sizeof(recv_info);
	log_recv = 0;
	log_lost = 0;
	resetLog(&log_cur);
	log_start = clock();
	/* end startup initialization */

	/* receive file name first */
	bytes_will_get = BUF_SIZE + ACK_LEN;
	do
	{
		memset(buffer, 0, BUF_SIZE + ACK_LEN);
		buf_ptr = 0;
		do
		{
			bytes_recv = recvfrom(sfd, buffer + buf_ptr, BUF_SIZE + ACK_LEN - buf_ptr, 0, &recv_info, &addr_len);
			if (bytes_recv <= 0)
			{
				perror("[error] on receiving filename: ");
				close(sfd);
				exit(EXIT_FAILURE);
			}

			buf_ptr += bytes_recv;
		} while (bytes_will_get != buf_ptr);

		if ((ACK_status = ACK_Check(&ACK_counter, buffer, &ACK_bytes_len)) == ACK_FAIL)
		{
			fprintf(stderr, "[error] on received filename ACK check failed.\n");
			log_lost += ACK_bytes_len;
			continue;
		}
		else if (ACK_status == ACK_REPEAT)
		{								/* ACK check repeat */
			ACK_LastStep(&ACK_counter); /* set ACK_counter to last step */
			printf("file name repeat\n");
		}

		/* ACK check success or repeat, both need to resend ACK */
		ACK_Set(&ACK_counter, ACKbuffer, "", 0);
		buf_ptr = 0;
		do
		{
			bytes_send = sendto(sfd, ACKbuffer + buf_ptr, ACK_LEN - buf_ptr, 0, &recv_info, addr_len);

			if (bytes_send <= 0)
			{
				perror("[error] on sending filename ACK: ");
				close(sfd);
				exit(EXIT_FAILURE);
			}

			buf_ptr += bytes_send;
		} while (buf_ptr != ACK_LEN);

	} while (ACK_status != ACK_SUCCESS); /* redo on ACK check failed */

	buffer[ACK_bytes_len] = '\0';
	memset(filename, 0, BUF_SIZE);
	sprintf(filename, "%s", buffer);
	/* end receive file name */

	printf("[server] filename received: %s\n", filename);

	fptr = fopen(filename, "wb");

	if (fptr == NULL)
	{ /* fopen function error check */
		perror("[error] file open failure: ");
		close(sfd);
		exit(EXIT_FAILURE);
	}

	/* receive file length */
	memset(buffer, 0, BUF_SIZE + ACK_LEN);
	memset(ACKbuffer, 0, ACK_LEN);
	bytes_will_get = BUF_SIZE + ACK_LEN;

	do
	{
		buf_ptr = 0;
		do
		{
			bytes_recv = recvfrom(sfd, buffer + buf_ptr, BUF_SIZE + ACK_LEN - buf_ptr, 0, &recv_info, &addr_len);

			if (bytes_recv <= 0)
			{
				perror("[error] on receiving file length: ");
				close(sfd);
				exit(EXIT_FAILURE);
			}

			buf_ptr += bytes_recv;
		} while (bytes_will_get != buf_ptr);

		if ((ACK_status = ACK_Check(&ACK_counter, buffer, &ACK_bytes_len)) == ACK_FAIL)
		{
			fprintf(stderr, "[error] on received filename ACK check failed.\n");
			log_lost += ACK_bytes_len;
			continue;
		}
		else if (ACK_status == ACK_REPEAT)
		{								/* ACK check repeat */
			ACK_LastStep(&ACK_counter); /* set ACK_counter to last step */
			printf("file length repeat\n");
		}

		/* ACK check success or repeat, both need to resend ACK */
		ACK_Set(&ACK_counter, ACKbuffer, "", 0);
		buf_ptr = 0;
		do
		{
			bytes_send = sendto(sfd, ACKbuffer + buf_ptr, ACK_LEN - buf_ptr, 0, &recv_info, addr_len);

			if (bytes_send <= 0)
			{
				perror("[error] on sending filename ACK: ");
				close(sfd);
				exit(EXIT_FAILURE);
			}

			buf_ptr += bytes_send;
		} while (buf_ptr != ACK_LEN);
	} while (ACK_status != ACK_SUCCESS);

	buffer[ACK_bytes_len] = '\0';
	memset(filelength, 0, BUF_SIZE);
	sprintf(filelength, "%s", buffer);
	/* end receive file length */

	bytes_len_total = strtoull(filelength, NULL, 10);
	log_total = bytes_len_total;

	printf("[server] file length received: %llu\n", bytes_len_total);

	/* receive file content */
	while (bytes_len_total != 0)
	{
		memset(buffer, 0, BUF_SIZE + ACK_LEN);
		memset(ACKbuffer, 0, ACK_LEN);
		bytes_will_get = (bytes_len_total >= BUF_SIZE ? BUF_SIZE : bytes_len_total) + ACK_LEN;
		do
		{
			buf_ptr = 0;
			do
			{
				bytes_recv = recvfrom(sfd, buffer + buf_ptr, bytes_will_get - buf_ptr, 0, &recv_info, &addr_len);

				if (bytes_recv <= 0)
				{
					perror("[error] on receiving file content: ");
					close(sfd);
					exit(EXIT_FAILURE);
				}

				buf_ptr += bytes_recv;
			} while (bytes_will_get != buf_ptr);

			if ((ACK_status = ACK_Check(&ACK_counter, buffer, &ACK_bytes_len)) == ACK_FAIL)
			{
				fprintf(stderr, "[error] on received filename ACK check failed.\n");
				log_lost += ACK_bytes_len;
				continue;
			}
			/* ACK check repeat */
			else if (ACK_status == ACK_REPEAT)
				ACK_LastStep(&ACK_counter); /* set ACK_counter to last step */

			/* ACK check success or repeat, both need to resend ACK */
			ACK_Set(&ACK_counter, ACKbuffer, "", 0);
			buf_ptr = 0;
			do
			{
				bytes_send = sendto(sfd, ACKbuffer + buf_ptr, ACK_LEN - buf_ptr, 0, &recv_info, addr_len);

				if (bytes_send <= 0)
				{
					perror("[error] on sending filename ACK: ");
					close(sfd);
					exit(EXIT_FAILURE);
				}

				buf_ptr += bytes_send;
			} while (buf_ptr != ACK_LEN);
		} while (ACK_status != ACK_SUCCESS);

		buf_ptr = 0;

		do
		{
			bytes_write = fwrite(buffer + buf_ptr, sizeof(char), ACK_bytes_len - buf_ptr, fptr);

			if (bytes_write <= 0)
			{
				perror("[error] on writing file content: ");
				close(sfd);
				exit(EXIT_FAILURE);
			}

			buf_ptr += bytes_write;
		} while (ACK_bytes_len != buf_ptr);

		bytes_len_total -= ACK_bytes_len;
		log_recv += ACK_bytes_len;
		printLog(log_recv, log_total, &log_cur);
	}
	/* end receive file content */

	log_end = clock();

	printf("[server] file content received.\n");

	printLostRate(log_lost, log_total + 2 * BUF_SIZE);
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
