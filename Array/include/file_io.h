#ifndef FILE_IO_H
#define FILE_IO_H
#include "product.h"

#define DATA_FILE "data/data.bin"

// * Nạp toàn bộ sản phẩm từ file products.bin vào mảng 
int loadProductsFromFile(Product listProducts[], int *count); 

// * Ghi đè toàn bộ data xuống file.bin 
int saveProductsToFile(Product listProducts[], int count); 

#endif