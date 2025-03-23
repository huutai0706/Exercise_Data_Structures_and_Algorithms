
#include <iostream>
using namespace std;

int factorial(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    return n*(n-1);
}

int main(){
    int n;
    cin >> n;
    cout << factorial(n) << endl;
    return 0;
}