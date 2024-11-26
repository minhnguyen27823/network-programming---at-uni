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

   sockaddr_in name;
   name.sin_family = AF_INET;
   name.sin_port = htons(5000);
   name.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

  connect(ListenSock, (SOCKADDR *) & name, sizeof (name));

}