#include <ws2tcpip.h>
#include "winsock2.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main(){

   WSADATA wsaData;
   WORD wVersion = MAKEWORD(2,2);
   WSAStartup(wVersion, &wsaData);

   SOCKET ListenSock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
   
   if(ListenSock != INVALID_SOCKET){

        cout << "Creating socket completed successfully" << endl;
   }
   else{
    cout << "Creating socket failed with code " << WSAGetLastError() << endl;
   }

   sockaddr_in name;
   name.sin_family = AF_INET;
   name.sin_port = htons(5000);
   name.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


    if(!bind (ListenSock, (sockaddr*) &name, sizeof (name)))
   {
        cout << "Bind API completed sucessfully." << endl;
   }
   else{
        cout << "Bind API failed with code: " << WSAGetLastError() << endl;
   }
   

    if (!listen(ListenSock, 5) ){
        cout << "Sucessfully!!! Server is listening the requests..." << endl;
   }else 
    {
        cout << "Listen failed with code: " << WSAGetLastError() << endl;
    }
    

     SOCKET AcceptSocket;
     wprintf(L"Waiting for client to connect...\n");


    AcceptSocket = accept(ListenSock, NULL, NULL);
    if (AcceptSocket == INVALID_SOCKET) {
        wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSock);
        WSACleanup();
        return 1;
    } else
        wprintf(L"Client connected.\n");

}