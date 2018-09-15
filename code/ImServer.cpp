//This is the server for my socket based console instant messanger application.
//Baruch Oltman September 2018
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
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
    
    
    /*************End Socket Code Clean up Winsock dll**********/
    
    WSACleanup();
} 
