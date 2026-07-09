#include <stdio.h>
#include <time.h> 
#include "../include/logger.h"
#include "../include/color.h"

#define LOG_FILE "data/logger.txt"

// * Ghi 1 dòng log vào file log.txt khi có thao tác quan trọng như thêm xóa sửa 
void writeLog(const char *action, const char *details, const char *status) {
    // "a" là chế độ mở file để ghi thêm vào cuối file, nếu file chưa tồn tại thì tạo mới
    FILE *file = fopen(LOG_FILE, "a"); 
    if (file == NULL) {
        setColor(COLOR_RED);
        perror("[Error: Cannot opening log file]");
        setColor(COLOR_DEFAULT);
        return;
    }

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    fprintf(file, "[%04d-%02d-%02d %02d:%02d:%02d] %s: %s - %s\n", 
            tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
            tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec,
            action, details, status);

    fclose(file);
}

// * Option 11: Đọc và in toàn bộ file log.txt ra màn hình 
void viewLogs() {
    FILE *file = fopen(LOG_FILE, "r"); 
    if (file == NULL) {
        setColor(COLOR_YELLOW);
        printf("\t\t[Notice: No logs found]\n");
        setColor(COLOR_DEFAULT); 
        return;
    }

    char line[300]; 
    int hasContent = 0; 
    while (fgets(line, sizeof(line), file) != NULL) {
        hasContent = 1; 
        printf("%s", line); 
    }
    if (!hasContent) {
        setColor(COLOR_YELLOW);
        printf("\t\t[Notice: No logs found]\n");
        setColor(COLOR_DEFAULT); 
    }
    fclose(file);
}