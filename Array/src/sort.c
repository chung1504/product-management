#include <stdio.h>
#include <string.h> 
#include "../include/sort.h"
#include "../include/validation.h"
#include "../include/file_io.h"
#include "../include/logger.h"
#include "../include/color.h"

// * Hàm static hoán đổi 2 phần tử 
static void swapProduct(Product *product1, Product *product2) {
    Product tmp = *product1; 
    *product1 = *product2;
    *product2 = tmp; 
}

// * Hàm so sánh 2 sản phẩm theo các thuộc tính 
static int compareByField(Product product1, Product product2, int field) {
    switch (field)
    {
    case 1:
        return product1.id - product2.id; 
    case 2: 
        return strcmp(product1.name, product2.name);
    case 3: 
        return (product1.price > product2.price) - (product1.price < product2.price);
    case 4: 
        return product1.quantity - product2.quantity; 
    }

    return 0; 
}

// * Option 8: Menu chọn các chức năng sắp xếp 
void menuSortProducts(Product listProducts[], int count) {
    if (count == 0) {
        setColor(COLOR_YELLOW);
        printf("\t\t[Notice: No product found]\n"); 
        setColor(COLOR_DEFAULT);
        return; 
    }

    setColor(COLOR_BLUE);
    printf("\n");
    printf("\t\t+-----------------+\n");
    printf("\t\t|    SORT MENU    |\n");
    printf("\t\t+-----------------+\n");
    setColor(COLOR_DEFAULT);

    printf("[1]. Sort by ID\n");
    printf("[2]. Sort by Name\n");
    printf("[3]. Sort by Price \n");
    printf("[4]. Sort by Quantity \n");
    printf("[0]. Back\n");

    setColor(COLOR_CYAN);
    int choice = inputInt(">> Enter your choice: ", 0, 4);
    setColor(COLOR_DEFAULT);

    if (choice == 0) return; 

    printf("\t[1]. Ascending\n");
    printf("\t[2]. Descending\n");

    setColor(COLOR_CYAN);
    int choice2 = inputInt("\t>> Enter your choice: ", 1, 2);
    setColor(COLOR_DEFAULT);
    
    int i, j; 
    for (i = 0; i < count - 1; i++) {
        int target = i; 
        for (j = i + 1; j < count; j++) {
            int cmp = compareByField(listProducts[j], listProducts[target], choice); 
            if ((choice2 == 1 && cmp < 0) || (choice2 == 2 && cmp > 0)) {
                target = j; 
            }
        }
        if (target != i) 
            swapProduct(&listProducts[i], &listProducts[target]);
    }

    saveProductsToFile(listProducts, count); 
    
    setColor(COLOR_GREEN);
    printf("[Success: Products sorted successfully]\n");
    setColor(COLOR_DEFAULT);

    writeLog("SORT", choice2 == 1 ? "Ascending" : "Descending", "SUCCESS");
}