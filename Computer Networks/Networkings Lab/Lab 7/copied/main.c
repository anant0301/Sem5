#include "headers.h"

extern int client_create(int PORT, char * ip_addr);
extern int server_create(int PORT);
extern int get_router_index(char device_name);
extern void init_routing_table(char device_name[], const char  ip_addr[][IP_ADDR_LEN], const char  port[][PORT_LEN], char this_device, int  connection_matrix[][MAX_DEVICES]);
int main(int aargc, char *argv[])
{
    char ip_addr[MAX_DEVICES][IP_ADDR_LEN] = {
        "127.0.0.1", "127.0.0.1", "127.0.0.1", "127.0.0.1"
    }; 
    char devices[] = "ABCD";
    char port[] = {
        "9000", "9001", "9002", "9003"
    };
    int connection_matrix[][MAX_DEVICES]= {
        {0, 12, 1, 3},
        {12, 0, 1, 2},
        {1, 1, 0, 0},
        {3, 2, 0, 0}
    };

    printf("This device name: \n");
    char this_device = getchar();
    init_routing_table(devices, ip_addr, port, this_device, connection_matrix);
    int this_device_index = get_router_index(this_device);



    printf("\n__________________Node %d__________________\n", this_device_index);
    printf("Device Name: %c\n", rt.devices[this_device_index].device);
    printf("IP: %s\n", rt.devices[this_device_index].ip_addr);
    printf("PORT: %s\n", rt.devices[this_device_index].port);



    return 0;
}