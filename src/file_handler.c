#include <stdio.h>
#include "file_handler.h"
#include "record.h"

int saveRecordsToFile(const char* filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }
    
    for (int i = 0; i < total_orders; i++) {
        fprintf(fp, "%d %s %d\n", order_database[i].order_id, 
                order_database[i].item_name, 
                order_database[i].status);
    }
    
    fclose(fp);
    return 0;
}

int loadRecordsFromFile(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1; 
    }
    
    total_orders = 0;
    int id, status;
    char item[MAX_STR_LEN];
    
    while (fscanf(fp, "%d %s %d", &id, item, &status) == 3) {
        if (total_orders < MAX_ORDERS) {
            order_database[total_orders].order_id = id;
            snprintf(order_database[total_orders].item_name, MAX_STR_LEN, "%s", item);
            order_database[total_orders].status = (OrderStatus_t)status;
            total_orders++;
        }
    }
    
    fclose(fp);
    return 0;
}