#include "headers.h"
void init_routing_table(char device_name[], const char  ip_addr[][IP_ADDR_LEN], const char  port[][PORT_LEN], char this_device, int  connection_matrix[][MAX_DEVICES])
{
    int this_device_index = 0;
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        if (device_name[i] == this_device)
        {
            this_device_index = i;
        }
    }
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        rt.devices[i].device = device_name[i];
        strcpy(rt.devices[i].ip_addr, ip_addr[i]);
        strcpy(rt.devices[i].port, port[i]);
        if (connection_matrix[this_device_index][i] > 0 && connection_matrix[i][this_device_index] > 0)
        {
            rt.devices[i].device_connected = connection_matrix[i][this_device_index];
        }
        else
        {
            rt.devices[i].device_connected = 0;
        }
    }    
}