#include <stdio.h>
#include <string.h>
#include "../include/file_io.h"
#include "../include/validation.h"
#include "../include/table.h"
#include "../include/logger.h"
#include "../include/file_io.h"
#include "../include/color.h"

// * Nhập thông tin 1 sản phẩm từ bàn phím
static void inputOneProduct(Product *p, Product listProducts[], int count) {
    while (1) {
        p->id = inputInt("\t[+] Enter product ID: ", 1, 999999999); 
        if (isIdExists(listProducts, count, p->id, -1)) {
            setColor(COLOR_RED);
            printf("\t[Id đã tồn tại rồi. Vui lòng nhập lại !]\n");
            setColor(COLOR_DEFAULT);
            continue;
        }
        break; 
    }
    inputString("\t[+] Enter product name: ", p->name, MAX_NAME_LENGTH); 
    p->price = inputFloat("\t[+] Enter product price: ", 0.01, 999999999.99);
    p->quantity = inputInt("\t[+] Enter product quantity: ", 0, 999999999);
}

// * Option 1: Write Products - nhập mới hoàn toàn, ghi đè dữ liệu cũ 
void menuWriteProducts(Product listProducts[], int *count) {
    // *count = 25; // Gán thẳng số lượng là 25
    // int i;
    // for (i = 0; i < *count; i++) {
    //     list[i].id = i + 1; 
    //     sprintf(list[i].name, "Product Layer %d", i + 1); 
    //     list[i].price = (float)(15.5 + i * 2.5);
    //     list[i].quantity = 10 + i; 
    // }

    // saveProductsToFile(list, *count); 

    setColor(COLOR_BLUE);
    printf("\n");
    printf("\t\t+-----------------+\n");
    printf("\t\t|  WRITE PRODUCTS |\n");
    printf("\t\t+-----------------+\n");
    setColor(COLOR_DEFAULT);

    printf("[1]. Write product\n");
    printf("[0]. Back\n");

    int choice; 
    setColor(COLOR_CYAN);
    choice = inputInt(">> Enter choice: ", 0, 1); 
    setColor(COLOR_DEFAULT);

    if (choice == 0) return; 

    setColor(COLOR_CYAN);
    int n = inputInt(">> Enter the number of products to write: ", 0, MAX_PRODUCTS); 
    setColor(COLOR_DEFAULT);

    // Vì ghi đè dữ liệu nên reset *count = 0 
    *count = 0; 

    int i; 
    for (i = 0 ; i < n; i++) {
        printf("[-] Enter details for product %d:\n", i + 1);
        inputOneProduct(&listProducts[*count], listProducts, *count);
        (*count)++;  
    }

    if (saveProductsToFile(listProducts, *count) == 0) {
        setColor(COLOR_GREEN);
        printf("[Success: Products wrote to file successfully]\n");
        setColor(COLOR_DEFAULT);
        writeLog("WRITE","Overwrite data.bin", "SUCCESS");
    } else {
        setColor(COLOR_RED);
        printf("[Error: Failed to save products to file]\n");
        setColor(COLOR_DEFAULT);
        writeLog("WRITE","Overwrite data.bin", "FAILED");
    }
}

