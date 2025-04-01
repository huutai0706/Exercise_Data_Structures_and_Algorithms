#include <iostream>
#include <vector>
using namespace std;

void scanf_arr(vector<int>& a){
    int x, n;
    cin >> n;
    for(int i = 0 ; i < n; i++){
        cin >> x;
        a.push_back(x);
    }
    return;
}

void prinf_arr(vector<int> a){
    for(int i = 0 ; i < a.size(); i++){
        cout << a[i] <<" ";
    }
    return;
}

int min_arr(vector<int> a){
    int l =0;
    int r = a.size()-1;
    while(l < r){
        int m = l + (r-l)/2;
        if(a[m] < a[r]){
            r = m;
        } else{
            l = m +1;
        }
    }
    return a[l];
}

int main(){
    vector<int> a;
    scanf_arr(a);
    cout << min_arr(a);
    return 0;
}