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

int linear_search(vector<int> a, int n, int k){
    if(n <= 0) {
        return -1;
    }
    if(a[n-1] == k){
        return n-1;
    } 
    return linear_search(a, n-1, k);
}

int main(){
    vector<int> a;
    scanf_arr(a);
    int k; cin >> k;
    int index = linear_search(a, a.size(), k);
    if(index != -1){
        cout << index << endl;
    } else{
        cout << -1 << endl;
    }
    return 0;
}