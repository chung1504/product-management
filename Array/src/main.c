#include <stdio.h> 
#include "../include/menu.h"
#include "../include/validation.h"
#include "../include/table.h"
#include "../include/product.h"
#include "../include/file_io.h"
#include "../include/search.h"
#include "../include/sort.h"
#include "../include/statistics.h"
#include "../include/logger.h"
#include "../include/export.h"
#include "../include/product_manager.h"

int main() {
    Product products[MAX_PRODUCTS]; 
    int count = 0; 

    loadProductsFromFile(products, &count); 

    int choice; 
    do {
        showMainMenu();
        choice = inputInt(">> Enter your choice: ", 0, 12);
        switch (choice) {
            case 1: menuWriteProducts(products, &count); break;
            case 2: menuAppendProducts(products, &count); break;
            case 3: menuReadProducts(products, count); break; 
            case 4: menuModifyProducts(products, count); break; 
            case 5: menuInsertProduct(products, &count); break;
            case 6: menuDeleteProduct(products, &count); break;
            case 7: menuSearchProduct(products, count); break;
            case 8: menuSortProducts(products, count); break; 
            case 9: menuStatisticsProduct(products, count); break; 
            case 10: menuExportProducts(products, count); break;
            case 11: viewLogs(); break;
            case 12: clearScreen(); break;
            case 0 :printf("Exiting the program....\n"); break;
        default:
            printf(">>> Invalid choice. Please try again <<<\n");
            break;
        }
    } while (choice != 0); 

    return 0; 
}