#pragma once 
/*include the headers only once, even if headers are requested from multiple files*/
#ifndef headers
#define headers

/*for basic output--> printf*/
#include<stdio.h>
/*for sizeof*/
#include<stdlib.h>
/*for socket function*/
#include<unistd.h>
/*for data types like sockaddr_in/ sock_addr*/
#include<sys/types.h>
/*for socket fucntions*/
#include<netinet/in.h>
/*to get file stats*/
#include <sys/stat.h>
/*for socket functions*/
#include<sys/socket.h>
/*for the connect port to sockaddr_in*/
#include<arpa/inet.h>
/*for string compare*/
#include<string.h>
/*for clock*/
#include<time.h>

/*some random 4 digit port number */
#define PORT 9000
/*file size for transfer of the file size */
#define bsize 1024
#endif
