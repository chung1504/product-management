#include <stdio.h>
#include <string.h>
#include "../include/file_io.h"
#include "../include/validation.h"
#include "../include/table.h"
#include "../include/logger.h"
#include "../include/file_io.h"

// * Option 1: Write Products - nhập mới hoàn toàn, ghi đè dữ liệu cũ 
void menuWriteProducts(Product list[], int *count) {
    *count = 25; // Gán thẳng số lượng là 25
    int i;
    for (i = 0; i < *count; i++) {
        list[i].id = i + 1; // ID chạy từ 101, 102...
        sprintf(list[i].name, "Product Layer %d", i + 1); // Tên tự động tăng dần
        list[i].price = (float)(15.5 + i * 2.5); // Giá tiền tự tăng
        list[i].quantity = 10 + i; // Số lượng tự tăng
    }

    saveProductsToFile(list, *count); 
}

// * Hàm nội bộ dùng để nhập thông tin 1 sản phẩm từ bàn phím, đảm báo id không bị trùng
static void inputOneProduct(Product *p, Product listProducts[], int count) {
    while (1) {
        p->id = inputInt(">> Enter product ID: ", 1, 999999999); 
        if (isIdExists(listProducts, count, p->id, -1)) {
            printf("Id đã tồn tại rồi. Vui lòng nhập lại !\n");
            continue;
        }
        break; 
    }
    inputString(">> Enter product name: ", p->name, MAX_NAME_LENGTH); 
    p->price = inputFloat(">> Enter product price: ", 0.01, 999999999.99);
    p->quantity = inputInt(">> Enter product quantity: ", 0, 999999999);
}

// * Option 2: AppendProducts - thêm sản phẩm mới , k mất dữ liệu 
void menuAppendProducts(Product listProducts[], int *count) {
    printf("\n=== Append Products ====\n");
    int n = inputInt("Enter the number of products to append: ", 0, MAX_PRODUCTS - (*count)); 

    int startCount = *count;
    for (int i = 0; i < n; i++) {
        if (*count >= MAX_PRODUCTS) {
            printf("Storage is full, cannot append more.\n");
            break;
        }
        printf("Enter details for product %d:\n", i + 1);
        inputOneProduct(&listProducts[*count], listProducts, *count);
        (*count)++;
    }

    // Theo đúng tinh thần "Append" (mở file ở chế độ ab), ta chỉ cần ghi THÊM
    // những bản ghi mới vào CUỐI file, không đụng tới phần dữ liệu cũ.
    FILE *fp = fopen(DATA_FILE, "ab");
    if (fp == NULL) {
        printf("Error: cannot open %s for appending.\n", DATA_FILE);
        writeLog("APPEND", "Append products", "FAILED");
        return;
    }
    fwrite(&listProducts[startCount], sizeof(Product), *count - startCount, fp);
    fclose(fp);

    printf("Products have been appended to the file successfully.\n");
    writeLog("APPEND", "Append products", "SUCCESS");
} 

// * Option 3: Read Products - hiện thị toàn bộ sản phẩm 
void menuReadProducts(Product listProducts[], int count) {
    printf("\n======> Read Products <======\n"); 
    if (count == 0) {
        printf("<< No product found >>\n"); 
        return; 
    }

    const int PAGE_SIZE = 10; // mỗi trang 10 sp
    int totalPages = (count + PAGE_SIZE -1) / PAGE_SIZE; // tổng trang 
    int page = 1; // Mặc định là trang 1 

    while (1) {
        // Xác định sản phẩm đầu tiên của trang hiện tại 
        int start = (page - 1) * PAGE_SIZE; 

        // Ví trí kết thức của trang hiện tại 
        int end = start + PAGE_SIZE; 

        // Nếu end không đủ 10 sp thì ta gán nó bằng số sp thực tế 
        if (end > count) end = count; 

        // In tiêu đè trang hiện tại 
        printf("\nPage %d / %d\n", page, totalPages); 

        // gọi hàm in 
        printProductTable(&listProducts[start], end - start); 

        printf ("\n[N] Next\n[P] Previous\n[Q] Quit\n"); 

        char choice[64]; 
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            break; 
        }
        choice[strcspn(choice, "\n")] = '\0';

        if (strlen(choice) != 1) {
            printf("Vui lòng nhập lại, chỉ nhập kí tự đơn (N, P, Q) !\n"); 
            continue;
        }

        char c = choice[0]; 
        if (c == 'n' || c == 'N') {
            // Nếu chưa là cuối trang thì tăng lên 1 
            if (page < totalPages) 
                page++; 
            else 
                printf("Đây là trang cuối rồi \n");
        } else if (c == 'p' || c == 'P') {
            // Nếu chưa phải trang đầu thì giảm đi 1 trang 
            if (page > 1) 
                page--;
            else 
                printf("Đây là trang đầu tiên rồi\n"); 
        } 
        else if (c == 'q' || c == 'Q') 
            break; 
        else 
            printf("Chỉ nhập N, P hoặc Q \n"); 
    }
}