// * Option 2: AppendProducts - thêm sản phẩm mới vào cuối mảng , k mất dữ liệu 
void menuAppendProducts(Product listProducts[], int *count) {
    setColor(COLOR_BLUE);
    printf("\n");
    printf("\t\t+-----------------+\n");
    printf("\t\t| APPEND PRODUCTS |\n");
    printf("\t\t+-----------------+\n");
    setColor(COLOR_DEFAULT);

    printf("[1]. Add product\n");
    printf("[0]. Back\n");

    int choice; 
    setColor(COLOR_CYAN);
    choice = inputInt(">> Enter choice: ", 0, 1); 
    setColor(COLOR_DEFAULT);

    if (choice == 0) return; 

    setColor(COLOR_CYAN);
    int n = inputInt(">> Enter the number of products to append: ", 1, MAX_PRODUCTS - (*count)); 
    setColor(COLOR_DEFAULT);

    // Lưu lại số sản phẩm ban đầu trước khi thêm mới 
    int startCount = *count;

    for (int i = 0; i < n; i++) {
        if (*count >= MAX_PRODUCTS) {
            setColor(COLOR_RED); 
            printf("[Error: Storage is full, cannot append more]\n");
            setColor(COLOR_DEFAULT);
            break;
        }
        printf("[-] Enter details for product %d:\n", i + 1);
        inputOneProduct(&listProducts[*count], listProducts, *count);
        (*count)++;
    }

    // ab: append birary: ghi mới vào cuối file, không đụng tới phần dữ liệu cũ.
    FILE *file = fopen(DATA_FILE, "ab");
    if (file == NULL) {
        setColor(COLOR_RED); 
        printf("[Error: cannot open %s for appending]\n", DATA_FILE);
        setColor(COLOR_DEFAULT);
        writeLog("APPEND", "Append products", "FAILED");
        return;
    }
    fwrite(&listProducts[startCount], sizeof(Product), (*count) - startCount, file);
    fclose(file);

    setColor(COLOR_GREEN);
    printf("[Success: Products have been appended to the file successfully]\n");
    setColor(COLOR_DEFAULT);
    writeLog("APPEND", "Append products", "SUCCESS");
} 

// * Option 3: Read Products - hiện thị toàn bộ sản phẩm 
void menuReadProducts(Product listProducts[], int count) {
    setColor(COLOR_BLUE);
    printf("\n");
    printf("\t\t+-----------------+\n");
    printf("\t\t|  READ PRODUCTS  |\n");
    printf("\t\t+-----------------+\n");
    setColor(COLOR_DEFAULT);

    if (count == 0) {
        setColor(COLOR_YELLOW);
        printf("\t     [Notice: No product found]\n"); 
        setColor(COLOR_DEFAULT); 
        return; 
    }

    const int PAGE_SIZE = 10;
    int totalPages = (count + PAGE_SIZE - 1) / PAGE_SIZE;
    int page = 1; 

    while (1) {
        // system("cls");

        // Xác định sản phẩm đầu tiên của trang hiện tại 
        int start = (page - 1) * PAGE_SIZE; 

        // Ví trí kết thức của trang hiện tại 
        int end = start + PAGE_SIZE; 

        // Nếu end không đủ 10 sp thì ta gán nó bằng số sp thực tế 
        if (end > count) end = count; 

        // In tiêu đè trang hiện tại 
        setColor(COLOR_GREEN);
        printf("[Page %d / %d]\n", page, totalPages); 
        setColor(COLOR_DEFAULT);

        printProductTable(&listProducts[start], end - start); 

        printf("\n[N] Next\n[P] Previous\n[Q] Quit\n"); 
        
        char choice[50]; 
        setColor(COLOR_CYAN);
        printf(">> Enter character (n/p/q): ");
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            continue; 
        }
        setColor(COLOR_DEFAULT);
        choice[strcspn(choice, "\n")] = '\0';

        // Check số lượng kí tự
        if (strlen(choice) != 1) {
            setColor(COLOR_YELLOW);
            printf("[Warning: Vui lòng nhập lại, chỉ nhập kí tự đơn (N, P, Q) !]\n"); 
            setColor(COLOR_DEFAULT);
            continue;
        }

        // Kiểm tra kí tự nhập vào
        char c = choice[0]; 
        if (c == 'n' || c == 'N') {
            if (page < totalPages) 
                page++; 
            else {
                setColor(COLOR_YELLOW);
                printf("\t[This is the last page]\n"); 
                setColor(COLOR_DEFAULT);
            }
        } else if (c == 'p' || c == 'P') {
            if (page > 1) 
                page--;
            else {
                setColor(COLOR_YELLOW);
                printf("\t[This is the first page]\n"); 
                setColor(COLOR_DEFAULT);
            }
        } else if (c == 'q' || c == 'Q') {
            break;
        } else { 
            setColor(COLOR_YELLOW);
            printf("[Warining: Only (n | p | q)]\n"); 
            setColor(COLOR_DEFAULT); 
        }
    }
}

