#ifndef LOGGER_H
#define LOGGER_H

// * Ghi 1 dòng log vào file log.txt khi có thao tác quan trọng như thêm xóa sửa 
void writeLog(const char *action, const char *details, const char *status);

// * Đọc và in toàn bộ file log.txt ra màn hình 
void viewLogs(); 

#endif