// * Option 4: Modify Products - sửa 1 sản phẩm theo id
void menuModifyProducts(Product listProducts[], int count) {
    printf("\n======> Modify Products <======\n");
    if (count == 0) {
        printf("<< No product found >>\n"); 
        return; 
    }

    int id = inputInt(">> Enter product ID to modify: ", 1, 999999999);

    // Tìm xem sản phẩm có id trong mảng không
    int index = -1; 
    int i; 
    for (i = 0; i < count; i++) {
        if (listProducts[i].id == id) {
            index = i;
            break; 
        }
    }

    if (index == -1) {
        printf("Không tìm thấy sản phẩm có id %d\n", id); 
        writeLog("MODIFY", "Product not found", "FAILED");
        return; 
    }

    printf("Sản phẩm được tìm thấy. Nhập thông tin mới: \n");

    // Cho phép giữ nguyên id, hoặc đổi id khác nếu chưa tồn tại id đó 
    int newId = inputInt("New Product ID: ", 1, 999999999); 

    if (newId != id && isIdExists(listProducts, count, newId, index)) {
        printf("Id đã tồn tại rồi không thể chỉnh sửa\n");
        writeLog("MODIFY", "Duplicate new ID", "FAILED"); 
        return; 
    }

    char newName[MAX_NAME_LENGTH];
    inputString("New Product Name: ", newName, MAX_NAME_LENGTH);
    float newPrice = inputFloat("New Price: ", 0.0, 9999999999.0);
    int newQty = inputInt("New Quantity: ", 0, 1000000000);

    listProducts[index].id = newId;
    strcpy(listProducts[index].name, newName);
    listProducts[index].price = newPrice;
    listProducts[index].quantity = newQty;

    if (saveProductsToFile(listProducts, count) == 0) {
        printf("Product updated successfully.\n");
        writeLog("MODIFY", "Product updated", "SUCCESS");
    } else {
        writeLog("MODIFY", "Save failed", "FAILED");
    }
}

// * Chèn 1 sản phầm vào 1 vị trí bất kì 
static void insertAtPosition(Product listProducts[], int *count) {
    // Check mảng đã đầy chưa
    if (*count >= MAX_PRODUCTS) {
        printf(">>> Error: Array product full. Cannot insert\n");
        writeLog("INSERT", "List full", "FAILED");
        return; 
    }

    printf("Current total products: %d\n", *count); 
    int insertIndex = inputInt(">> Enter position to insert: ", 0, *count); 

    // Nhập dữ liệu cho sản phẩm mới và hứng dữ liệu trước
    Product newProduct; 
    inputOneProduct(&newProduct, listProducts, *count);

    // Xác nhận 
    if (!confirmYesNo("Are you sure want to insert?")) {
        printf("Cancelled\n");
        return; 
    }

    // Dịch phần tử để chèn 
    int i; 
    for (i = *count; i > insertIndex; i--) {
        listProducts[i] = listProducts[i - 1]; 
    }

    // Gán lại dữ liệu đã hứng 
    listProducts[insertIndex] = newProduct; 

    (*count)++;
    saveProductsToFile(listProducts, *count); 
    printf("[--- Product inserted successfully at position %d---]\n", insertIndex);
    writeLog("INSERT", "Product inserted", "SUCCESS");
}

// * Option 5: Insert Products - chèn 1 sản phẩm vào chỗ bất kì
void menuInsertProduct(Product listProducts[], int *count) {
    printf("\n>>> Insert Menu <<<\n");
    printf("[1]. Insert at a specific position\n");
    printf("[0]. Back\n");

    int choice = inputInt(">> Enter your choice: ", 0, 1);
    switch (choice)
    {
        case 1: insertAtPosition(listProducts, count); break;
        case 0: break;
        default: break;
    }
}

// * Hàm xóa 1 sản phẩm bất kì bằng id
static void deleteById(Product listProducts[], int *count) {
    int idToDelete  = inputInt(">> Delete ID: ", 1, 999999999); 

    int indexToDelete = -1; 
    int i; 
    for (i = 0; i < *count; i++) {
        if (listProducts[i].id == idToDelete) {
            indexToDelete = i;
            break;  
        } 
    }
    if (indexToDelete == -1) {
        printf("Product not found.\n");
        writeLog("DELETE", "ID not found", "FAILED");
        return;
    }

    if (!confirmYesNo("Are you sure ? ")) {
        printf("Cancelled.\n");
        return;
    }

    for (i = indexToDelete; i < *count - 1; i++) {
        listProducts[i] = listProducts[i + 1]; 
    }
    (*count)--;

    saveProductsToFile(listProducts, *count);
    printf("Product deleted successfully.\n");
    writeLog("DELETE", "ID deleted", "SUCCESS");
}

// * Hàm xóa tất cả sản phẩm
static void deleteAll(Product listProducts[], int *count) {
    printf("\n>> Delete ALL products?\n");
    if (!confirmYesNo("Confirm")) {
        printf("Cancelled.\n");
        return;
    }
    *count = 0;
    saveProductsToFile(listProducts, *count);
    printf("All products deleted.\n");
    writeLog("DELETE", "All products", "SUCCESS");
}

// * Option 6: Menu chức năng xóa 
void menuDeleteProduct(Product listProducts[], int *count) {
    if (*count == 0) {
        printf("No product found to delete\n");
        return; 
    }

    printf("\n>>> Delete Menu <<<\n");
    printf("[1]. Delete by ID\n");
    printf("[2]. Delete all\n");
    printf("[0]. Back\n");

    int choice = inputInt(">> Enter your choice: ", 0, 2);
    switch (choice)
    {
        case 1: deleteById(listProducts, count); break;
        case 2: deleteAll(listProducts, count); break;
        case 0: break;
        default:
            break;
    }
}