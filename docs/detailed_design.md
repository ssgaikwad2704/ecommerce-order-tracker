# Detailed Software Design

## 5. High-Level Architecture
The software is organized into modules to ensure separation of concerns:
- **User Interface:** `main.c` (Handles menu and raw inputs)
- **Application Data:** `record.c` (Manages the struct array)
- **Validation:** `validation.c` (Ensures data integrity)
- **File IO:** `file_handler.c` (Reads/Writes to `data/sample_data.txt`)
- **Reporting:** `report.c` (Filters and prints data to console)

### 5.1 Architecture Diagram
*(Saved in repository as `docs/architecture.png`)*
User -> `main.c` -> `validation.c` -> `record.c` <-> `file_handler.c` <-> `data/sample_data.txt`

### 5.2 High-Level Workflow
1. Application Start.
2. `file_handler.c` reads existing orders from `data/sample_data.txt` into memory.
3. `main.c` displays the main menu loop.
4. User selects an option (e.g., Add Order).
5. User enters data; `validation.c` checks for positive integers, valid status, and unique IDs.
6. `record.c` updates the internal array of structures.
7. Upon selecting "Save and Exit", `file_handler.c` writes the updated array back to `data/sample_data.txt`.
8. Application Exit.

---

## 6. Module Design

### 6.1 Module Summary
| Module Name | Source File | Header File | Responsibility |
| :--- | :--- | :--- | :--- |
| Main application | `main.c` | Not applicable | Controls the high-level application flow and menu |
| Record management | `record.c` | `record.h` | Stores and modifies the order array |
| Input validation | `validation.c` | `validation.h` | Prevents invalid or duplicate data entries |
| File handling | `file_handler.c`| `file_handler.h` | Loads and saves data to text files |
| Report generation | `report.c` | `report.h` | Formats and displays data to the console |

### 6.2 Detailed Module Description

**Module: Record Management**
* **Source file:** `record.c`
* **Header file:** `record.h`
* **Purpose:** Manages the primary data array for all e-commerce orders.
* **Public functions:** `addOrder()`, `findOrderIndexById()`, `updateOrderStatus()`
* **Data used:** `order_database` (array of `Order_t`), `total_orders` (integer).
* **Possible errors:** Returns `-1` if array is full or order ID is not found.

**Module: Input Validation**
* **Source file:** `validation.c`
* **Header file:** `validation.h`
* **Purpose:** Ensures data integrity before insertion.
* **Public functions:** `isValidId()`, `isUniqueId()`, `isValidStatus()`
* **Dependencies:** Depends on `record.c` to check uniqueness against existing data.

**Module: File Handling**
* **Source file:** `file_handler.c`
* **Header file:** `file_handler.h`
* **Purpose:** Provides persistent storage across application restarts.
* **Public functions:** `saveRecordsToFile()`, `loadRecordsFromFile()`
* **Dependencies:** Depends on `record.c` to read/write the master array.
* **Possible errors:** Returns `-1` if file pointer is NULL.

---

## 7. Data Design

### 7.1 Structure and Enumeration Definitions
**Main Structure:**
```c
typedef enum {
    STATUS_PENDING = 0,
    STATUS_DISPATCHED = 1,
    STATUS_DELIVERED = 2,
    STATUS_RETURNED = 3
} OrderStatus_t;

typedef struct {
    int order_id;
    char item_name[50];
    OrderStatus_t status;
} Order_t;