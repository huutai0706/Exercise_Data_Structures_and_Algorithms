#include <iostream>
#include <algorithm>
using namespace std;

void scanf_arr(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

void kiemtra(int a[], int n) {
    sort(a, a + n); // yeu cau mang phai duoc sap xep

    for (int i = 0; i < n - 2; i++) {
        int l = i + 1, r = n - 1; 

        while (l < r) {
            int sum = a[i] + a[l] + a[r];  

            if (sum == 0) {  // neu tong bang 0 in ra cac gia tri cua mang
                cout << a[i] << " " << a[l] << " " << a[r] << endl;
                l++;  // dich l qua phai (tang gia tri cua a[l]) 
                r--;  // dich r qua trai giam gia tri cua a[r]
            } else if (sum > 0) {
                r--;  // neu tong sum lon thi gia r xuong
            } else {
                l++;  // neu tong sum nho tang gia tri l len
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    scanf_arr(a, n);
    kiemtra(a, n);
    delete[] a;
    return 0;
}
