#include <stdio.h>
#include "../include/export.h"
#include "../include/validation.h"
#include "../include/logger.h"
#include "../include/file_io.h"
#include "../include/color.h"

// * Xuất sang filr txt 
void exportTxt(Product listProducts[], int count) {
    FILE *file = fopen("data/products.txt", "w");
    if (file == NULL) {
        setColor(COLOR_RED);
        printf("\t\t[Error: Cannot create products.txt]\n");
        setColor(COLOR_DEFAULT);

        writeLog("EXPORT TXT", "open failed", "FAILED");
        return;
    }

    fprintf(file, "ID | Name | Price | Quantity\n");
    int i; 
    for (i = 0 ; i < count; i++) {
        fprintf(file, "%d | %s | %.2f | %d \n",
                listProducts[i].id, listProducts[i].name, listProducts[i].price, listProducts[i].quantity);
    }

    fclose(file);

    setColor(COLOR_GREEN);
    printf("\t\t[Success: Exported to products.txt]\n");
    setColor(COLOR_DEFAULT);

    writeLog("EXPORT TXT", "data/products.txt", "SUCCESS");
}

// * Xuất sang file csv(excel)
static void exportCsv(Product list[], int count) {
    FILE *fp = fopen("data/products.csv", "w");
    if (fp == NULL) {
        setColor(COLOR_RED);
        printf("\t\t[Error: Cannot create products.csv]\n");
        setColor(COLOR_DEFAULT);
        writeLog("EXPORT CSV", "open failed", "FAILED");
        return;
    }
    
    fprintf(fp, "ID;Name;Price;Quantity\n"); 
    
    int i;
    for (i = 0; i < count; i++) {
        fprintf(fp, "%d;%s;%.2f;%d\n",
                list[i].id, list[i].name, list[i].price, list[i].quantity);
    }
    fclose(fp);

    setColor(COLOR_GREEN);
    printf("\t\t[Success: Exported to products.csv]\n");
    setColor(COLOR_DEFAULT);

    writeLog("EXPORT CSV", "data/products.csv", "SUCCESS");
}

// * Xuất sang file cơ sở sữ liệu sql
void exportSqlite(Product list[], int count) {
    FILE *fp = fopen("data/products.sql", "w");
    if (fp == NULL) {
        setColor(COLOR_RED);
        printf("\t\t[Error: Cannot create products.sql]\n");
        setColor(COLOR_DEFAULT);
        writeLog("EXPORT SQLITE", "open failed", "FAILED");
        return;
    }

    fprintf(fp, "DROP TABLE IF EXISTS Product;\n");
    fprintf(fp, "CREATE TABLE Product (\n"
                "  id INTEGER PRIMARY KEY,\n"
                "  name TEXT NOT NULL,\n"
                "  price REAL NOT NULL,\n"
                "  quantity INTEGER NOT NULL\n"
                ");\n");

    int i;
    for (i = 0; i < count; i++) {
        fprintf(fp, "INSERT INTO Product (id, name, price, quantity) VALUES (%d, '%s', %.2f, %d);\n",
                list[i].id, list[i].name, list[i].price, list[i].quantity);
    }
    fclose(fp);

    setColor(COLOR_GREEN);
    printf("\t\t[Success: Exported to products.sql]\n");
    setColor(COLOR_DEFAULT);
    // printf(">>> Run: sqlite3 data/products.db < data/products.sql (for PowerShell)\n >>> sqlite3 data/products.db < data/products.sql (CMD)\n \n");
    writeLog("EXPORT SQLITE", "data/products.sql", "SUCCESS");
}

// * Option 10: Export Products - menu chức năng xuất dữ liệu sang txt / csv / sqlite
void menuExportProducts(Product listProducts[], int count) {
    if (count == 0) {
        setColor(COLOR_YELLOW);
        printf("\t\t[Notice: No product found]\n"); 
        setColor(COLOR_DEFAULT);
        return; 
    }

    setColor(COLOR_BLUE);
    printf("\n");
    printf("\t\t+-----------------+\n");
    printf("\t\t|   EXPORT MENU   |\n");
    printf("\t\t+-----------------+\n");
    setColor(COLOR_DEFAULT);

    printf("[1]. Export To TXT\n");
    printf("[2]. Export To CSV\n");
    printf("[3]. Export To SQLite\n");
    printf("[0]. Back\n");

    setColor(COLOR_CYAN);
    int choice = inputInt(">> Enter your choice: ", 0, 3);
    setColor(COLOR_DEFAULT);

    switch (choice)
    {
        case 1: exportTxt(listProducts, count); break;
        case 2: exportCsv(listProducts, count); break;
        case 3: exportSqlite(listProducts, count); break;
        case 0: break;
        default: break;
    }
}


