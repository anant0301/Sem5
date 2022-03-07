#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SOCKERROR (-1)
#define BACK_LOG 10         // while the server listening
#define PORT_LEN 10         // PORT length stored in the router 
#define MAX_DEVICES 4       // max devices that can be connected
#define IP_ADDR_LEN 16      // length of the string containing IP_ADDR
#define MAX_STR_LEN 100     // the max length accepted in a string
#define BASE_PORT 9000
#define LIMIT 3

int serv_sock;              // socket having server sock descriptor
int client_sock[MAX_DEVICES - 1];                 // the client socket descriptor


typedef struct routing_table
{
    int sock;
    int dev_id;
    int conn_time;
} RoutingTableElement;            // the routing details of other devices stored in the router

typedef struct Info
{
    char * ip_addr; 
    int * ports;
    int * connection_matrix[MAX_DEVICES];
    int mapping[MAX_DEVICES][2];
}Info;

typedef struct router_device
{
    int dev_id;
    char ip_addr[IP_ADDR_LEN];
    int port;
    int serv_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr[MAX_DEVICES - 1];
    socklen_t sock_addr_len;
    int num_device_conn;    
    int client_sock[MAX_DEVICES - 1];
    RoutingTableElement elements[MAX_DEVICES - 1];
    pthread_t client_req_response;
    pthread_t client_threads[MAX_DEVICES - 1];
    Info * connection_info;
    pthread_t sending_thread;
    int num_serv_conn;
    int runner;
    int flag;
} Router;                   // the router device  

int check(int val, char err_msg[]);
Router *new_router(int dev_id, int port, char ip_addr[]);
void * accept_client(void * param);
void * server_response(void * param);
int getIndex(Router * this, int id);
int compare(Router * this, int index, int new_time);
void * server_response(void * param);
int create_client_conn(int port);
void * router_client(void * param);
void destroy(Router * this);

// thread synchronization variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t dest_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t conditional_var = PTHREAD_COND_INITIALIZER;
pthread_cond_t dest_wait = PTHREAD_COND_INITIALIZER;


int ports[MAX_DEVICES];
char ip_addr[MAX_DEVICES][IP_ADDR_LEN];
int connection_matrix[MAX_DEVICES][MAX_DEVICES];
int device_id[MAX_DEVICES];

int main(int argc, char * argv[])
{
    // data initialization, the choices of the port numbers, ip address, possible device_id and connection matrix
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        device_id[i] = i;
        ports[i] = BASE_PORT + i * MAX_DEVICES;
        strcpy(ip_addr[i], "127.0.0.1");
    }
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        for (int j = 0; j < i; j++)
        {
            connection_matrix[i][j] = connection_matrix[j][i] = rand() % LIMIT;
        }
    }
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        for (int j = 0; j < MAX_DEVICES; j++)
        {
            printf("%d\t", connection_matrix[j][i]);
        }
        printf("\n");
    }
    
    // i plan to have ids as the 0,1,2,3 and hence the offsets 
    // these offsets will ensure give us the additional client ports
    // the ports[] contains the 4 server nodes planned
    int id;
    printf("Enter the Id of the device using: ");
    scanf("%d", &id);
    int offset = id;
    Router * this_router = new_router(device_id[id], ports[id], ip_addr[id]);
    // sleep(30);
    while(this_router-> runner);
    // destroy(this_router);
    printf("\nSuccessful termination\n");
}
int check(int val, char err_msg[])
{
    if(val == SOCKERROR)
    {
        printf("%s\n", err_msg);
        return 0;
    }
    return 1;
}

