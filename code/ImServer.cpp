/*****************************************************************************
 This is the server for my socket based console instant messanger application.
Baruch Oltman September 2018
     ****************************************************************************/
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

// TODO(baruch): Only supporting ascii consider Unicode later
#undef UNICODE

#define DEFAULT_PORT "27015"

int main(int argc, char **argv)
{
    //wsaData to hold Winsock dll information
    WSADATA wsaData;
    WORD wVersionRequired = MAKEWORD(2, 2);
    
    //Attempts to load winsock dll matching required version and fills WSADATA object
    int wsaInit = WSAStartup(wVersionRequired, &wsaData);
    if(wsaInit != 0)
    {
        printf("WSAStartup failed with error code: %d\n", wsaInit);
    }
    
    //If dll fails to load correct version free winsock dll resources
    if(wsaData.wHighVersion != wVersionRequired)
    {
        printf("No usable version of Winsock.dll found\n");
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Winsock dll 2.2 loaded correctly\n");
    }
    
    /**********************Socket Code Here**********************/
    
    
    /**********************Get address info*************/
    struct addrinfo *result = NULL;
    //*ptr is used to access each addrinfo struct returned in result as a linked list.
    struct addrinfo *ptr = NULL;
    //hints is a struct to hold basic information about which type of socket
    //the caller (in this case server) supports. Must set zero out unused members
    struct addrinfo hints;
    
    //Zero unused hints members to prevent error
    hints.ai_addrlen = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    
    // TODO(baruch): Currently only supporting IPv4, consider IPv6 later
    hints.ai_family = AF_INET;
    // This is a stream socket i.e. tcp/ip
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    //Specifies socket will be used in bind function 
    hints.ai_flags = AI_PASSIVE;
    
    //gives list of addresses based on port and type?
    int resultCode = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    
    if(resultCode != 0)
    {
        printf("getaddrinfo failed with error: %d\n", resultCode);
        WSACleanup();
        return 1;
    }
    /**************Got address info****************/
    
    //INVALID_SOCKET used like NULL
    SOCKET ListenSocket = INVALID_SOCKET;
    
    // TODO(baruch): Only supporting IP_V4
    // Socket for server to listen on for client connections
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    
    if(ListenSocket == INVALID_SOCKET)
    {
        printf("socket() error: %ld\n", WSAGetLastError());
        //clean up address info after getaddrinfo function when socket fails
        freeaddrinfo(result);
        WSACleanup();
    }
    
    /*************End Socket Code Clean up Winsock dll**********/
    
    WSACleanup();
} 
