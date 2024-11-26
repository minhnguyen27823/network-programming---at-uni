#include <ws2tcpip.h>
#include "winsock2.h"
#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
// g++ socket.cpp -o socket.exe  -lWs2_32
int main(){
   char* recvbuf = new char[512];
   int recvbuflen = 512;

   WSADATA wsaData;
   WORD wVersion = MAKEWORD(2,2);
   int iResult=WSAStartup(wVersion, &wsaData);

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

    iResult = connect(ListenSock, (SOCKADDR *) & name, sizeof (name));
    if (iResult == SOCKET_ERROR) {
        cout << L"connect function failed with error: %ld\n", WSAGetLastError();
        iResult = closesocket(ListenSock);
        if (iResult == SOCKET_ERROR)
           cout << L"closesocket function failed with error: %ld\n", WSAGetLastError();
        WSACleanup();
        return 1;
    }else
    {  
        iResult = recv(ListenSock, recvbuf, recvbuflen, 0);
        recvbuf[iResult] = '\0';
        cout <<  recvbuf << endl;
       
        do{
        char* temp= new char;
        cout << "nhap  :";

        cin.getline(temp, 100);
        const char *sendbuf = new char[100] ;
        sendbuf = temp;

        iResult = send( ListenSock, sendbuf, (int)strlen(sendbuf), 0 );
        iResult = recv(ListenSock, recvbuf, recvbuflen, 0);
        recvbuf[iResult] = '\0';
        cout << recvbuf << endl;
        }while(strcmp(recvbuf, "nhap mat khau") != 0);

        do{
        char* temp= new char;
        cout << "nhap  :";

        cin.getline(temp, 100);
        const char *sendbuf = new char[100] ;
        sendbuf = temp;

        iResult = send( ListenSock, sendbuf, (int)strlen(sendbuf), 0 );
        iResult = recv(ListenSock, recvbuf, recvbuflen, 0);
        recvbuf[iResult] = '\0';
        cout <<recvbuf << endl;
        }while(strcmp(recvbuf, "mat khau dung") != 0);
        
         cout << "nhap mat khau moi co chua ki tu dac biet " << endl;

          do{
        char* temp= new char;
        cout << "nhap  :";

        cin.getline(temp, 100);
        const char *sendbuf = new char[100] ;
        sendbuf = temp;

        iResult = send( ListenSock, sendbuf, (int)strlen(sendbuf), 0 );
        iResult = recv(ListenSock, recvbuf, recvbuflen, 0);
        recvbuf[iResult] = '\0';
        cout << recvbuf << endl;
        }while(strcmp(recvbuf, "mat khau hop le") != 0);
    }




while(TRUE){
    char* temp= new char;
    cout << "nhap thong tin can truyen :";

    cin.getline(temp, 100);
    const char *sendbuf = new char[100] ;
    sendbuf = temp;
    iResult = send( ListenSock, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSock);
        WSACleanup();
        return 1;
    }
    do {
    iResult = recv(ListenSock, recvbuf, recvbuflen, 0);
    if (iResult > 0){

        recvbuf[iResult] = '\0';
        cout << "server sent : " << recvbuf << endl;
        break;
    }
    else if (iResult == 0)
        printf("Connection closed\n");
    else
        printf("recv failed: %d\n", WSAGetLastError());
    } while (iResult > 0);
      const char* goodbye = "good bye";
      if(strcmp(recvbuf, goodbye)==0) break;

}


    iResult = shutdown(ListenSock, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSock);
        WSACleanup();
        return 1;
    }
   cout << "disconnect";
   closesocket(ListenSock);
   WSACleanup();

}