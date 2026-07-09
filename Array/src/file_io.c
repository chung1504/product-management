#include <stdio.h>
#include <string.h>
#include "../include/file_io.h"
#include "../include/validation.h"
#include "../include/table.h"
#include "../include/logger.h"

// * Nạp toàn bộ sản phẩm từ file .bin vào mảng 
int loadProductsFromFile(Product listProducts[], int *count) {
    *count = 0;
    FILE *file = fopen(DATA_FILE, "rb"); 
    if (file == NULL) {
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

// * Ghi đè toàn bộ data xuống file.bin 
int saveProductsToFile(Product listProducts[], int count) {
    // "wb" = write binary, GHI ĐÈ toàn bộ nội dung file cũ 
    FILE *file = fopen(DATA_FILE, "wb"); 
    if (file == NULL) {
        printf("Error: cannot open %s for writing\n", DATA_FILE);
        return -1; 
    }

    fwrite(listProducts, sizeof(Product), count, file);
    fclose(file);
    return 0; 
}