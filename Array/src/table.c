#include <stdio.h> 
#include <string.h> 
#include "../include/table.h"
#include "../include/color.h"

// * Vẽ đường kẻ ngang dạng +----+----+ linh động theo độ rộng từng cột
static void printSeparator(int idWidth, int nameWidth, int priceWidth, int quanlityWidth) {
    int i; 
    printf("+"); 
    for (i = 0; i < idWidth + 2; i++) printf("-"); 

    printf("+"); 
    for (i = 0; i < nameWidth + 2; i++) printf("-"); 

    printf("+"); 
    for (i = 0; i < priceWidth + 2; i++) printf("-"); 

    printf("+"); 
    for (i = 0; i < quanlityWidth + 2; i++) printf("-"); 

    printf("+\n"); 
}

// * In danh sách sản phẩm dưới dạng bảng với độ rộng co giãn 
void printProductTable(Product listProducts[], int count) {
    if (count == 0) {
        setColor(COLOR_YELLOW);
        printf("\t\t[Notice: No product found]\n"); 
        setColor(COLOR_DEFAULT);
        return; 
    }

    // Độ dài của các tiêu đề cột 
    int idWidth = strlen("ID");
    int nameWidth = strlen("Name");
    int priceWidth = strlen("Price");
    int quantityWidth = strlen("Quantity");

    char buffer[100]; 
    // Duyệt qua từng sản phầm, lấy độ dài lớn nhất của các thuộc tính của nó để xử lí tiếp 
    int i;
    for (i = 0; i < count; i++) {
        int length; 

        length = snprintf(buffer, sizeof(buffer), "%d", listProducts[i].id); 
        if (length > idWidth) {
            idWidth = length; 
        }

        length = strlen(listProducts[i].name); 
        if (length > nameWidth) {
            nameWidth = length; 
        }

        length = snprintf(buffer, sizeof(buffer), "%.2f", listProducts[i].price); 
        if (length > priceWidth) {
            priceWidth = length; 
        }

        length = snprintf(buffer, sizeof(buffer), "%d", listProducts[i].quantity);
        if (length > quantityWidth) {
            quantityWidth = length; 
        }
    } 

    printSeparator(idWidth, nameWidth, priceWidth, quantityWidth); 

    // Các chữ tiêu đề 
    printf("| %-*s | %-*s | %-*s | %-*s |\n", idWidth, "ID", nameWidth, "Name", priceWidth, "Price", quantityWidth, "Quantity"); 

    printSeparator(idWidth, nameWidth, priceWidth, quantityWidth); 

    // Thông tin các sinh viên 
    for (i = 0 ; i < count; i++) {
        printf("| %-*d | %-*s | %-*.2f | %-*d |\n",
               idWidth, listProducts[i].id,
               nameWidth, listProducts[i].name,
               priceWidth, listProducts[i].price,
               quantityWidth, listProducts[i].quantity);
    }

    // Gạch ngang 
    printSeparator(idWidth, nameWidth, priceWidth, quantityWidth); 

    setColor(COLOR_BLUE);
    printf("\t[Total: %d products]\n", count);
    setColor(COLOR_DEFAULT);
}