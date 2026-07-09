/* Xử lí các ngoại lệ nhập thông tin vào */

#ifndef VALIDATION_H
#define VALIDATION_H
#include "product.h"

// * Xử lí nhập số nguyên
int inputInt(const char *prompt, int minValue, int maxValue); 

// * Xử lí nhập số thực
float inputFloat(const char *prompt, float minValue, float maxValue); 

// * Xử lí nhập chuỗi ký tự
void inputString(const char *prompt, char *buffer, int maxLength); 

// * Xử lí khi hỏi xác nhận (y/n)
int confirmYesNo(const char *prompt); 

// * Dọn sách bộ nhớ đệm bàn phím 
void clearInputBuffer();

// * Check xem id đã tồn tại chưa 
int isIdExists(Product listProducts[], int count, int id, int excludeIndex); 

#endif