#include <ws2tcpip.h>
#include "winsock2.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
// g++ socket.cpp -o socket.exe  -lWs2_32

void removeDigitsAndSpecialChars(char* str) {
    int length = strlen(str);
    int j = 0;

    for (int i = 0; i < length; ++i) {
        if (isalpha(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; 
}
char* to_lower(char* s){
	for(int i = 0; i < (int)strlen(s); i++){
		if(s[i] >= 'A' && s[i] <= 'Z'){
			s[i] += 32;
		}
	}
	return s;
}

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

     char* recvbuf = new char;
     int recvbuflen = 512;     
     int recvResult ;

     do {

        recvResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        if (recvResult > 0) {
            recvbuf[recvResult] = '\0';
            cout << "server received:" << recvbuf << endl;
            removeDigitsAndSpecialChars(recvbuf);

        //If exit or quit
            const char* exit = "exit";
            const char* quit = "quit";
        char *temp =  to_lower(recvbuf);
        if(strcmp(temp, exit) == 0 || strcmp(temp, quit) == 0 ){
            const char* temp="good bye";
            int iSendResult = send( AcceptSocket, temp, (int)strlen(temp), 0 );
            break;
        }
        // buffer back 
        // else if (recvbuf[strlen(recvbuf)-1] == '\0'){
        //     const char* temp="nhap lai chuoi khac";
        //     int iSendResult = send( AcceptSocket, temp, (int)strlen(temp), 0 );
        //     break;
        // }
        else{
            int iSendResult = send( AcceptSocket, recvbuf, (int)strlen(recvbuf), 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(AcceptSocket);
                WSACleanup();
                return 1;
            }
        }
    }
        else if (recvResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(AcceptSocket);
            WSACleanup();
            return 1;
        }

    } while (recvResult > 0);
    recvResult = shutdown(AcceptSocket, SD_SEND);
    if (recvResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(AcceptSocket);
        WSACleanup();
        return 1;
    }
      closesocket(AcceptSocket);
      closesocket(ListenSock);
    cout << "disconnect";
     if (WSACleanup() == SOCKET_ERROR) {
          cout << "WSACleanup failed with error: " << WSAGetLastError() << endl;
     }

     return 0;

}