#include <iostream>
using namespace std;
//Hàm giải Tháp Hà Nội
void Tower_Of_Hanoi(int n, char cot_dau, char cot_giua, char cot_dich) {
    //Nếu chỉ còn 1 dĩa ở cột đầu di chuyển nó từ cột đầu đến cột giữa
    if (n == 1) {
        cout << "Di chuyen dia 1 tu " << cot_dau << " den " << cot_giua << endl;
        return; //Kết thúc khi còn 1 dĩa.
    }
    //Di chuyển n-1 dĩa từ cột đầu sang cột giữa, dùng cột đích làm cột trung gian
    Tower_Of_Hanoi(n-1, cot_dau, cot_dich, cot_giua);
    //Di chuyển đĩa lớn nhất từ cột đầu sang cột đích
    cout << "Di chuyen dia " << n << " tu " << cot_dau << " den " << cot_dich << endl;
    // Di chuyển n-1 đĩa từ cột giữa sang cột đích cột đầu làm trung gian
    Tower_Of_Hanoi(n-1, cot_dich, cot_giua, cot_dau);
}
int main() {
    int n;
    //Nhap n;
    cin >> n;
    //Gọi hàm Tower_Of_Hanoi 
    //Cot A côt đầu B giữa C cuối
    Tower_Of_Hanoi(n, 'A', 'C', 'B'); 
    return 0;
}
