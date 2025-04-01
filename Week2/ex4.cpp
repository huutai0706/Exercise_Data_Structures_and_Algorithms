#include <iostream>
#include <vector>
using namespace std;

// ham kiem tra cos the van chuyen trong day ngay khong
bool ship(vector<int> weights, int days, int capacity) {
    int dayCount = 1;  // ngay hien tai
    int sumWeight = 0; // tong trong luong cua ngay hien tai

    for (int i = 0; i < weights.size(); i++) {
        // neu trong luong vuot chi tieu thi qua ngay moi de chat
        if (sumWeight + weights[i] > capacity) {
            dayCount++;    // tang ngay len
            sumWeight = weights[i]; // dua trong luong qua ngay moi
            // neu trong luong vuot qua thi tra ve gia tri false
            if (dayCount > days) {
                return false;
            }
        } else {
            sumWeight += weights[i]; // tong trong luong ngay hien tai
        }
    }
    return true; // neu trong luong du cho phep tra ve false;
}

// ham tim trong luong can thiet cua mot ngay
int maxWeightss(vector<int> weights) {
    int n = weights.size();
    int max = weights[0];// gia su max trong luong la cua phan tu thu nhat

   // ham duyet de tim trong lunog lon nhat
    for (int i = 0; i < n; i++) {
        if (weights[i] > max) {
            max = weights[i]; // gan gia tri max trong luong cho phan tu lon nhat
        }
    }
    return max;
}

// ham tim trong luong nho nhat van chuyen mot ngay
int shipdays(vector<int> weights, int days) {
    int maxWeights = 0;   // trong luong lon nhat cua hang
    int totalWeights = 0; // tong trong luong cua goi hang

    // tinh tong trong luong va tim max trong luong
    for (int i = 0; i < weights.size(); i++) {
        totalWeights += weights[i]; 
        maxWeights = maxWeightss(weights); 
    }

    // duyet ke kiem trong luong toi thieu
    for (int i = maxWeights; i <= totalWeights; i++) {
        if (ship(weights, days, i)) { 
            return i;
        }
    }
    return totalWeights; // tra ve tong trong luong toi thieu
}

int main() {
    int n;
    cin >> n;  
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    int days;
    cin >> days;  
    // in ra trong luong toi thieu de van chuyen trong day ngay
    cout << shipdays(weights, days) << endl;
    return 0;
}
