#include <iostream>
using namespace std;

int minLengthArr(int target, int a[], int n) {
    int minLength = n + 1;  // gia tri ban dau n+1
    int sum = 0;  // tong day con hien tai
    int start = 0;  // con tro dau
    for (int i = 0; i < n; i++) {
        sum += a[i];  // tong gia tri toi vi tri i       
        // neu tong lon thi di chuyen start
        while (sum >= target) {
            minLength = min(minLength, i - start + 1);  // do dai nho nhat // quan trong
            sum -= a[start];  // loai tru gia tri tai start
            start++;  // chuyen start sang phai
        }
    }
    // neu khong tim day day con thoa tra ve 0 
    return (minLength == n + 1) ? 0 : minLength; // toan tu 3 ngoi
}

int main() {
    int n, target;
    cin >> n >> target;  
    int* a = new int[n];

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << minLengthArr(target, a, n) << endl;
    delete[] a;
    return 0;
}
