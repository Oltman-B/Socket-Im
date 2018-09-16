/*****************************************************************************
 This is the client for my socket based console instant messanger application.
 
Baruch Oltman September 2018
     ****************************************************************************/
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

// TODO(baruch): Only supporting ascii consider Unicode later
#undef UNICODE

#define DEFAULT_PORT "5555"
#define DEFAULT_BUFLEN 512
#define SERVER_IPV4 "10.50.212.152"

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
    
    //gives list of addresses based on port and type?
    char serverIPv4[] = SERVER_IPV4;
    int resultCode = getaddrinfo(serverIPv4, DEFAULT_PORT, &hints, &result);
    
    if(resultCode != 0)
    {
        printf("getaddrinfo failed with error: %d\n", resultCode);
        WSACleanup();
        return 1;
    }
    /**************Create Socket****************/
    
    //INVALID_SOCKET used like NULL
    SOCKET ConnectSocket = INVALID_SOCKET;
    
    // TODO(baruch): Only supporting IP_V4
    // TODO(baruch): ptr checks first struct of linked list only, this may need to be changed for release.
    ptr = result;
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    
    if(ConnectSocket == INVALID_SOCKET)
    {
        printf("socket() error: %ld\n", WSAGetLastError());
        //clean up address info after getaddrinfo function when socket fails
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    
    /*****************Connect to socket**************/
    
    int connectResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if(connectResult == SOCKET_ERROR)
    {
        printf("Connect failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }
    else
    {
        printf("Connected with server: %s\n", serverIPv4);
    }
    
    // TODO(baruch):If connection fails move ptr to next address struct in linked list and try again. For testing, just trying first address.
    while(true);// TODO(baruch): Remove
    
    freeaddrinfo(result);
    
    if(ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect with server\n");
        WSACleanup();
        return 1;
    }
    
    /*************END of Socket CODE CLEANUP********/
    
    // TODO(baruch): close socket
    WSACleanup();
    
}
