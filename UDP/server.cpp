#include <ws2tcpip.h>
#include "winsock2.h"
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
// g++ socket.cpp -o socket.exe  -lWs2_32

int main(int argc, char **argv){

   WSADATA wsaData;
   WORD wVersion = MAKEWORD(2,2);
   WSAStartup(wVersion, &wsaData);

   SOCKET UDPsock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);


   sockaddr_in name;
   name.sin_family = AF_INET;
   int port=atoi(argv[1]);
   name.sin_port = htons(port);
   name.sin_addr.s_addr = INADDR_ANY;

   if(!bind (UDPsock, (sockaddr*) &name, sizeof (name)))
   {
        cout << "Bind API completed sucessfully." << endl;
   }
   else{
        cout << "Bind API failed with code: " << WSAGetLastError() << endl;
   }
   cout << "Waiting ............." << endl;


   char RecvBuf[1024];
   int BufLen = 1024;
   struct sockaddr_in SenderAddr;
   int SenderAddrSize = sizeof (SenderAddr);
   int i=0;
   i=recvfrom(UDPsock, RecvBuf, BufLen, 0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);
    if (i == SOCKET_ERROR) {
        wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
    }

    RecvBuf[i] = '\0';
    cout << "thong tin nhan dc: " << RecvBuf << endl;
    
    hostent *remoteHost= gethostbyname(RecvBuf);
    struct in_addr **addr_list;

    addr_list = (struct in_addr **)remoteHost->h_addr_list;    
    char *IP = new char[16];
    IP=inet_ntoa(*addr_list[0]);
    cout << "Phan giai ten mien sang IP: " << IP << endl;

    i=sendto(UDPsock, IP, strlen(IP), 0, (SOCKADDR *)&SenderAddr, sizeof(SenderAddr));
    if (i == SOCKET_ERROR) {
    wprintf(L"send failed with error: %d\n", WSAGetLastError());
    closesocket(UDPsock);
    WSACleanup();
    return 1;
}
else{
     cout << "IP sent back" << endl;
}

  closesocket(UDPsock);
  cout << "disconnect" << endl;
  if (WSACleanup() == SOCKET_ERROR) {
          cout << "WSACleanup failed with error: " << WSAGetLastError() << endl;
     }

     return 0;

}