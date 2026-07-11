#include <stdio.h>
#include "../include/statistics.h"
#include "../include/validation.h"
#include "../include/table.h"
#include "../include/color.h"

//* Tổng tất cả sản phẩm
static void totalProducts(Product listProducts[], int count) {
    int countProduct = 0; 
    int i; 
    for (i = 0; i < count; i++) {
        countProduct++; 
    }

    setColor(COLOR_GREEN);
    printf ("\t\t[Total products: %d]\n", countProduct); 
    setColor(COLOR_DEFAULT);
}

// * TỔng hàng hóa còn lại
static void totalQuantity(Product listProducts[], int count) {
    int sum = 0; 
    int i; 
    for (i = 0; i < count; i++) {
        sum += listProducts[i].quantity;
    }

    setColor(COLOR_GREEN);
    printf ("\t\t[Total quantity: %d]\n", sum); 
    setColor(COLOR_DEFAULT); 
}

// * Giá sản phẩm cao nhất 
static void highestPrice(Product listProducts[], int count) {
    int i; 
    float maxPrice = listProducts[0].price; 
    // Tìm giá sản phẩm cao nhất 
    for (i = 0; i < count; i++) {
        if (maxPrice < listProducts[i].price) {
            maxPrice = listProducts[i].price; 
        }
    }

    Product result[MAX_PRODUCTS]; 
    int resultCount = 0; 
    // Nếu sản phầm vị trí nào = maxPrice thì gán sang mảng mới
    for (i = 0; i < count; i++) {
        if (listProducts[i].price == maxPrice) {
            result[resultCount] = listProducts[i];
            resultCount++;
        }
    }

    printProductTable(result, resultCount); 

    setColor(COLOR_GREEN);
    printf ("[The products highest price: %.2f and found %d products]\n", maxPrice, resultCount); 
    setColor(COLOR_DEFAULT); 
}

// * Giá sản phẩm thấp nhất 
static void lowestPrice(Product listProducts[], int count) {
    float minPrice = listProducts[0].price; 
    int i; 
    for (i = 0; i < count; i++) {
        if (minPrice > listProducts[i].price) {
            minPrice = listProducts[i].price; 
        }
    }

    Product result[MAX_PRODUCTS];
    int resultCount = 0; 
    for (i = 0; i < count; i++) {
        if (listProducts[i].price == minPrice) {
            result[resultCount] = listProducts[i];
            resultCount++; 
        }
    }
    printProductTable(result, resultCount); 

    setColor(COLOR_GREEN);
    printf ("[The products lowest price: %.2f and found %d products]\n", minPrice, resultCount); 
    setColor(COLOR_DEFAULT); 
}

// * Giá trung bình các sản phẩm
static void averagePrice(Product listProducts[], int count) {
    int i; 
    float averagePriceProducts = 0;
    for (i = 0; i < count; i++) {
        averagePriceProducts += listProducts[i].price;
    }

    setColor(COLOR_GREEN);
    printf ("\t[Total value average of all products: %.2f]\n", averagePriceProducts / (float)count); 
    setColor(COLOR_DEFAULT); 
}

// * Tổng giá trị sản phẩm 
static void totalValue(Product listProducts[], int count) {
    int i; 
    float averagePriceProducts = 0;
    for (i = 0; i < count; i++) {
        averagePriceProducts += listProducts[i].price;
    }

    setColor(COLOR_GREEN);
    printf ("\t[Total value of all products: %.2f]\n", averagePriceProducts); 
    setColor(COLOR_DEFAULT); 
}


// * Option 9: Statistics - tính các thông kê về product
void menuStatisticsProduct(Product listProducts[], int count) {
    if (count == 0) {
        setColor(COLOR_YELLOW);
        printf("\t\t[Notice: No product found]\n"); 
        setColor(COLOR_DEFAULT);
        return; 
    }

    setColor(COLOR_BLUE);
    printf("\n");
    printf("\t\t+-----------------+\n");
    printf("\t\t| STATISTICS MENU |\n");
    printf("\t\t+-----------------+\n");
    setColor(COLOR_DEFAULT);

    printf("[1]. Total Products\n");
    printf("[2]. Total Quantity\n");
    printf("[3]. Highest Price\n");
    printf("[4]. Lowest Price\n");
    printf("[5]. Average Price\n");
    printf("[6]. Total Value\n");
    printf("[0]. Back\n");

    setColor(COLOR_CYAN);
    int choice = inputInt(">> Enter your choice: ", 0, 6);
    setColor(COLOR_DEFAULT);

    switch (choice)
    {
        case 1: totalProducts(listProducts, count); break;
        case 2: totalQuantity(listProducts, count); break;
        case 3: highestPrice(listProducts, count); break; 
        case 4: lowestPrice(listProducts, count); break;
        case 5: averagePrice(listProducts, count); break;
        case 6: totalValue(listProducts, count); break;
        case 0: break;
        default: break;
    }
}

