#include "../include/color.h"

// * Thiết lập màu
void setColor(int color) {
    // Lấy quyền điều khiện terminal 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Thiết lập màu mới
    SetConsoleTextAttribute(hConsole, color); 
}