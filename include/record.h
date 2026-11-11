#ifndef RECORD_H
#define RECORD_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ORDERS 200
#define MAX_STR_LEN 50

typedef enum {
    STATUS_PENDING = 0,
    STATUS_DISPATCHED = 1,
    STATUS_DELIVERED = 2,
    STATUS_RETURNED = 3
} OrderStatus_t;

typedef struct {
    int order_id;
    char item_name[MAX_STR_LEN];
    OrderStatus_t status;
} Order_t;

extern Order_t order_database[MAX_ORDERS];
extern int total_orders;

int addOrder(int id, const char* item, OrderStatus_t status);
int findOrderIndexById(int id);
int updateOrderStatus(int id, OrderStatus_t new_status);

#ifdef __cplusplus
}
#endif

#endif