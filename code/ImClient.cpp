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

#define DEFAULT_PORT 5555
#define DEFAULT_BUFLEN 512
#define SERVER_IPV4 "199.184.143.92"


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
    //convert ip string to binary format for use in SOCKADDR_IN struct.
    int iP4;
    inet_pton(AF_INET, SERVER_IPV4, &iP4);
    
    SOCKADDR_IN SockAddrIP4;
    SockAddrIP4.sin_family = AF_INET;
    SockAddrIP4.sin_addr.s_addr = iP4;
    SockAddrIP4.sin_port = htons(DEFAULT_PORT);
    
    /**************Create Socket****************/
    
    //INVALID_SOCKET used like NULL
    SOCKET ConnectSocket = INVALID_SOCKET;
    
    // TODO(baruch): Only supporting IP_V4
    // TODO(baruch): ptr checks first struct of linked list only, this may need to be changed for release.
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(ConnectSocket == INVALID_SOCKET)
    {
        printf("socket() error: %ld\n", WSAGetLastError());
        //clean up address info after getaddrinfo function when socket fails
        WSACleanup();
        return 1;
    }
    
    /*****************Connect to socket**************/
    
    int connectResult = connect(ConnectSocket, (SOCKADDR*)&SockAddrIP4, sizeof(SOCKADDR_IN));
    if(connectResult == SOCKET_ERROR)
    {
        printf("Connect failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }
    else
    {
        printf("Connected with server: %s\n", SERVER_IPV4);
    }
    
    // TODO(baruch):If connection fails move ptr to next address struct in linked list and try again. For testing, just trying first address.
    
    
    if(ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect with server\n");
        WSACleanup();
        return 1;
    }
    
    while(true);// TODO(baruch): Remove
    /*************END of Socket CODE CLEANUP********/
    
    // TODO(baruch): close socket
    WSACleanup();
    
}
