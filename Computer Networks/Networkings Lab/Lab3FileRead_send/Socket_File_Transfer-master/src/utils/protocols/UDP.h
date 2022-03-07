#ifndef UDP_H
#define UDP_H
#include "argsetup.h"

#define UDP_USEC_SLEEP_TO_RECV (100)
#define UDP_USEC_SLEEP_TO_RESEND (100)

extern void UDPS(char filename[], int sfd, struct addrinfo *send_info);
extern void UDPR(int sfd);

#endif