// * Option 4: Modify Products - sửa 1 sản phẩm theo id
void menuModifyProducts(Product listProducts[], int count) {
    setColor(COLOR_BLUE);
    printf("\n");
    printf("\t\t+-----------------+\n");
    printf("\t\t| MODIFY PRODUCTS |\n");
    printf("\t\t+-----------------+\n");
    setColor(COLOR_DEFAULT);

    if (count == 0) {
        setColor(COLOR_YELLOW);
        printf("\t\t[Notice: No product found]\n"); 
        setColor(COLOR_DEFAULT);
        return; 
    }

    setColor(COLOR_CYAN);
    int idToEdit = inputInt(">> Enter product ID to modify: ", 1, 999999999);
    setColor(COLOR_DEFAULT);

    // Tìm xem sản phẩm có id trong mảng không
    int index = -1; 
    int i; 
    for (i = 0; i < count; i++) {
        if (listProducts[i].id == idToEdit) {
            index = i;
            break; 
        }
    }

    if (index == -1) {
        setColor(COLOR_RED);
        printf("[Error: No product has id %d]\n", idToEdit); 
        setColor(COLOR_DEFAULT);
        writeLog("MODIFY", "Product not found", "FAILED");
        return; 
    }

    printf("[-] Product found. Enter new infomation: \n");

    // Cho phép giữ nguyên id, hoặc đổi id khác nếu chưa tồn tại id đó 
    int newId;
    while (1) {
        newId = inputInt("\t[+] New Product ID: ", 1, 999999999); 

        if (newId != idToEdit && isIdExists(listProducts, count, newId, index)) {
            setColor(COLOR_YELLOW);
            printf("\t[Notice: Id existed cannot edit]\n");
            setColor(COLOR_DEFAULT);
            writeLog("MODIFY", "Duplicate new ID", "FAILED"); 
            continue; 
        }
        break;
    }

    char newName[MAX_NAME_LENGTH];
    inputString("\t[+] New Product Name: ", newName, MAX_NAME_LENGTH);
    float newPrice = inputFloat("\t[+] New Price: ", 0.0, 9999999999.0);
    int newQty = inputInt("\t[+] New Quantity: ", 0, 1000000000);

    listProducts[index].id = newId;
    strcpy(listProducts[index].name, newName);
    listProducts[index].price = newPrice;
    listProducts[index].quantity = newQty;

    if (saveProductsToFile(listProducts, count) == 0) {
        setColor(COLOR_GREEN);
        printf("[Success: Product updated successfully]\n");
        setColor(COLOR_DEFAULT);
        writeLog("MODIFY", "Product updated", "SUCCESS");
    } else {
        writeLog("MODIFY", "Save failed", "FAILED");
    }
}

