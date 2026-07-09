#include <stdio.h>
#include "../include/statistics.h"
#include "../include/validation.h"
#include "../include/table.h"

//* Tổng tất cả sản phẩm
static void totalProducts(Product listProducts[], int count) {
    int countProduct = 0; 
    int i; 
    for (i = 0; i < count; i++) {
        countProduct++; 
    }

    printf (">> Total products: %d <<", countProduct); 
}

// * TỔng hàng hóa còn lại
static void totalQuantity(Product listProducts[], int count) {
    int sum = 0; 
    int i; 
    for (i = 0; i < count; i++) {
        sum += listProducts[i].quantity;
    }

    printf (">> Total quantity: %d <<", sum);  
}

// * Giá sản phẩm cao nhất 
static void highestPrice(Product listProducts[], int count) {
    float maxPrice; 
    int i; 
    int index = 0;
    for (i = 0; i < count; i++) {
        if (maxPrice < listProducts[i].price) {
            maxPrice = listProducts[i].price; 
            index = i; 
        }
    }

    Product result[1]; 
    result[0] = listProducts[index];
    printProductTable(result, 1); 
    printf (">> The products highest price: %.2f <<\n", maxPrice); 
}

// * Giá sản phẩm thấp nhất 
static void lowestPrice(Product listProducts[], int count) {
    float minPrice; 
    int i; 
    int index = 0;
    for (i = 0; i < count; i++) {
        if (minPrice > listProducts[i].price) {
            minPrice = listProducts[i].price; 
            index = i;
        }
    }

    Product result[1]; 
    result[0] = listProducts[index];
    printProductTable(result, 1); 
    printf (">> The products lowest price: %.2f <<", minPrice);  
}

// * Giá trung bình các sản phẩm
static void averagePrice(Product listProducts[], int count) {
    int i; 
    float averagePriceProducts = 0;
    for (i = 0; i < count; i++) {
        averagePriceProducts += listProducts[i].price;
    }

    printf (">> Total value average of all products: %.2f <<", averagePriceProducts / (float)count); 
}

// * Tổng giá trị sản phẩm 
static void totalValue(Product listProducts[], int count) {
    int i; 
    float averagePriceProducts = 0;
    for (i = 0; i < count; i++) {
        averagePriceProducts += listProducts[i].price;
    }

    printf (">> Total value of all products: %.2f <<", averagePriceProducts); 
}


// * Option 8: Statistics - tính các thông kê về product
void menuStatisticsProduct(Product listProducts[], int count) {
    printf("\n=== Statistics ===\n");
    if (count == 0) {
        printf("No product found.\n");
        return;
    }

    printf("\n>>> Statistics Menu <<<\n");
    printf("[1]. Total Products\n");
    printf("[2]. Total Quantity\n");
    printf("[3]. Highest Price\n");
    printf("[4]. Lowest Price\n");
    printf("[5]. Average Price\n");
    printf("[6]. Total Value\n");
    printf("[0]. Back\n");

    int choice = inputInt(">> Enter your choice: ", 0, 6);
    switch (choice)
    {
        case 1: totalProducts(listProducts, count); break;
        case 2: totalQuantity(listProducts, count); break;
        case 3: highestPrice(listProducts, count); break; 
        case 4: lowestPrice(listProducts, count); break;
        case 5: averagePrice(listProducts, count); break;
        case 6: totalValue(listProducts, count); break;
        case 0: break;
        default:
            break;
    }
}

