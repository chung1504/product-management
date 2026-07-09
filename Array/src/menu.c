#include <stdio.h> 
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/color.h"

void showMainMenu() {
    printf("\n");
    setColor(COLOR_BLUE);
    printf("+=======================================================\n");
    printf("|               PRODUCT MANAGEMENT SYSTEM              |\n");
    printf("+=======================================================\n");
    setColor(COLOR_DEFAULT);
    printf("|  [01] Write Products      |  [07] Search Product     |\n");
    printf("|  [02] Append Products     |  [08] Sort Products      |\n");
    printf("|  [03] Read Products       |  [09] Statistics         |\n");
    printf("|  [04] Modify Product      |  [10] Export Products    |\n");
    printf("|  [05] Insert Product      |  [11] View Logs          |\n");
    printf("|  [06] Delete Product      |  [12] Clear Screen       |\n");
    printf("+---------------------------+--------------------------+\n");
    printf("|                   [00] EXIT SYSTEM                   |\n");
    printf("+------------------------------------------------------+\n");

}

// * Clear screen 
void clearScreen() {
    #ifdef _WIN32
        system("cls"); 
    #else 
        system("clear");
    #endif
}