#include <stdio.h>
#include "report.h"
#include "record.h"

void printAllOrders(void) {
    printf("\n--- All E-Commerce Orders ---\n");
    printf("Order ID\tItem Name\t\tStatus\n");
    for (int i = 0; i < total_orders; i++) {
        printf("%d\t\t%s\t\t%d\n", order_database[i].order_id, 
               order_database[i].item_name, 
               order_database[i].status);
    }
    printf("-----------------------------\n");
}

void printReturnedOrders(void) {
    printf("\n--- Returned Orders (Action Required) ---\n");
    printf("Order ID\tItem Name\n");
    int count = 0;
    for (int i = 0; i < total_orders; i++) {
        if (order_database[i].status == STATUS_RETURNED) {
            printf("%d\t\t%s\n", order_database[i].order_id, order_database[i].item_name);
            count++;
        }
    }
    if (count == 0) {
        printf("No returned orders pending.\n");
    }
    printf("-----------------------------------------\n");
}