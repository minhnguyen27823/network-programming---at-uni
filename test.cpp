#include <iostream>
#include <math.h>
using namespace std;
int reverse(int x) {
        long long results = x%10;
        cout << results << endl;
        x = x/10;
        int temp;
        int dk;
        while(x != 0){
            temp=x % 10;
            results = 10*results+temp;
            cout << results << endl;
            x=x/10;
        }
        if(results > (pow(2,31)-1) || results < (-pow(2,31))) return 0;
        cout << "resutl trc return" << results << endl;
        return results;
    }
int main(){
    int x = 1534236469;
    int re = reverse(x);
    cout << re;
}