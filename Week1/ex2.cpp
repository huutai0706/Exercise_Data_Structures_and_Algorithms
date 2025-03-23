#include <iostream>
using namespace std;

// ham tinh giai thua
int factorial(int n){
    if(n == 0) return 1;
    if(n == 1) return 1;
    return n*factorial(n-1);
}
int main(){
    int n; cin >> n;
    cout << factorial(n) << endl;
    return 0;
}
