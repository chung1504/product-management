#include <stdio.h>
#include <string.h>
#include "../include/file_io.h"
#include "../include/validation.h"
#include "../include/table.h"
#include "../include/logger.h"
#include "../include/color.h"

// * Mở program và nạp toàn bộ sản phẩm từ file .bin vào mảng 
int loadProductsFromFile(Product listProducts[], int *count) {
    *count = 0;
    FILE *file = fopen(DATA_FILE, "rb"); 
    if (file == NULL) {
        // Nếu file chưa có thì tạo 1 file rỗng rồi đóng lại
        file = fopen(DATA_FILE, "wb");
        if (file != NULL) {
            fclose(file);
            return 0;
        }

        // Nếu đến đây vẫn NULL thì mới thực sự là lỗi
        setColor(COLOR_RED);
        printf("[Error: Cannot open or create %s]\n", DATA_FILE);
        setColor(COLOR_DEFAULT);
        return -1; 
    }

    Product p; 
    // fread: trả về số phần tử đọc được , đọc tới khi hết file hoặc đầy mảng 
    while (*count < MAX_PRODUCTS && fread(&p, sizeof(Product), 1, file) == 1) {
        listProducts[*count] = p;
        (*count)++; 
    }
    fclose(file);
    return 0; 
}

// * Ghi đè toàn bộ mảng xuống file.bin 
int saveProductsToFile(Product listProducts[], int count) {
    // "wb" = write binary, GHI ĐÈ toàn bộ nội dung file cũ 
    FILE *file = fopen(DATA_FILE, "wb"); 
    if (file == NULL) {
        setColor(COLOR_RED);
        printf("[Error: cannot open %s for writing]\n", DATA_FILE);
        setColor(COLOR_DEFAULT);
        return -1; 
    }

    // Ghi cả nấy phtu xuống luôn
    fwrite(listProducts, sizeof(Product), count, file);
    fclose(file);
    return 0; 
}