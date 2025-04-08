#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Thay thế #define bằng const hoặc constexpr
const int N = 500000;  // Định nghĩa số lượng phần tử mặc định là 1000

// Hàm hoán vị
void HoanVi(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % n;
    }
    return;
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    return;
}

// Hàm phát sinh mảng dữ liệu có thứ tự giảm dần
void GenerateReverseData(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = n - 1 - i;
    }
    return;
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n) {
    GenerateSortedData(a, n);
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        int r1 = rand() % n;
        int r2 = rand() % n;
        HoanVi(a[r1], a[r2]);
    }
}

void WriteToFile(const string &filename, int a[], int n) {
    ofstream file(filename);
    if (!file) {
        cerr << "Khong the mo file " << filename << "!\n";
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        file << a[i] << " ";
    }
    file.close();
    cout << "Da luu du lieu vao " << filename << "\n";
}

int main() {
    int dataType;
    cout << "Chon loai du lieu (0: Ngau nhien, 1: Tang dan, 2: Giam dan, 3: Gan dung): ";
    cin >> dataType;
    
    // Sử dụng N thay vì n để xác định kích thước mảng
    int *a = new int[N];  // Sử dụng N đã được định nghĩa là 1000
    
    switch (dataType) {
        case 0: GenerateRandomData(a, N); break;
        case 1: GenerateSortedData(a, N); break;
        case 2: GenerateReverseData(a, N); break;
        case 3: GenerateNearlySortedData(a, N); break;
        default: cout << "Loai du lieu khong hop le!\n"; delete[] a; return 1;
    }
    
    WriteToFile("input.txt", a, N);
    
    delete[] a;
    return 0;
}