Router *new_router(int dev_id, int port, char ip_addr[])
{
    /*
    create a basic server socket and add client socket accept 
    */
    Router *this = malloc(sizeof(Router));
    this-> dev_id = dev_id;
    this-> port = port;
    strcpy(this-> ip_addr, ip_addr);
    this-> serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    this-> serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this-> serv_addr.sin_family = AF_INET;
    this-> serv_addr.sin_port = htons(this-> port);
    this-> sock_addr_len = sizeof(struct sockaddr);
    this-> num_device_conn = 0; 
    this-> flag = 0;
    this-> num_serv_conn = 0;
    this-> runner = 1;
    
    
    // this-> connection_info = malloc(sizeof(Info));
    // for (int i = 0; i < MAX_DEVICES; i++)
    // {
    //     this-> connection_info-> connection_matrix[i] = connection_matrix[i];
    // }
    // this-> connection_info-> ip_addr = ip_addr;
    // this-> connection_info-> ports = ports;
    // for (int i = 0; i < MAX_DEVICES; i++)
    // {    
    //     this-> connection_info-> mapping[i][0] = i;
    //     this-> connection_info-> mapping[i][1] = device_id[i];
    // }
    // Info * conn_info = this-> connection_info;
    // for (int j = 0; j < MAX_DEVICES; j++)
    // {
    //     if(conn_info-> connection_matrix[this-> dev_id][j])
    //     {
    //         do
    //         {
    //             this-> client_sock[this-> num_serv_conn] = create_client_conn(ports[j]);
    //         }while(this-> client_sock[this-> num_serv_conn] == -1);
    //         this-> num_serv_conn++;
    //     }
    // }
    check(bind(this-> serv_sock, (struct sockaddr*)&this-> serv_addr, this-> sock_addr_len), "Binding Failure");
    check(listen(this-> serv_sock, BACK_LOG), "Listening Failure");
    printf("The thread accept_client\n");
    pthread_create(&(this-> client_req_response), NULL, accept_client, this);
    for (int i = 0; i < MAX_DEVICES - 1; i++)
    {
        this-> elements[i].sock = -1;
        this-> elements[i].dev_id = -1;
        this-> elements[i].conn_time = -1;
    }
    pthread_create(&(this-> sending_thread), NULL, router_client, this-> connection_info);
    return this;
}

void * accept_client(void * param)
{
    Router * this = param;
    printf("\nServer accepting new client\n");
    while(this-> num_device_conn < MAX_DEVICES - 1 && this-> runner)
    {
        // accept client conenction from different routers and establish a connection
        struct sockaddr_in new = this-> client_addr[this-> num_device_conn];
        int len = sizeof(this-> client_addr[this-> num_device_conn]);
        this-> elements[this-> num_device_conn].sock = accept(this-> serv_sock, (struct sockaddr *)&new, &len);
        printf("The socket %d\n", this-> elements[this-> num_device_conn].sock);
        if(this-> elements[this-> num_device_conn].sock >= 0)
        {
            pthread_create(&(this-> client_threads[this-> num_device_conn]), NULL, server_response, this);
            pthread_cond_wait(&conditional_var, &mutex);
            printf("\nServer accepting new client again\n");
            ++this-> num_device_conn;
        }
        sleep(1);
    }
    pthread_exit(NULL);
}

void * server_response(void * param)
{
    /*
    take the inputs from the client
    */
    Router * device = param;
    char buffer[MAX_STR_LEN];
    int index = device-> num_device_conn;
    pthread_cond_signal(&conditional_var);
    RoutingTableElement * this = &(device-> elements[index]);
    printf("The client is received\n");
    recv(this-> sock, buffer, MAX_STR_LEN, 0);
    printf("\nNew device Conencted\n");
    char * token; // = strtok(buffer, "_");
    int recv_id;
    int recv_time;
    int recv_index;
    for (int i = 0; (i < MAX_DEVICES - 1) && (device-> runner); i++)
    {
        bzero(buffer, MAX_STR_LEN);
        printf("\nThe device info sent: %s\n", buffer);
        recv(this-> sock, buffer, MAX_STR_LEN, 0);
        pthread_mutex_lock(&mutex);
        while(token != NULL)
        {
            token = strtok(buffer, "_");
            recv_id = atoi(token);
            token = strtok(buffer, ";");
            recv_time = atoi(token);
            recv_index = getIndex(device, recv_id);
            if(recv_index != -1)
            {
                if (compare(device, recv_index, recv_time))
                {
                    device-> elements[recv_index].conn_time = recv_index;
                }
            }
            else
            {
                recv_index = device-> num_device_conn++;
                device-> elements[recv_index].dev_id = recv_id;
                device-> elements[recv_index].conn_time = recv_time;
                device-> elements[recv_index].conn_time = recv_index;
            }
        }
        device-> flag++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int getIndex(Router * this, int id)
{
    /*
    get index in the element in the router table element array for the id passed
    */
    for (int i = 0; i < this-> num_device_conn; i++)
    {
        if(this-> elements[i].dev_id == id)
        {
            return i;
        }
    }
    return -1;
}

int compare(Router * this, int index, int new_time)
{
    /*
    return the true if the new_time value should be updated in the routing table element 
    */
    return this-> elements[index].conn_time > new_time;
}

int create_client_conn(int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr)); 

    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
        printf("Error in connections %d\n", port);
        sleep(1);
        return -1;
    }
    return sock;
}


