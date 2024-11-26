#include <iostream>
#include <fstream>

using namespace std;
int main(){
    ifstream read_file;
        char tk[100];
        char mk[100];
        read_file.open("D:/zip/C++/train_forexam/accout.txt");
        read_file.getline(tk, 100);
        read_file.getline(mk, 100);

        read_file.close();

cout << tk;
cout << mk;
}
