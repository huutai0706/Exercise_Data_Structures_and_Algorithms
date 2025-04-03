#pragma
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*---------------------------------------------------------------------*/

//Thuật toán bubble sort
void bubble_sort(vector<int>& a) {
    long long count = 0;
    int n = a.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) { 
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) { 
            count++;
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    cout << "\nSo phep so sanh cua bubble sort: " << count << " lan\n";
}


/*---------------------------------------------------------------------*/

//Thuật toán selection sort
void selection_sort(vector<int>& a) {
    int n = a.size();
    long long count = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            count++;
            if (a[j] < a[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(a[i], a[min]);
        }
    }
    cout << "\nSo phep so sanh cua selection sort: " << count << " lan\n";
}


/*---------------------------------------------------------------------*/

//Thuật toán shell sort
void shell_sort(vector<int>& a) {
    int n = a.size();
    long long count = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > temp) {
                count++; 
                a[j] = a[j - gap];
                j -= gap;
            }
            count++; // Đếm so sánh cuối cùng khi vòng lặp dừng lại
            a[j] = temp;
        }
    }
    cout << "\nSo phep so sanh cua shell sort: " << count << " lan\n";
}



/*---------------------------------------------------------------------*/


//Thuật toán counting sort
void counting_sort(vector<int>& a) {
    if (a.empty()) return;
    long long count_S = 0;

    int max_a = *max_element(a.begin(), a.end());
    vector<int> count(max_a + 1, 0);

    for (int num : a) {
        count[num]++;
    }

    int index = 0;
    for (int i = 0; i <= max_a; i++) {
        while (count[i] > 0) {
            count_S++;
            a[index++] = i;
            count[i]--;
        }
    }
    cout << "\nSo lan thuc hien phep so sanh cua counting sort: " << count_S << " lan\n";
}


/*---------------------------------------------------------------------*/

int count_merge = 0;

void merge(vector<int>& a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> l(n1), r(n2);
    
    for (int i = 0; i < n1; i++) l[i] = a[left + i];
    for (int i = 0; i < n2; i++) r[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        count_merge++;
        if (l[i] <= r[j]) {
            a[k] = l[i++];
        } else {
            a[k] = r[j++];
        }
        k++;
    }

    while (i < n1) a[k++] = l[i++];
    while (j < n2) a[k++] = r[j++];
}

void merge_sort(vector<int>& a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

void print_merge_comparisons() {
    cout << "\nSo lan thuc hien phep so sanh cua merge sort: " << count_merge << " lan\n";
}





/*---------------------------------------------------------------------*/

//Thuật toán flash sort
void flash_sort(vector<int>& a){
    int n = a.size();
    if (n <= 1) return;

    // 1️⃣ Tìm giá trị min và max
    int min_value = a[0], max_index = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < min_value) min_value = a[i];
        if (a[i] > a[max_index]) max_index = i;
    }
    if (a[max_index] == min_value) return; // Nếu tất cả phần tử giống nhau

    // 2️⃣ Chia mảng thành nhóm (Lớp)
    int m = int(0.45 * n);  // Số nhóm tối ưu (thường bằng 45% số phần tử)
    vector<int> L(m, 0);
    double scale = (double)(m - 1) / (a[max_index] - min_value);

    // 3️⃣ Xác định số phần tử trong mỗi nhóm
    for (int i = 0; i < n; i++) {
        int index = scale * (a[i] - min_value);
        L[index]++;
    }

    // 4️⃣ Tính vị trí bắt đầu của mỗi nhóm
    for (int i = 1; i < m; i++) {
        L[i] += L[i - 1];
    }

    // 5️⃣ Hoán đổi phần tử vào đúng vị trí
    int i = 0, count = 0;
    while (count < n) {
        int index = scale * (a[i] - min_value);
        while (i >= L[index]) index = scale * (a[++i] - min_value);
        
        int temp = a[i];
        while (i != L[index]) {
            index = scale * (temp - min_value);
            swap(temp, a[--L[index]]);
            count++;
        }
    }

    // 6️⃣ Dùng Insertion Sort để hoàn tất sắp xếp
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/