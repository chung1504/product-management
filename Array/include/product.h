#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCTS 1000
#define MAX_NAME_LENGTH 50

typedef struct
{
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Product;

#endif