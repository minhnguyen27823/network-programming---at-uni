#include <winsock2.h>
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

bool containsSpecialChar(const char* str) {
    while (*str) {
        if (!isalnum(*str)) { // Nếu ký tự không phải là chữ cái hoặc số
            return true; // Ký tự đặc biệt được phát hiện
        }
        str++; // Di chuyển sang ký tự tiếp theo
    }
    return false; // Không có ký tự đặc biệt nào
}



int main(){
     char* recvbuf = new char;
        int recvbuflen = 512;     
        int recvResult ;
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
    cout << "listening client connect ......" << endl;

    AcceptSocket = accept(ListenSock, NULL, NULL);
    ////////////////////nhap mat khau tai khoan
    if (AcceptSocket == INVALID_SOCKET) {
        wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSock);
        WSACleanup();
        return 1;
    } else
    {   
        ifstream read_file;
        char tk[100];
        char mk[100];
        read_file.open("D:/zip/C++/train_forexam/accout.txt");
        read_file.getline(tk, 100);
        read_file.getline(mk, 100);

        read_file.close();

        cout << "client connected " << endl;
        const char* temp="nhap tai khoan";
        int iSendResult = send( AcceptSocket, temp, (int)strlen(temp), 0 );
        recvResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        recvbuf[recvResult] = '\0';
        int count_tk=0;
        int count_mk=0;
        while(strcmp(recvbuf, tk) != 0){
            temp ="khong ton tai tai khoan nay";
            iSendResult = send( AcceptSocket, temp, (int)strlen(temp), 0 );
            count_tk++;
            recvResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
            recvbuf[recvResult] = '\0';
        }
        temp ="nhap mat khau";
        iSendResult = send( AcceptSocket, temp, (int)strlen(temp), 0 );
        recvResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        recvbuf[recvResult] = '\0';


        while(strcmp(recvbuf, mk) != 0){
            temp ="sai mat khau";
            iSendResult = send( AcceptSocket, temp, (int)strlen(temp), 0 );
            recvResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
            recvbuf[recvResult] = '\0';
        }
        
        temp ="mat khau dung";
        iSendResult = send( AcceptSocket, temp, (int)strlen(temp), 0 );
        recvResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        recvbuf[recvResult] = '\0';
        
        while(!containsSpecialChar(recvbuf))
        {
            temp ="mat khau khong hop le";
            iSendResult = send( AcceptSocket, temp, (int)strlen(temp), 0 );
            recvResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
            recvbuf[recvResult] = '\0';

        }
   
        temp ="mat khau hop le";
        iSendResult = send( AcceptSocket, temp, (int)strlen(temp), 0 );

    }
        


        //////////////////////////////////
do {

        recvResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        if (recvResult > 0) {
            recvbuf[recvResult] = '\0';
            cout << "server received:" << recvbuf << endl;

        //If exit or quit
            const char* exit = "exit";
            const char* quit = "quit";
        char *temp =  recvbuf;
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