void * router_client(void * param)
{
    /*
    function where the router sends request for connections to other sockets as client 
    and also passes the any updates in the value from the prev routing table
    pattern of sending the information over to the other Routers-- id_time_taken;id_time_taken;...
    */
    Router * this = param;
    
    // for (int j = 0; j < MAX_DEVICES; j++)
    // {
    //     if(conn_info-> connection_matrix[this-> dev_id][j])
    //     {
    //         client_sock[this-> num_serv_conn] = socket(AF_INET, SOCK_STREAM, 0);
    //         this-> client_addr[this-> num_serv_conn].sin_addr.s_addr = htonl(INADDR_ANY);
    //         this-> client_addr[this-> num_serv_conn].sin_family = AF_INET;
    //         this-> client_addr[this-> num_serv_conn].sin_port = htons(conn_info-> ports[j]);
    //         check(connect(this-> client_sock[this-> num_serv_conn], (struct sockaddr *)&(this-> client_addr[this-> num_serv_conn]), this-> sock_addr_len), "Client Connection Error ");
    //         this-> num_serv_conn++;
    //     }
    // } 
    
    this-> connection_info = malloc(sizeof(Info));
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        this-> connection_info-> connection_matrix[i] = connection_matrix[i];
    }
    strcpy(this-> connection_info-> ip_addr, ip_addr[this-> connection_info-> mapping[this-> dev_id][1]]);
    this-> connection_info-> ports = ports;
    for (int i = 0; i < MAX_DEVICES; i++)
    {    
        this-> connection_info-> mapping[i][0] = i;
        this-> connection_info-> mapping[i][1] = device_id[i];
    }
    Info * conn_info = this-> connection_info;
    for (int j = 0; j < MAX_DEVICES; j++)
    {
        if(conn_info-> connection_matrix[this-> dev_id][j])
        {
            do
            {
                this-> client_sock[this-> num_serv_conn] = create_client_conn(ports[j]);
            }while(this-> client_sock[this-> num_serv_conn] == -1);
            this-> num_serv_conn++;
        }
    }
    
    // Info * conn_info = this-> connection_info;
    char buffer[MAX_STR_LEN];
    char addition[MAX_STR_LEN];

    for (int i = 0; i < this-> num_device_conn; i++)
    {
        bzero(addition, MAX_STR_LEN);
        sprintf(addition, "%d_%d;", this-> dev_id, this-> elements[i].conn_time);
        strcat(buffer, addition);
    }
    printf("Broadcasting\n");
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        send(this-> client_sock[i], buffer, MAX_STR_LEN, 0);
    }
        

    int flag = 0;
    while(this-> runner)
    {
        if (this-> flag != flag)
        {
            printf("Runner has changed\n");
            bzero(buffer, MAX_STR_LEN);
            pthread_mutex_lock(&mutex);
            for (int i = 0; i < this-> num_device_conn; i++)
            {
                bzero(addition, MAX_STR_LEN);
                sprintf(addition, "%d_%d;", this-> dev_id, this-> elements[i].conn_time);
                strcat(buffer, addition);
            }
            printf("%s\n", buffer);
            for (int j = 0; j < this-> num_serv_conn; j++)
            {
                send(this-> client_sock[j], buffer, MAX_STR_LEN, 0);
            }
            pthread_mutex_unlock(&mutex);
            flag = this-> flag;
        }
    }
    for (int i = 0; i < this-> num_serv_conn; i++)
    {
        close(this-> client_sock[i]);
    }
    pthread_exit(NULL);
}


void destroy(Router * this)
{
    /*
    join all threads and close all sockets
    */
    pthread_cond_wait(&dest_wait, &dest_mutex);
    printf("\nThe process is to be terminated or not y / n: ");
    while(getc(stdin) != 'y')
    {
        sleep(1);
        printf("\nThe process is to be terminated or not y / n: ");
    };
    pthread_mutex_unlock(&mutex);
    printf("Termination Proces begin\n");
    this-> runner = 0;
    pthread_join(this-> client_req_response, NULL);
    pthread_join(this-> sending_thread, NULL);
    printf("\nFinal Routing Table device ID: %d\n", this-> dev_id);
    for (int i = 0; i < this-> num_device_conn - 1; i++)
    {
        printf("\n%d and %d -- connection time --  %d\n ", this-> dev_id, this-> elements[i].dev_id, this-> elements[i].conn_time);
        close(this-> elements[i].sock);
    }
    pthread_join(this-> serv_sock, NULL);
}
