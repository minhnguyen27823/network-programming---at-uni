#include <iostream>
#include <string.h>
using namespace std;
int main(){
    string s;
    cin >> s;
    string temp ;
    temp = string(1,s[0]);
    int dem1=1;
    int dem2=0;
    int check =0 ;
    for(int i = 1 ; i < s.size() ;i++){
        int size = temp.size();
        cout << "temp size" << size << endl;
          for(int j = 0 ; j < size; j++){
            if(s[i] != temp[j]){
                  check++;
            }else{
                cout << "temp bi xoa " << temp << endl;
                if(temp.size() > dem2) dem2=temp.size();
                for(int temp_j = j ; j >=0;j --) temp.erase(temp_j, 1);
                temp=temp + string(1, s[i]);
                dem1=0;
                break;
            }
          }
          if(check == size ) temp = temp + string(1, s[i]);
          check=0;
    }
    if(temp.size() > dem2) dem2=temp.size();
    cout << dem2;
    } 
