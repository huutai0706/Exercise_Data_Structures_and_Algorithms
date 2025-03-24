#include <iostream>
#include <string>
using namespace std;
//Hàm in ra chuỗi bit có độ dài n;
void generateBinaryStrings(int n, string str){
    //Nếu chuỗi có độ dài n thì in ra chuỗi
    if(str.length() == n){
        cout << str << endl;
    } else{
        //Đệ quy thêm "0" và "1" vào cuối chuỗi
        generateBinaryStrings(n, str + "0");
        generateBinaryStrings(n, str + "1");
    }
}

int main(){
    int n; 
    //Nháp n;
    cin >> n;
    //Gọi hàm để in ra chuỗi;
    generateBinaryStrings(n, "");
    return 0;
}