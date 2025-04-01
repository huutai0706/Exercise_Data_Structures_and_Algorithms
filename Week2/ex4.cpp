#include <iostream>
#include <vector>
using namespace std;

bool ship(vector<int> weights, int days, int capacity){
    int dayCount = 1;
    int sumWeight = 0;
    for(int i = 0; i < weights.size(); i++){
        if(sumWeight + weights[i] > capacity){
            dayCount++;
            sumWeight = weights[i];
            if(dayCount > days){
                return false;
            }
        } else{
            sumWeight += weights[i];
        }
    }
    return true;
}

int maxWeightss(vector<int> weights){
    int n = weights.size();
    int max = weights[0];
    for(int i = 0 ; i < n ; i++){
        if(weights[i] > max){
            max = weights[i];
        }
    }
    return max;
}

int shipdays(vector<int> weights, int days){
    int maxWeights = 0;
    int totalWeights = 0;
    for(int i = 0 ; i < weights.size(); i++){
        totalWeights += weights[i];
        maxWeights = maxWeightss(weights);
    }
    for(int i = maxWeights; i <= totalWeights ; i++){
        if(ship(weights, days, i)){
            return i;
        }
    }
    return totalWeights;
}

int main() {
    int n;
    cin >> n;  // Nhập số lượng gói hàng
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];  // Nhập trọng lượng của các gói hàng
    }
    int days;
    cin >> days;  // Nhập số ngày cho phép

    // In ra dung lượng tàu tối thiểu để vận chuyển trong số ngày cho phép
    cout << shipdays(weights, days) << endl;
    return 0;
}