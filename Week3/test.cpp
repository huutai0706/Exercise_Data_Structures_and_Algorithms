#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>  // Thư viện để đo thời gian
#include <algorithm>  // Thư viện để đo thời gian
#include <iomanip>


using namespace std;
using namespace std::chrono;

void selection_sort(vector<int>& arr, long long& comparisons) {
    int n = arr.size();
    
    // Lặp qua tất cả các phần tử
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        
        // Tìm phần tử nhỏ nhất trong mảng chưa sắp xếp
        for (int j = i + 1; j < n; ++j) {
            comparisons++;  // Đếm phép so sánh
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Hoán đổi phần tử hiện tại với phần tử nhỏ nhất tìm được
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

void insertion_sort(vector<int>& arr, long long& comparisons) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            } else break;
        }
        arr[j + 1] = key;
    }
}


void bubble_sort(vector<int>& a, long long& comparisons) {
    int n = a.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) { 
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}


void shell_sort(vector<int>& a, long long& comparisons) {
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j = i;
            while (j >= gap) {
                comparisons++;
                if (a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    j -= gap;
                } else {
                    break;
                }
            }
            a[j] = temp;
        }
    }
}


void counting_sort(vector<int>& a, long long& comparisons) {
    comparisons = 0;  // Counting sort không thực hiện so sánh giữa các phần tử
    if (a.empty()) return;
    
    // Tìm giá trị lớn nhất trong mảng
    int max_a = *max_element(a.begin(), a.end());
    
    // Khởi tạo mảng đếm (count) với số lượng phần tử bằng với max_a + 1
    vector<int> count(max_a + 1, 0);
    
    // Đếm số lần xuất hiện của mỗi giá trị
    for (int num : a) {
        count[num]++;
    }

    // Dùng mảng đếm để tái tạo lại mảng đã sắp xếp
    int index = 0;
    for (int i = 0; i <= max_a; i++) {
        while (count[i] > 0) {
            a[index++] = i;
            count[i]--;
            comparisons++; // Đếm mỗi lần truy cập mảng đếm, mặc dù đây không phải là phép so sánh thực tế
        }
    }
}



void merge(vector<int>& a, int left, int mid, int right, long long& comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> l(n1), r(n2);
    for (int i = 0; i < n1; i++) l[i] = a[left + i];
    for (int i = 0; i < n2; i++) r[i] = a[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (l[i] <= r[j]) a[k++] = l[i++];
        else a[k++] = r[j++];
    }
    while (i < n1) a[k++] = l[i++];
    while (j < n2) a[k++] = r[j++];
}

void merge_sort(vector<int>& a, int left, int right, long long& comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(a, left, mid, comparisons);
        merge_sort(a, mid + 1, right, comparisons);
        merge(a, left, mid, right, comparisons);
    }
}


void flash_sort(vector<int>& a, long long& comparisons) {
    int n = a.size();
    if (n <= 1) return;

    int min_value = a[0], max_index = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < min_value) min_value = a[i];
        if (a[i] > a[max_index]) max_index = i;
    }

    if (a[max_index] == min_value) return;

    int m = int(0.45 * n);
    vector<int> L(m, 0);
    double scale = (double)(m - 1) / (a[max_index] - min_value);

    for (int i = 0; i < n; i++) {
        int index = scale * (a[i] - min_value);
        L[index]++;
    }

    for (int i = 1; i < m; i++) {
        L[i] += L[i - 1];
    }

    int i = 0, countMove = 0;
    while (countMove < n) {
        int index = scale * (a[i] - min_value);
        while (i >= L[index]) {
            index = scale * (a[++i] - min_value);
        }

        int temp = a[i];
        while (i != L[index]) {
            index = scale * (temp - min_value);
            swap(temp, a[--L[index]]);
            countMove++;
        }
    }

    // Insertion sort sau khi flash
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                j--;
            } else break;
        }
        a[j + 1] = key;
    }
}



void shaker_sort(vector<int>& arr, long long& comparisons) {
    int n = arr.size();
    int left = 0, right = n - 1;
    int temp;

    while (left < right) {
        for (int i = left; i < right; i++) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            comparisons++;
            if (arr[i] < arr[i - 1]) {
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
            }
        }
        left++;
    }
}



