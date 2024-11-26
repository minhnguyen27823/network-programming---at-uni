#include <ws2tcpip.h>
#include "winsock2.h"
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
// g++ socket.cpp -o socket.exe  -lWs2_32

void splitString(const char* input, char* part2, char* part3) {
    char temp[100];  // Tạo bản sao của chuỗi input để không làm thay đổi chuỗi gốc
    strcpy(temp, input);

    // Bỏ qua phần đầu tiên "GetCrd"
    strtok(temp, "<>");  // Không lưu giá trị

    // Tách phần thứ hai
    char* token = strtok(NULL, "<>");
    strcpy(part2, token);

    // Tách phần thứ ba
    token = strtok(NULL, "<>");
    strcpy(part3, token);
}
struct SV{
unsigned long msv;
   string matkhau;
   string hovaten;
   string ngaythangnamsinh;
   int tinchi;
};
int main(int argc, char **argv){
    
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
          SV sinhvien;
        ifstream test;
        test.open("D:/zip/C++/giuaki/SV.txt");
        if (!test.is_open()) {
                cout << "Không thể mở file." << endl;
                return 1;
            }

            test >> sinhvien.msv;
            test >> sinhvien.matkhau;
            test.ignore();  // Bỏ qua ký tự xuống dòng sau khi đọc chuỗi
            getline(test, sinhvien.hovaten);
            getline(test, sinhvien.ngaythangnamsinh);
            test >> sinhvien.tinchi;

          test.close();

        
        recvResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        if (recvResult > 0) {
            recvbuf[recvResult] = '\0';
            cout << "server received:" << recvbuf << endl;
            
            
           char *msv = new char[100];
           char *mk =new char [100];      
           string newmk=mk; 
          splitString(recvbuf, msv, mk);
          char *endptr;
          unsigned long num = strtoul(msv, &endptr, 10);
          if(num == sinhvien.msv){
            cout << "dung roi";
            if(newmk == sinhvien.matkhau) cout << "dang nhap thanh cong ";
          };
           
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