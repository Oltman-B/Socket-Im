//This is the server for my socket based console instant messanger application.
//Baruch Oltman September 2018
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    WORD wVersionRequired = MAKEWORD(2, 2);
    int error;
    
    int wsaInit = WSAStartup(wVersionRequired, &wsaData);
    if(wsaInit != 0)
    {
        printf("WSAStartup failed with error code: %d\n", wsaInit);
    }
} 
