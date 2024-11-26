#include <ws2tcpip.h>
#include "winsock2.h"
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
//g++ inet_pton.cpp -o inet_pton.exe  -lWs2_32
char* long_to_binary(unsigned long k)

{
        static char c[65];
        c[0] = '\0';

        unsigned long val;
        for (val = 1UL << (sizeof(unsigned long)*8-1); val > 0; val >>= 1) 
        {   
            strcat(c, ((k & val) == val) ? "1" : "0");
        }

           int i = 24;
            int j = 0;

            char* temp_result = new char[32 + 1]; 

           while(i>=0 & ( j>=0 & j<32))
        {
            for(int count=0;count < 8;count++)
            {
                temp_result[j]=c[i+count];
                j++;
            }
            i=i-8;
        }
        temp_result[j] = '\0'; 
        char *m = new char;
        m=temp_result;

    return m;
    }

int main()
{ 
    struct in_addr ipv4addr;
    const char *ipv4_str = "127.0.0.196";//MSSV:106210245
    inet_pton(AF_INET, ipv4_str, &ipv4addr);
    char* result = new char[32];
    result= long_to_binary(ipv4addr.s_addr);
    cout << "BINARY: " << result;
}