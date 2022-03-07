#include "headers.h"
int cfileexists(const char* filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if(exist == 0)
    {
        return 1;
    }
    else 
    {
        return 0;
	}
}