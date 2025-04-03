#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

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

// Hàm ghi mảng vào file
void WriteToFile(const string &filename, int a[], int n) {
    ofstream file(filename);
    if (!file) {
        cerr << "Khong the mo file " << filename << "!\n";
        exit(1);
    }
    //file << n << "\n"; // Ghi số lượng phần tử vào dòng đầu tiên
    for (int i = 0; i < n; i++) {
        file << a[i] << " ";
    }
    file.close();
    cout << "Da luu du lieu vao " << filename << "\n";
}

// Hàm chính
int main() {
    int n, dataType;
    cout << "Nhap so phan tu cua mang: ";
    cin >> n;
    cout << "Chon loai du lieu (0: Ngau nhien, 1: Tang dan, 2: Giam dan, 3: Gan dung): ";
    cin >> dataType;
    
    int *a = new int[n];
    
    switch (dataType) {
        case 0: GenerateRandomData(a, n); break;
        case 1: GenerateSortedData(a, n); break;
        case 2: GenerateReverseData(a, n); break;
        case 3: GenerateNearlySortedData(a, n); break;
        default: cout << "Loai du lieu khong hop le!\n"; delete[] a; return 1;
    }
    
    WriteToFile("input.txt", a, n);
    
    delete[] a;
    return 0;
}