// * Chèn 1 sản phầm vào 1 vị trí bất kì 
static void insertAtPosition(Product listProducts[], int *count) {
    // Check mảng đã đầy chưa
    if (*count >= MAX_PRODUCTS) {
        setColor(COLOR_RED);
        printf("[Error: Array product full. Cannot insert]\n");
        setColor(COLOR_DEFAULT); 
        writeLog("INSERT", "List full", "FAILED");
        return; 
    }

    printf("\t[Current total products: %d]\n", *count); 

    setColor(COLOR_CYAN);
    int insertIndex = inputInt(">> Enter position to insert: ", 0, *count); 
    setColor(COLOR_DEFAULT); 

    // Nhập dữ liệu cho sản phẩm mới và hứng dữ liệu trước
    Product newProduct; 
    inputOneProduct(&newProduct, listProducts, *count);

    // Xác nhận 
    setColor(COLOR_YELLOW);
    if (!confirmYesNo("Are you sure want to insert?")) {
        setColor(COLOR_RED);
        printf("[Notice: Cancelled]\n");
        setColor(COLOR_DEFAULT); 
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
    setColor(COLOR_GREEN);
    printf("[Success: Product inserted successfully at position %d]\n", insertIndex);
    setColor(COLOR_DEFAULT);
    writeLog("INSERT", "Product inserted", "SUCCESS");
}

// * Option 5: Insert Products - chèn 1 sản phẩm vào chỗ bất kì
void menuInsertProduct(Product listProducts[], int *count) {
    setColor(COLOR_BLUE);
    printf("\n\t\t+-------------+\n");
    printf("\t\t| INSERT MENU |\n");
    printf("\t\t+-------------+\n");
    setColor(COLOR_DEFAULT);
    printf("[1]. Insert at a position\n");
    printf("[0]. Back\n");

    setColor(COLOR_CYAN);
    int choice = inputInt(">> Enter your choice: ", 0, 1);
    setColor(COLOR_DEFAULT);
    switch (choice)
    {
        case 1: insertAtPosition(listProducts, count); break;
        case 0: break;
        default: break;
    }
}

// * Hàm xóa 1 sản phẩm bất kì bằng id
static void deleteById(Product listProducts[], int *count) {
    setColor(COLOR_CYAN);
    int idToDelete  = inputInt(">> Delete ID: ", 1, 999999999); 
    setColor(COLOR_DEFAULT);

    int indexToDelete = -1; 
    int i; 
    for (i = 0; i < *count; i++) {
        if (listProducts[i].id == idToDelete) {
            indexToDelete = i;
            break;  
        } 
    }
    if (indexToDelete == -1) {
        setColor(COLOR_RED);
        printf("[Error: Product not found]\n");
        setColor(COLOR_DEFAULT);
        writeLog("DELETE", "ID not found", "FAILED");
        return;
    }

    if (!confirmYesNo("Are you sure ?")) {
        setColor(COLOR_YELLOW);
        printf("[Notice: Cancelled]\n");
        setColor(COLOR_DEFAULT);
        return;
    }

    for (i = indexToDelete; i < *count - 1; i++) {
        listProducts[i] = listProducts[i + 1]; 
    }
    (*count)--;

    saveProductsToFile(listProducts, *count);
    setColor(COLOR_GREEN);
    printf("[Success: Product deleted successfully]\n");
    setColor(COLOR_DEFAULT);
    writeLog("DELETE", "ID deleted", "SUCCESS");
}

// * Hàm xóa tất cả sản phẩm
static void deleteAll(Product listProducts[], int *count) {
    if (!confirmYesNo("Delete ALL products?")) {
        setColor(COLOR_RED);
        printf("[Notice: Cancelled]\n");
        setColor(COLOR_DEFAULT); 
        return;
    }

    *count = 0;
    saveProductsToFile(listProducts, *count);

    setColor(COLOR_GREEN); 
    printf("[Success: All products deleted ]\n");
    setColor(COLOR_DEFAULT); 

    writeLog("DELETE", "All products", "SUCCESS");
}

// * Option 6: Menu chức năng xóa 
void menuDeleteProduct(Product listProducts[], int *count) {
    if (*count == 0) {
        setColor(COLOR_YELLOW);
        printf("[Notice: No product found to delete]\n");
        setColor(COLOR_DEFAULT); 
        return; 
    }

    setColor(COLOR_BLUE);
    printf("\n\t\t+-------------+\n");
    printf("\t\t| DELETE MENU |\n");
    printf("\t\t+-------------+\n");
    setColor(COLOR_DEFAULT);
    printf("[1]. Delete by ID\n");
    printf("[2]. Delete all\n");
    printf("[0]. Back\n");

    setColor(COLOR_CYAN);
    int choice = inputInt(">> Enter your choice: ", 0, 2);
    setColor(COLOR_DEFAULT); 
    switch (choice)
    {
        case 1: deleteById(listProducts, count); break;
        case 2: deleteAll(listProducts, count); break;
        case 0: break;
        default:
            break;
    }
}