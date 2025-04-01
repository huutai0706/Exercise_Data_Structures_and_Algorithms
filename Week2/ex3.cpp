#include <iostream>
#include <vector>
using namespace std;
// ham nhap gia tri cho mang
void scanf_arr(vector<int>& a){
    int x, n;
    cin >> n;
    for(int i = 0 ; i < n; i++){
        cin >> x;
        a.push_back(x);
    }
    return;
}
// ham in ra gia tri trong mang
void prinf_arr(vector<int> a){
    for(int i = 0 ; i < a.size(); i++){
        cout << a[i] <<" ";
    }
    return;
}
// ham tim min cua mang vong
int min_arr(vector<int> a){
    // gan left = 0;
    int l = 0;
    int r = a.size()-1; // gan right = n-1
    while(l < r){ // neu left lon hon hoac bang right thi dung lai
        int m = l + (r-l)/2; // khoi tao gia tri cua mid
        if(a[m] < a[r]){ // neu a[mid] < a[right] thi right = mid
            r = m;
        } else{ // nguoc lai neu a[mid] > a[right] thi left = mid + 1
            l = m +1;
        }
    }
    return a[l];
}

int main(){
    vector<int> a;
    scanf_arr(a);
    // in rs gia tri min trong mang
    cout << min_arr(a);
    return 0;
}