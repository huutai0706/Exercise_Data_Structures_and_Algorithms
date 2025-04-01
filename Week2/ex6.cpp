#include <iostream>
using namespace std;

void scanf_arr(int a[], int n){

    for(int i = 0 ; i < n; i++){
        cin >> a[i];
    }
    return;
}
// ham kiem tra tong hai phan tu trong mang co bang k khong
bool kiemtra(int a[], int n, int k){
    int l = 0, r = n - 1;
    // neu l < r thi ket thuc lap tra ve gia tri false
    while (l < r) {
        // tinh tong vi tri dau va cuoi
        int sum = a[l] + a[r];  
        // neu tong bang k thi dang lap va tra ve true
        if (sum == k) {
            return true;  
        } else if (sum > k) { // neu sum > k thi giam gia tri sum xuong bang cach giam vi tri xuong
            r--;  
        } else {
            // neu sum < k tang gia tri sum len bang tang l len de co gia tri lon hon
            l++; 
        }
    }
    // neu khi vong lap ket thuc thi tra ve gia tri false
    return false;
}

int main(){
    int n; cin >> n;
    int* a = new int[n];
    scanf_arr(a, n);
    int k; cin >> k;
    // neu ham kiemtra tra va gia tri true thi in ra YES con khong thif in ra NO
    if(kiemtra(a, n, k)){
        cout <<"YES" << endl;
    } else  cout <<"NO";
    delete[] a;
    return 0;
}