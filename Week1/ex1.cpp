#include <iostream>
using namespace std;

// Hàm tính số fibonacci thứ n
int fibonacci(int n){
    if(n==0) return 0; //fibonacci(0) = 0;
    if(n==1) return 1; //fibonacci(1) = 1;
    //fibonacci(n) = fibonacci(n-1) + fibonacci(n-2);
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
    int n; 
    //Nhap n;
    cin >> n;
    //In ra so fibonaci thứ n;
    cout << fibonacci(n) << endl;
    return 0;
}
