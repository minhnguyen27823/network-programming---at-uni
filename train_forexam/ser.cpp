#include <ws2tcpip.h>
#include "winsock2.h"
#include <iostream>
#include <cctype>
#include <cstring>
#include <ctype.h>
#include <fstream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
// g++ socket.cpp -o socket.exe  -lWs2_32

struct Account{
    SOCKET a;
    char *tk=new char[100];
    char *mk=new char[100];
};

unsigned __stdcall MyThread(void* data) {
    Account* server = (Account*)data;
    cout << "Thread is running!" << endl;
    cout << server->tk << endl;
    cout << server->mk << endl;
    return 0;
}


unsigned __stdcall checkaccount(void* data) {
    cout << "Thread is running!" << endl;
    return 0;
}


char* to_upper(char* s){
	
	if(s[0]<=122 && s[0] >= 97) s[0]=toupper(s[0]);
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

   unsigned long ul=1;

   if(ioctlsocket(ListenSock, FIONBIO, (unsigned long*)&ul)){
        cout << "Error" << endl;
        return 0;
   }
  
     SOCKET AcceptSocket_max[5];
     int numClient=0;
     wprintf(L"Waiting for client to connect...\n");
    Account server;
    
    ifstream read_file;
    read_file.open("D:/zip/C++/train_forexam/accout.txt");
    if(!read_file){
        cout << "error at read file" << endl;
    }else{
         read_file.getline(server.tk, 100);
         read_file.getline(server.mk, 100);
         cout << "tai khoan " << server.tk << endl;
         cout << "mat khau " << server.mk << endl;
    }
    
    read_file.close();

            unsigned threadID;
            HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, MyThread, &server, 0, &threadID);
            if (hThread != 0) {
                cout << "Thread created successfull "  << endl;
                WaitForSingleObject(hThread, INFINITE);  
                cout << "Thread complete" << endl;
                CloseHandle(hThread);  
            } else {
                cout << "Failed to create thread!" << endl;
            }

            
    while(1){
     sockaddr_in clientAddr;
    int clientAddrlen = sizeof(clientAddr);
    SOCKET AcceptSocket;
    AcceptSocket = accept(ListenSock, (sockaddr *) &clientAddr, &clientAddrlen);
    if (AcceptSocket != INVALID_SOCKET) {        
        AcceptSocket_max[numClient]= AcceptSocket;
        numClient++;
        cout << "client " << numClient << " connected" << endl;
    } 
        
    
     
     for(int i=0;i<numClient;i++){
        // unsigned threadID;
        // HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, MyThread, NULL, 0, &threadID);
        char* recvbuf = new char;
        int recvbuflen = 512;     
        int recvResult=recv(AcceptSocket_max[i], recvbuf, recvbuflen, 0); ;
     
       if(recvResult == SOCKET_ERROR){
           if(WSAGetLastError() != WSAEWOULDBLOCK) closesocket(AcceptSocket_max[i]);
       }
        else {
            recvbuf[recvResult] = '\0';
            cout << "server received:" << recvbuf << endl;
            // if(strcmp(recvbuf, "thread") == 0){
            //         unsigned threadID;
            //         HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, MyThread, &server, 0, &threadID);
            //         if (hThread != 0) {
            //             cout << "Thread created successfull "  << endl;
            //             WaitForSingleObject(hThread, INFINITE);  
            //             cout << "Thread complete" << endl;
            //             CloseHandle(hThread);  
            //         } else {
            //             cout << "Failed to create thread!" << endl;
            //         }
            // }
            recvbuf=to_upper(recvbuf);
       
            int iSendResult = send( AcceptSocket_max[i], recvbuf, (int)strlen(recvbuf), 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(AcceptSocket_max[i]);
                WSACleanup();
                return 1;
        }
    }
    }
    }
    cout << "disconnect";
     if (WSACleanup() == SOCKET_ERROR) {
          cout << "WSACleanup failed with error: " << WSAGetLastError() << endl;
     }

     return 0;

}