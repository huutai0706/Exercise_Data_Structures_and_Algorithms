#include <iostream>
using namespace std;

//Hàm tính n giai thừa
int factorial(int n){
    if(n == 0) return 1; //0! = 1;
    if(n == 1) return 1; //1! = 1;
    //Đệ quy n! = n*(n-1)!;
    return n*factorial(n-1);
}
int main(){
    int n; 
    //Nhập n;
    cin >> n;
    //In ra n giai thừa;
    cout << factorial(n) << endl;
    return 0;
}
