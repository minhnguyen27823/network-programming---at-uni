#include "winsock2.h"
#include "iostream"

using namespace std;

int main()
{
    WSADATA wsaData;
    WORD wVersion = MAKEWORD(2,2);
    int Stat;

    if ((Stat = WSAStartup(wVersion, &wsaData)) != 0)
    {
        cout << "Failed: " << Stat << endl;
        return 0;
    }
    else
    {
        cout << "Startup Winsock successfully...";
    }

    if (WSACleanup() == SOCKET_ERROR)
    {
        cout << "WSACleanup failed with error: " << WSAGetLastError() << endl;
    }
    return 0;
}