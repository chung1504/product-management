#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H
#include "product.h"

// * Option 1: Write Products - nhập mới hoàn toàn, ghi đè dữ liệu cũ
void menuWriteProducts(Product listProducts[], int *count);

// * Option 2: AppendProducts - thêm sản phẩm mới , k mất dữ liệu
void menuAppendProducts(Product listProducts[], int *count);

// * Option 3: Read Products - hiện thị toàn bộ sản phẩm
void menuReadProducts(Product listProducts[], int count);

// * Option 4: Modify Products - sửa 1 sản phẩm theo id
void menuModifyProducts(Product listProducts[], int count);

// * Option 5: Insert Products - chèn 1 sản phẩm vào chỗ bất kì
void menuInsertProduct(Product listProducts[], int *count);

// * Option 6: Delete Product - menu con xóa theo ID hoặc xóa tất cả
void menuDeleteProduct(Product listProduct[], int *count);

#endif