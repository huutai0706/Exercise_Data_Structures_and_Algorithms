#include <iostream>
using namespace std;

void Tower_Of_Hanoi(int n, char cot_dau, char cot_giua, char cot_dich) {
    if (n == 1) {
        cout << "Di chuyen dia 1 tu " << cot_dau << " den " << cot_giua << endl;
        return;
    }
    Tower_Of_Hanoi(n-1, cot_dau, cot_dich, cot_giua);
    cout << "Di chuyen dia " << n << " tu " << cot_dau << " den " << cot_giua << endl;
    Tower_Of_Hanoi(n-1, cot_dich, cot_giua, cot_dau);
}
int main() {
    int n;
    cout << "Nhap so luong dia: ";
    cin >> n;
    Tower_Of_Hanoi(n, 'A', 'C', 'B'); 
    return 0;
}
