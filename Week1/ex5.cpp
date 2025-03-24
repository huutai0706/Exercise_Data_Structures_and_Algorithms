#include <iostream>
using namespace std;
//Hàm kiểm tra mảng sắp xếp tăng dần hay không
bool check_sort_Increasing(int a[], int n) {
    // Nếu chỉ có một phần tử mảng luôn được sắp xếp
    if (n == 1) return true; 
    //Kiểm tra nếu phần tử hiện tại nhỏ hơn phần tử trước đó thì mảng tăng 
    if (a[n-1] < a[n-2]) return false;  
    //Đệ quy kiểm tra phần còn lại của ,ảng
    return check_sort_Increasing(a, n-1);  
}
//Hàm kiểm tra mảng sắp xếp giảm dần hay không
bool check_sort_Descending(int a[], int n){
    //Nếu chỉ có một phần tử mảng luôn được sắp xếp
    if (n == 1) return true; 
    //Nếu phần tử hiện tại lớn hơn phần tử trước nó thì mảng giảm
    if (a[n-1] > a[n-2]) return false;  
    //Đệ quy kiểm tra phần còn lại của mảng
    return check_sort_Descending(a, n-1); 
}
//Hàm nhập vào mảng
void scanf_arr(int a[], int n){
    //Duyệt qua các phần tử của mảng
    for(int i = 0 ; i < n ; i++){
        cin >> *(a+i); //Nhập từng giá trị cho từng phần tử
    }
    return;
}

int main() {
    int n; 
    cin >> n; //Nhập n;
    int* a = new int[n];
    //Gọi hàm nhập
    scanf_arr(a, n);
    //Kiểm tra phần tử đầu và cuối để xem tính chất mảng
    if(a[n-1] >= a[0]){
        //Nếu phần tử cuối lớn hơn hoặc bằng phần tử đầu kiểm tra tăng dần
        if (check_sort_Increasing(a, n)) {
            cout << "Array is sorted in increasing order" << endl; 
        } else {
            cout << "Array is not sorted in increasing order" << endl;  
        }
    }else{
        // Nếu phần tử cuối nhỏ hơn phần tử đầu, kiểm tra thứ tự giảm dần
        if (check_sort_Descending(a, n)) {
            cout << "Array is sorted in decreasing order" << endl; 
        } else {
            cout << "Array is not sorted in decreasing order" << endl;  
        }
    }
    //Giair phóng bộ nhớ
    delete[] a;
    return 0;
}
