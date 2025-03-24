#include <iostream>
using namespace std;

const int N = 8;       // Kích thước của bàn cờ
int board[N][N] = {0}; // Bàn cờ 8x8, khởi tạo tất cả các ô là 0
int solutions = 0;     // Biến đếm số cách sắp xếp các quân hậu

// Hàm kiểm tra xem có thể đặt quân hậu tại vị trí (row, col) không
bool isSafe(int row, int col){
    for (int i = 0; i < row; i++){
        if (board[i][col] == 1)
            return false; // Kiểm tra cột
        if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1)
            return false; // Kiểm tra đường chéo trái
        if (col + (row - i) < N && board[i][col + (row - i)] == 1)
            return false; // Kiểm tra đường chéo phải
    }
    return true; // Nếu không có quân hậu nào vi phạm các điều kiện, trả về true
}

// Hàm đệ quy giải quyết bài toán N-Queens
void solveNQueens(int row){
    if (row == N){
        solutions++; // Tăng số lượng nghiệm hợp lệ 
        return;      // dừng đệ quy
    }
    // Duyệt tất cả các cột trong dòng hiện tại để thử đặt quân hậu
    for (int col = 0; col < N; col++){
        // Kiểm tra nếu có thể đặt quân hậu tại vị trí (row, col)
        if (isSafe(row, col)){
            board[row][col] = 1;   // Đặt quân hậu tại vị trí (row, col)
            solveNQueens(row + 1); // Đệ quy vào dòng tiếp theo
            board[row][col] = 0;   // Quay lại nếu không tìm được nghiệm hợp lệ
        }
    }
}

int main(){
    solveNQueens(0);
    cout << solutions << endl;
    return 0;
}
