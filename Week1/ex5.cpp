#include <iostream>
using namespace std;

bool check_sort_Increasing(int a[], int n) {
    if (n == 1) return true; 
    if (a[n-1] < a[n-2]) return false;  
    return check_sort_Increasing(a, n-1);  
}

bool check_sort_Descending(int a[], int n){
    if (n == 1) return true; 
    if (a[n-1] > a[n-2]) return false;  
    return check_sort_Descending(a, n-1); 
}

void scanf_arr(int a[], int n){
    for(int i = 0 ; i < n ; i++){
        cin >> *(a+i);
    }
    return;
}

int main() {
    int n; cin >> n;
    int* a = new int[n];
    scanf_arr(a, n);
    if(a[n-1] >= a[0]){
        if (check_sort_Increasing(a, n)) {
            cout << "Array is sorted in increasing order" << endl; 
        } else {
            cout << "Array is not sorted in increasing order" << endl;  
        }
    }else{
        if (check_sort_Descending(a, n)) {
            cout << "Array is sorted in decreasing order" << endl; 
        } else {
            cout << "Array is not sorted in decreasing order" << endl;  
        }
    }
    delete[] a;
    return 0;
}
