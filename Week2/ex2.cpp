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

int linear_search_with_sentinel(vector<int> a, int k){
    int n = a.size();
    int last = a[n-1]; a[n-1] = k;
    // tim vi tri key;
    int i = 0;
    while(a[i] != k){
        i++;
    }

    if(a[n-1] == k || i < n-1){
        return i;
    }

    a[n-1] = last;

    return -1;

}

int main(){
    int k;
    vector<int> a;
    scanf_arr(a);
    cin >> k;
    int index = linear_search_with_sentinel(a, k);
    if(index != -1){
        cout << index << endl;
    } else{
        cout << -1 << endl;
    }
    return 0;
}