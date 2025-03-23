#include <iostream>
using namespace std;

void TowerOfHanoi(int n, char from_peg, char to_peg, char aux_peg) {
    if (n == 1) {
        cout << "Di chuyrn dia 1 tu " << from_peg << " den " << to_peg << endl;
        return;
    }
    TowerOfHanoi(n-1, from_peg, aux_peg, to_peg);
    cout << "Di chuyen dia " << n << " tu " << from_peg << " den " << to_peg << endl;
    TowerOfHanoi(n-1, aux_peg, to_peg, from_peg);
}
int main() {
    int n;
    cout << "Nhap so luong dia: ";
    cin >> n;
    TowerOfHanoi(n, 'A', 'C', 'B'); 
    return 0;
}
