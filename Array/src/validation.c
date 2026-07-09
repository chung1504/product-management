#include <stdio.h>
#include <string.h> 
#include <ctype.h>
#include "../include/validation.h"
#include "../include/color.h"

// * Xử lí nhập số nguyên
int inputInt(const char *prompt, int minValue, int maxValue) {
    char line[128]; 
    int value; 
    while (1) {
        printf("%s", prompt); 

        // Nếu fgets đọc bị lỗi, trả về NULL, tiếp tục vòng lặp để yêu cầu nhập lại
        if (fgets(line, sizeof(line), stdin) == NULL) {
            continue;
        }

        // Làm thùng rác chứa các kí tự thừa 
        char extra; 

        // Nó sẽ lấy line để mổ xẻ theo %d gán vào value, %c vào extra
        if (sscanf(line, " %d %c", &value, &extra) != 1) {
            setColor(COLOR_YELLOW);
            printf("\t[Warning: Vui lòng nhập một số nguyên hợp lệ]\n");
            setColor(COLOR_DEFAULT);
            continue; 
        }

        if (value < minValue || value > maxValue) {
            setColor(COLOR_YELLOW);
            printf("\t[Warning: Giá trị phải nằm trong khoảng từ %d đến %d]\n", minValue, maxValue);
            setColor(COLOR_DEFAULT);
            continue; 
        }

        return value; 
    }
}

// * Xử lí nhập số thực
float inputFloat(const char *prompt, float minValue, float maxValue) {
    char line[128];
    float value; 

    while(1) {
        printf("%s", prompt); 

        if (fgets(line, sizeof(line), stdin) == NULL) {
            continue; 
        }

        char extra; 
        if (sscanf(line, " %f %c", &value, &extra) != 1) {
            setColor(COLOR_YELLOW);
            printf("\t[Warning: Vui lòng nhập một số thực hợp lệ]\n");
            setColor(COLOR_DEFAULT);
            continue; 
        }

        if (value < minValue || value > maxValue) {
            setColor(COLOR_YELLOW);
            printf("\t[Warning: Giá trị phải nằm trong khoảng từ %.2f đến %.2f]\n", minValue, maxValue);
            setColor(COLOR_DEFAULT);
            continue; 
        }
        return value; 
    }
}

// * Xử lí nhập chuỗi ký tự
void inputString(const char *prompt, char *buffer, int maxLength) {
    while(1) {
        printf("%s", prompt); 

        // Đọc chuỗi nhập sau đó lưu thẳng vào buffer, nếu lõi khi fgets thì tiếp tục vòng lặp để yêu cầu nhập lại
        if (fgets(buffer, maxLength, stdin) == NULL) {
            continue; 
        }

        // Loại bỏ ký tự '\n' nếu có
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0'; 
            length--;
        } else {  
            // Nếu không có '\n' thì có nghĩa là người dùng nhập quá dài, cần cắt ngang để dọn sạch bộ đệm bàn phím
            clearInputBuffer();
        }

        if (maxLength == 0) {
            setColor(COLOR_YELLOW);
            printf("\t[Waring: Chiều dài chuỗi phải lớn hơn 0]\n");
            setColor(COLOR_DEFAULT);
            continue; 
        }

        return; 
    }
}

// * Xử lí khi hỏi xác nhận (y/n)
int confirmYesNo(const char *prompt) {
    char line[16]; 
    while(1) {
        setColor(COLOR_YELLOW);
        printf(">> %s (Y/N): ", prompt); 
        setColor(COLOR_DEFAULT);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            continue; 
        }

        // Dọn bộ nhớ đệm nếu người dùng nhập quá dài 
        size_t length = strlen(line); 
        if (length > 0 && line[length - 1] != '\n') {
            clearInputBuffer(); 
        }

        // Tìm xem có kí tự nào phía sau N / Y hay không 
        char choice, extra; 
        int numberScanned = sscanf(line, " %c %c", &choice, &extra);

        // Nếu = 1 tức là người dùng chỉ nhập 1 kí tự thôi 
        if (numberScanned == 1) {
            // Lấy kí tự đầu tiên ra éo in hoa để kiểm tra 
            char c = toupper(line[0]);
            if (c == 'Y') return 1; 
            if (c == 'N') return 0;
        }
        
        setColor(COLOR_YELLOW);
        printf("[Notice: Vui lòng nhập 'Y' hoặc 'N']\n");
        setColor(COLOR_DEFAULT);
    }
}

// * Xử lí buffer bàn phím 
void clearInputBuffer() {
    int c; 
    // Vòng lặp liên tục đọc từng ký tự trong bộ nhớ đệm ra
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// * Check xem id đã tồn tại chưa (1 = tồn tại, 0 = chưa tồn tại) 
int isIdExists(Product listProducts[], int count, int id, int excludeIndex) {
    int i;
    for (i = 0; i < count; i++) {
        if (i == excludeIndex) continue; // Bỏ qua chỉ số cần loại trừ

        if (listProducts[i].id == id) {
            return 1; 
        }
    }
    return 0; 
}