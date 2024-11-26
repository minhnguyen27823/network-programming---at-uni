#include <ws2tcpip.h>
#include "winsock2.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
// g++ socket.cpp -o socket.exe  -lWs2_32
int main(int argc, char **argv){


   WSADATA wsaData;
   WORD wVersion = MAKEWORD(2,2);
   int iResult=WSAStartup(wVersion, &wsaData);

   SOCKET UDPsock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   
   if(UDPsock != INVALID_SOCKET){

        cout << "Creating socket completed successfully" << endl;
   }
   else{
    cout << "Creating socket failed with code " << WSAGetLastError() << endl;
   }


   sockaddr_in name;
   name.sin_family = AF_INET;
   int port=atoi(argv[2]);
   name.sin_port = htons(port);
   name.sin_addr.s_addr = inet_addr(argv[1]);


char* temp= new char[1024];
cout << "Thong tin can truyen :" << argv[3] << endl;

// cin.getline(temp, 1024);


iResult = sendto(UDPsock, argv[3], strlen(argv[3]), 0, (SOCKADDR *) & name, sizeof (name));
if (iResult == SOCKET_ERROR) {
    wprintf(L"send failed with error: %d\n", WSAGetLastError());
    closesocket(UDPsock);
    WSACleanup();
    return 1;
}
   char RecvBuf[1024];
   int BufLen = 1024;
   struct sockaddr_in SenderAddr;
   int SenderAddrSize = sizeof (SenderAddr);

   iResult = recvfrom(UDPsock, RecvBuf, BufLen, 0, (SOCKADDR*)&SenderAddr, &SenderAddrSize);
    if (iResult == SOCKET_ERROR) {
        cout << "recvfrom failed with error: " << WSAGetLastError() << endl;
    } else {
        RecvBuf[iResult] = '\0'; // Đảm bảo chuỗi kết thúc
        cout << "Thong tin nhan dc: " << RecvBuf << endl;
    }


    iResult = shutdown(UDPsock, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(UDPsock);
        WSACleanup();
        return 1;
    }
   cout << "disconnect";
   closesocket(UDPsock);
   WSACleanup();
}