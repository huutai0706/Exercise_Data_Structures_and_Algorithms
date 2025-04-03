#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "algorithm.h"

using namespace chrono;
using namespace std;

// Hàm đọc dữ liệu từ file vào vector
void read_file(const string& filename, vector<int>& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong the mo file: " << filename << "!!!\n" << endl;
        exit(1);
    }
    int num;
    while (file >> num) {
        data.push_back(num);
    }
    file.close();
}

// Hàm ghi dữ liệu từ vector vào file
void write_file(const string& filename, const vector<int>& data) {
    ofstream file(filename);
    if (!file) {
        cerr << "Khong the mo file: " << filename << "!!!\n" << endl;
        exit(1);
    }
    for (int num : data) {
        file << num << " ";
    }
    file.close();
}

int main(int argc, char* argv[]) {
    string algorithm, ip, op;
    vector<int> data;

    // Kiểm tra nếu số lượng tham số không đủ
    if (argc < 7) {
        cerr << "Cach su dung: " << argv[0] << " -a <ten thuat toan> -i <file input> -o <file output>" << endl;
        return 1;
    }

    // Xử lý tham số dòng lệnh
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-a" && i + 1 < argc) {
            algorithm = argv[++i];
        } else if (arg == "-i" && i + 1 < argc) {
            ip = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            op = argv[++i];
        } else {
            cerr << "Tham so khong hop le: " << arg << endl;
            return 1;
        }
    }

    // Đọc file đầu vào
    read_file(ip, data);

    // Kiểm tra nếu file rỗng
    if (data.empty()) {
        cerr << "File input rong!" << endl;
        return 1;
    }

    auto start = high_resolution_clock::now(); // Bắt đầu đo thời gian

    // Chọn thuật toán sắp xếp
    if (algorithm == "selection_sort") {
        selection_sort(data);
    } else if (algorithm == "bubble_sort") {
        bubble_sort(data);
    } else if (algorithm == "merge_sort") {
        merge_sort(data, 0, data.size() - 1); 
    } else if (algorithm == "shell_sort") {
        shell_sort(data);
    } else if (algorithm == "counting_sort") {
        counting_sort(data);
    } else if (algorithm == "flash_sort") {
        flash_sort(data);
    } else {
        cerr << "Thuat toan khong hop le!" << endl;
        return 1;
    }

    auto end = high_resolution_clock::now(); // Kết thúc đo thời gian

    // Tính toán thời gian chạy
    auto duration = duration_cast<milliseconds>(end - start);

    // Ghi kết quả ra file đầu ra
    write_file(op, data);

    cout << "\nDa sap xep xong, luu vao file " << op << endl;
    cout << "\nThoi gian chay thuat toan " << algorithm << " la: " << duration.count() << " mili giay!\n\n"; 
    return 0;
}
