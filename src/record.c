#include <string.h>
#include "record.h"

Order_t order_database[MAX_ORDERS];
int total_orders = 0;

int addOrder(int id, const char* item, OrderStatus_t status) {
    if (total_orders >= MAX_ORDERS) {
        return -1; 
    }
    
    order_database[total_orders].order_id = id;
    strncpy(order_database[total_orders].item_name, item, MAX_STR_LEN - 1);
    order_database[total_orders].item_name[MAX_STR_LEN - 1] = '\0';
    order_database[total_orders].status = status;
    
    total_orders++;
    return 0;
}

int findOrderIndexById(int id) {
    for (int i = 0; i < total_orders; i++) {
        if (order_database[i].order_id == id) {
            return i;
        }
    }
    return -1;
}

int updateOrderStatus(int id, OrderStatus_t new_status) {
    int index = findOrderIndexById(id);
    if (index != -1) {
        order_database[index].status = new_status;
        return 0;
    }
    return -1;
}