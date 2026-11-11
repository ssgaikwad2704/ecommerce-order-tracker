# 1. High-Level Architecture
The software is organized into modules to ensure separation of concerns:
* **User Interface:** `main.c` (Handles menu and raw inputs)
* **Application Data:** `record.c` (Manages the struct array)
* **Validation:** `validation.c` (Ensures data integrity)
* **File IO:** `file_handler.c` (Reads/Writes to `data/sample_data.txt`)
* **Reporting:** `report.c` (Filters and prints data to console)

# 2. Data Design
**Main Structure:**
```c
typedef struct {
    int order_id;
    char item_name[50];
    OrderStatus_t status;
} Order_t;

ypedef enum {
    STATUS_PENDING = 0,
    STATUS_DISPATCHED = 1,
    STATUS_DELIVERED = 2,
    STATUS_RETURNED = 3
} OrderStatus_t;    