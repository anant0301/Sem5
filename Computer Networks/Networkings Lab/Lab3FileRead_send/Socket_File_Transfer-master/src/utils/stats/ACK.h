#ifndef ACK_H
#define ACK_H

extern void ACK_init(unsigned long long int *num);
extern void ACK_LastStep(unsigned long long int *num);
extern void ACK_Set(unsigned long long int *num, char dst[], const char src[], unsigned long long int len);
extern int ACK_Check(unsigned long long int *num, char src[], unsigned long long int *len);

/************************************
 *	ACK encode format, x,o=[0-9]*	*
 ***********************************/
#define ACK_ENCODE "AxxxxooooxxxxooooxxxxCxxxxxK"
#define ACK_LEN ((unsigned long long int)strlen(ACK_ENCODE))
#define ACK_NUM_MAX (20)
#define ACK_FAIL (0)
#define ACK_SUCCESS (1)
#define ACK_REPEAT (-1)

#endif