void Heapify(vector<int>& arr, int n, int i, long long& comparisons) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparisons++;
        if (arr[left] > arr[largest])
            largest = left;
    }

    if (right < n) {
        comparisons++;
        if (arr[right] > arr[largest])
            largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest, comparisons);
    }
}

void heap_sort(vector<int>& arr, long long& comparisons) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i, comparisons);

    for (int i = n - 1; i >= 1; i--) {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0, comparisons);
    }
}


void quick_sort(vector<int>& arr, int low, int high, long long& comparisons) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            comparisons++;
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quick_sort(arr, low, pi - 1, comparisons);
        quick_sort(arr, pi + 1, high, comparisons);
    }
}


void radix_sort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;  // Radix Sort không thực hiện so sánh giữa các phần tử
    int n = arr.size();
    if (n <= 1) return; // Nếu mảng chỉ có 1 phần tử hoặc trống, không cần sắp xếp

    int max_val = *max_element(arr.begin(), arr.end());

    // Sắp xếp theo từng chữ số (từ đơn vị đến hàng lớn nhất)
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        vector<int> output(n);
        int count[10] = {0};

        // Đếm số lần xuất hiện của từng chữ số tại vị trí exp
        for (int i = 0; i < n; i++) {
            comparisons++;  // Đếm số phép so sánh khi chia để lấy chữ số
            count[(arr[i] / exp) % 10]++;
        }

        // Tính chỉ số cuối cùng cho các chữ số (prefix sum)
        for (int i = 1; i < 10; i++) {
            comparisons++;  // Đếm số phép so sánh khi cộng dồn giá trị trong count
            count[i] += count[i - 1];
        }

        // Xây dựng mảng output theo thứ tự sắp xếp dựa trên chữ số ở vị trí exp
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        // Sao chép mảng output vào mảng gốc
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}





void WriteToFile(const string &filename, const vector<int>& arr) {
    ofstream file(filename);
    if (!file) {
        cerr << "khong the mo file " << filename << "!\n";
        exit(1);
    }

    for (int i = 0; i < arr.size(); i++) {
        file << arr[i] << " ";
    }
    file.close();
    cout << "da luu du lieu vao " << filename << "\n";
}

void ReadFromFile(const string& filename, vector<int>& arr) {
    ifstream file(filename);
    if (!file) {
        cerr << "khong th mo filer " << filename << "!\n";
        exit(1);
    }

    int num;
    while (file >> num) {
        arr.push_back(num);
    }
    file.close();
}

int main() {
    vector<int> arr;

    // Đọc dữ liệu từ file input.txt
    ReadFromFile("input.txt", arr);

    // Đếm số phép so sánh
    long long comparisons = 0;

    // Đo thời gian trước khi sắp xếp
    auto start = high_resolution_clock::now();

    // Thực hiện sắp xếp bằng Selection Sort
    // selection_sort(arr, comparisons);                  //1
    // insertion_sort(arr, comparisons);                  //2
    // bubble_sort(arr, comparisons);                     //3
    // shaker_sort(arr, comparisons);                     //4
    // shell_sort(arr, comparisons);                      //5
    // heap_sort(arr, comparisons);                       //6
    // merge_sort(arr, 0, arr.size()-1, comparisons);     //7
    quick_sort(arr,0, arr.size()-1, comparisons);      //8
    // counting_sort(arr, comparisons);                   //9
    // radix_sort(arr, comparisons);                      //10
    // flash_sort(arr, comparisons);                      //11

    // Đo thời gian sau khi sắp xếp
    auto end = high_resolution_clock::now();

    // Tính toán thời gian chạy
    auto duration = duration_cast<milliseconds>(end - start);

    // In kết quả
    cout << "So phep so sanh: " << comparisons << " lần\n";
    cout << "Thoi gian chay: " << fixed << setprecision(8) << duration.count() * 1.0 << " ms\n";

    // Ghi kết quả ra file (tùy chọn)
    WriteToFile("output.txt", arr);

    return 0;
}
