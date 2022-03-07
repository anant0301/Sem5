#include "headers.h"
int get_router_index(char device_name)
{
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        if (device_name == rt.devices[i].device)
        {
            return i;
        }
    }
    return -1;
}