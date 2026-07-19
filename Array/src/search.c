#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include "../include/search.h"
#include "../include/validation.h"
#include "../include/table.h"
#include "../include/color.h"

// * static: chuyển 1 ký tự sang chữ thường, so sanh chuỗi không phân biệt hoa thường 
static char lower(char c) {
    return tolower(c); 
}

// * static: kiểm tra 1 chuỗi cần tìm có xuất hiện trong chuỗi lớn không 
static int containsIgnoreCase(const char *bigString, const char *findString) {
    // Đo dộ dài chuỗi lớn và chuỗi cần tìm 
    int lengthBigString = strlen(bigString);
    int lengthFindString = strlen(findString);

    // Nếu từ khóa cần tìm bị rỗng (k nhập gì) , thì coi như tìm thấy 
    if (lengthFindString == 0) return 1; 

    // Lặp tới vị trí của độ dài chuỗi lớn - đọ dài chuỗi cần tìm, ví dụ 
    // Có cây thước 10 cm (lớn) , 3cm (cần tìm) thì ta chỉ cần đặt thước tới đoạn 7cm để so sánh thôi 
    int i, j; 
    for (i = 0 ; i <= lengthBigString - lengthFindString; i++) {
        int foundMatchingString = 1; 
        // duyệt qua trùng kí tự chuỗi con xem có khớp không 
        for (j = 0; j < lengthFindString; j++) {
            // Chuyển cả 2 về chữ thường và so sanh 
            if (lower(bigString[i + j]) != lower(findString[j])) {
                foundMatchingString = 0;
                break;
            }
        }

        // Nếu lặp hết các chuỗi con mà vẫn = 1 thì chứng tỏ khớp hết 
        if (foundMatchingString) return 1; 
    }

    return 0; 
}

// * Tách chuoix ddieuf kiện 
static int parseConditions(const char *text, char operator[3], float *value) {
    int indexNumber = 0;   // đánh dấu xem vị trí số là thứ mất 
    if (text[0] == '>' && text[1] == '=') {
        strcpy(operator, ">="); 
        indexNumber = 2; // Đánh dấu rằng con số là vị trí thứ 2 ,vì >= chiếm 0 và 1 rồi
    }
    else if (text[0] == '<' && text[1] == '=') {
        strcpy(operator, "<="); 
        indexNumber = 2; 
    }
    else if (text[0] == '>') {
        strcpy(operator, ">");
        indexNumber = 1; 
    }    
    else if (text[0] == '<') { 
        strcpy(operator, "<"); 
        indexNumber = 1; 
    }
    else if (text[0] == '=') { 
        strcpy(operator, "="); 
        indexNumber = 1; 
    }

    // Đọc con số sau toán tử so sánh vừa nhập trên 
    if (sscanf(text + indexNumber, "%f", value) != 1) 
        return 0; 

    return 1; 
}

// * Hàm này dùng để để kiểm tra có khớp không khi đã bóc tách chuỗi điều kiện
static int checkCondition(float realValueProduct, const char *operator, float valueOfCondition) {
    if (strcmp(operator, ">=") == 0) 
        return realValueProduct >= valueOfCondition; 
    if (strcmp(operator, "<=") == 0) 
        return realValueProduct <= valueOfCondition; 
    if (strcmp(operator, ">") == 0) 
        return realValueProduct > valueOfCondition; 
    if (strcmp(operator, "<") == 0) 
        return realValueProduct < valueOfCondition; 

    return realValueProduct == valueOfCondition; 
}

// * Tìm bằng id 
static void searchById(Product listProducts[], int count) {
    setColor(COLOR_CYAN);
    int id = inputInt(">> Enter ID to find: ", 1, 99999999); 
    setColor(COLOR_DEFAULT); 

    Product result[1]; 
    int found = 0; 
    int i;
    for (i = 0; i < count; i++) {
        if (listProducts[i].id == id) {
            result[0] = listProducts[i]; 
            found = 1;
            break; 
        }
    }
    printProductTable(result, found ? 1 : 0); 
}

// * Tìm bằng ký tự
static void sreachByKeyword(Product listProducts[], int count) {
    char keyword[MAX_NAME_LENGTH]; 
    setColor(COLOR_CYAN);
    inputString(">> Enter keyword to find: ", keyword, MAX_NAME_LENGTH); 
    setColor(COLOR_DEFAULT); 

    Product result[MAX_PRODUCTS]; 
    int found = 0; 
    int i; 
    for (i = 0; i < count; i++) {
        if (containsIgnoreCase(listProducts[i].name, keyword)) {
            result[found] = listProducts[i]; 
            found++; 
        }
    }

    printProductTable(result, found); 
}

// * Tìm kiếm bằng giá trị sản phẩm
static void searchByPrice(Product listProducts[], int count) {
    char text[30]; 
    setColor(COLOR_CYAN);
    inputString(">> Enter price condition (ex: >= 100 || = 100): ", text, sizeof(text)); 
    setColor(COLOR_DEFAULT); 

    char operator[3]; 
    float value; 
    if (!parseConditions(text, operator, &value)) {
        setColor(COLOR_RED);
        printf("[Error: Invalid condition format]\n");
        setColor(COLOR_DEFAULT);
        return;
    }

    Product results[MAX_PRODUCTS]; 
    int i; 
    int found = 0;
    for (i = 0; i < count; i++) {
        if (checkCondition(listProducts[i].price, operator, value)) {
            results[found] = listProducts[i]; 
            found++;
        }
    }

    printProductTable(results, found); 
}

// * Tìm kiến bằng sản phẩm kho hàng 
static void searchByQuantity(Product listProducts[], int count) {
    char text[30]; 
    setColor(COLOR_CYAN);
    inputString(">> Enter quantity condition (ex: >= 100 hoặc = 10): ", text, MAX_NAME_LENGTH);
    setColor(COLOR_DEFAULT); 

    char operator[3]; 
    float value; 

    if (!parseConditions(text, operator, &value)) {
        setColor(COLOR_RED);
        printf("[Error: Invalid condition format]\n");
        setColor(COLOR_DEFAULT);
        return;
    }

    Product results[MAX_PRODUCTS]; 
    int found = 0;
    int i; 
    for (i = 0 ; i < count; i++) {
        if (checkCondition(listProducts[i].quantity, operator, value)) {
            results[found] = listProducts[i];
            found++;
        }
    }

    printProductTable(results, found); 
}

// * Option 7:  hiện thị menu con để chọn các kiểu tìm kiếm
void menuSearchProduct(Product listProducts[], int count) {
    if (count == 0) {
        setColor(COLOR_YELLOW);
        printf("[Notice: No product found]\n"); 
        setColor(COLOR_DEFAULT);
        return; 
    }

    setColor(COLOR_BLUE);
    printf("\n");
    printf("\t\t+-----------------+\n");
    printf("\t\t|   SEARCH MENU   |\n");
    printf("\t\t+-----------------+\n");
    setColor(COLOR_DEFAULT);

    printf("[1]. Search by ID\n");
    printf("[2]. Search by Name\n");
    printf("[3]. Search by Price \n");
    printf("[4]. Search by Quantity \n");
    printf("[0]. Back\n");

    setColor(COLOR_CYAN);
    int choice = inputInt(">> Enter your choice: ", 0, 4);
    setColor(COLOR_DEFAULT);
    switch (choice)
    {
        case 1: searchById(listProducts, count); break;
        case 2: sreachByKeyword(listProducts, count); break;
        case 3: searchByPrice(listProducts, count); break; 
        case 4: searchByQuantity(listProducts, count); break;
        case 0: break;
        default: break;
    }
}