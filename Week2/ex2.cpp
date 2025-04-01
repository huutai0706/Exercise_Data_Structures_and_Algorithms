#include <iostream>
#include <vector>
using namespace std;
// ham nhap gia tri mang
void scanf_arr(vector<int>& a){
    int x, n;
    cin >> n;
    for(int i = 0 ; i < n; i++){
        cin >> x;
        a.push_back(x);
    }
    return;
}
// ham in mang
void prinf_arr(vector<int> a){
    for(int i = 0 ; i < a.size(); i++){
        cout << a[i] <<" ";
    }
    return;
}
// ham tim kiem
int linear_search_with_sentinel(vector<int> a, int k){

    int n = a.size();
    //gan gia tri phan tu cuoi cho last
    int last = a[n-1]; 
    // gan gia tri k cho vi tri cuoi mang
    a[n-1] = k;
    int i = 0;
    // lap khi tim thay phan tu mang bang k thi dung lai va tang gia tri i len
    while(a[i] != k){
        i++;
    }
    // neu phan tu cuoi bang k hoac i nho hon n-1 thi in ra vi tri i 
    if(a[n-1] == k || i < n-1){
        return i;
    }
    // tra lai phan tu cuoi mang bang last
    a[n-1] = last;
    // neu khong tim thay in ra -1
    return -1;

}

int main(){
    int k;
    vector<int> a;
    scanf_arr(a);
    cin >> k;
    // gan index bang gia tri tra ve cua ham tim kiem
    int index = linear_search_with_sentinel(a, k);
    if(index != -1){ // neu index khac -1 thi in ra index con khong in ra -1 khong tim thay
        cout << index << endl;
    } else{
        cout << -1 << endl;
    }
    return 0;
}