#include <iostream>
#include <pthread.h>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

#define MAX_DEV 4
#define SOCKERROR (-1)



void check(int ret_val, string error_msg);
class Router{
    string name;
    int port;
    string ip_addr;
    struct sockaddr_in serv_addr;
    socklen_t sock_addr_length;
    int serv_sock;
    int dev_conn;
    int client_sock[MAX_DEV - 1]; 
    pthread_t client_req_response;
    Router(string name, int port, string ip_addr);
    void create_serv_socket();
    void client_resp();
    void * accept_client(void * param);
};


int main(int argc, char * argv[])
{
    return 0;
}
void check(int ret_val, string error_msg)
{
    if(ret_val == SOCKERROR)
        cout << error_msg << endl;
}

Router::Router(string name, int port, string ip_addr)
{
    this-> name = name;
    this-> port = port;
    this-> ip_addr = ip_addr;
    this-> dev_conn = 0;
    this-> sock_addr_length = sizeof(this-> serv_addr);
    this-> create_serv_socket();
    check(listen(serv_sock, 4), "Listening Failure");
    // a thread to continue to listen to client requests 
    pthread_create(&client_req_response, NULL, Router::accept_client, this);
}
void Router::create_serv_socket()
{
    // creating a basic server socket and binding it to the port
    this-> serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    this-> serv_addr.sin_family = AF_INET;
    this-> serv_addr.sin_port = htons(this-> port);
    this-> serv_addr.sin_addr.s_addr = INADDR_ANY;
    check(bind(this-> serv_sock, (struct sockaddr *)&(this-> serv_addr), this-> sock_addr_length), "Bind Failure");
}
void * Router::accept_client(void * param)
{
    Router * self = (Router *) param;
    // accept client connections from different routers
    int i = 0;
    while( self-> dev_conn < 3)
    {
        self-> client_sock[i] = accept(self-> serv_sock, (struct sockaddr *)&(self-> serv_addr), &(self-> sock_addr_length));
        if(self-> client_sock[i] > 0)
        {

        }
    }    
}

void Router::client_resp()
{
    
}