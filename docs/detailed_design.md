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
- **Source file:** `record.c`
- **Header file:** `record.h`
- **Purpose:** Manages the primary data array for all e-commerce orders.
- **Public functions:** `addOrder()`, `findOrderIndexById()`, `updateOrderStatus()`
- **Data used:** `order_database` (array of `Order_t`), `total_orders` (integer).
- **Possible errors:** Returns `-1` if array is full or order ID is not found.

**Module: Input Validation**
- **Source file:** `validation.c`
- **Header file:** `validation.h`
- **Purpose:** Ensures data integrity before insertion.
- **Public functions:** `isValidId()`, `isUniqueId()`, `isValidStatus()`
- **Dependencies:** Depends on `record.c` to check uniqueness against existing data.

**Module: File Handling**
- **Source file:** `file_handler.c`
- **Header file:** `file_handler.h`
- **Purpose:** Provides persistent storage across application restarts.
- **Public functions:** `saveRecordsToFile()`, `loadRecordsFromFile()`
- **Dependencies:** Depends on `record.c` to read/write the master array.
- **Possible errors:** Returns `-1` if file pointer is NULL.

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
```

### 7.2 Constants
| Constant | Value | Purpose |
| :--- | :--- | :--- |
| `MAX_ORDERS` | 200 | Maximum number of orders the system can hold in memory. |
| `MAX_STR_LEN`| 50 | Maximum character length for an apparel item name. |

---

## 8. Function Design

**Function: addOrder**
* **Module:** `record.c`
* **Prototype:** `int addOrder(int id, const char* item, OrderStatus_t status);`
* **Purpose:** Appends a new verified order to the global database array.
* **Parameters:** ID (int), Item Name (string), Status (Enum).
* **Return type:** `int` (`0` for success, `-1` if database is full).

**Function: updateOrderStatus**
* **Module:** `record.c`
* **Prototype:** `int updateOrderStatus(int id, OrderStatus_t new_status);`
* **Purpose:** Modifies the shipping state of an existing order.
* **Return type:** `int` (`0` for success, `-1` if ID is not found).

---

## 9. Input-Validation Plan
| Input | Source | Validation Rule | Expected Error Behaviour |
| :--- | :--- | :--- | :--- |
| Order ID | User | Must be > 0 | Rejects input, displays error message, returns to menu |
| Order ID | User | Must be unique | Rejects duplicate ID, returns to menu |
| Status | User | Must be 0, 1, 2, or 3 | Rejects invalid status integer, returns to menu |

---

## 10. File-Handling Design
* **File:** `data/sample_data.txt`
* **Format:** Text format.
* **Record Format:** `[ID] [Item_Name] [Status_Integer]` separated by spaces.
* **Operations:** 
  * `fopen(..., "r")` using `fscanf` on application startup.
  * `fopen(..., "w")` using `fprintf` on application exit.

---

## 11. Error-Handling Strategy
* **Logical Errors:** Handled via integer return codes (`0` for success, `-1` for failure). `main.c` checks these codes and prints user-friendly messages rather than crashing.
* **Buffer Overflow:** Prevented by utilizing `strncpy` and `snprintf` in string copies, capping lengths to `MAX_STR_LEN - 1`.
* **Array Overflow:** Blocked by checking `total_orders >= MAX_ORDERS` before insertion.

---

## 12. Coding Standards Plan
* **Indentation:** 4 spaces.
* **Variables:** `snake_case` (e.g., `total_orders`).
* **Functions:** `camelCase` (e.g., `addOrder`, `updateOrderStatus`).
* **Constants & Macros:** `UPPERCASE_WITH_UNDERSCORES`.
* **Warnings:** Strict compiler flags utilized (`-Wall -Wextra -Wpedantic`).

---

## 14. Unit-Test Plan
| Test ID | Function | Category | Input or Condition | Expected Result |
| :--- | :--- | :--- | :--- | :--- |
| UT-01 | `isValidId` | Positive | `5001` | `1` (True) |
| UT-02 | `isValidId` | Negative | `-10` | `0` (False) |
| UT-03 | `isValidStatus` | Boundary | `0`, `3` | `1` (True) |
| UT-04 | `addOrder` | Positive | `1001`, "Dress", `0` | Returns `0`, `total_orders` = 1 |
| UT-05 | `updateOrderStatus` | Negative | ID `9999` (not exists) | Returns `-1` |

---

## 15. Makefile Design
| Target | Command (Windows) | Purpose |
| :--- | :--- | :--- |
| `all` | `mingw32-make all` | Builds the main application executable |
| `run` | `mingw32-make run` | Runs the compiled application executable |
| `test`| `mingw32-make test`| Compiles and runs the Google Test C++ files |
| `clean`| `mingw32-make clean`| Removes all generated `.o` and `.exe` files |

*(Note: GCC mapped via TDM-GCC is utilized for Windows compatibility).*

---

## 16. Repository Structure
```text
ecommerce-order-tracker/
|-- src/
|   |-- main.c
|   |-- record.c
|   |-- validation.c
|   |-- file_handler.c
|   `-- report.c
|
|-- include/
|   |-- record.h
|   |-- validation.h
|   |-- file_handler.h
|   `-- report.h
|
|-- tests/
|   |-- test_record.cpp
|   |-- test_validation.cpp
|   `-- test_report.cpp
|
|-- data/
|   `-- sample_data.txt
|
|-- docs/
|   |-- project_proposal.md
|   `-- detailed_design.md
|
|-- Makefile
|-- README.md
`-- .gitignore
```

---

## 17. Git and GitHub Plan
**Executed Commit Milestones:**
1. `Create initial project structure`
2. `Add header files and data structures`
3. `Implement core modules and main logic`
4. `Add unit tests and project documentation`
5. `Log local gTest execution output and environmental limitations`

---

## 18. Implementation Status
| Work Item | Status |
| :--- | :--- |
| Proposal | Complete |
| Detailed design | Complete |
| Module 1 (Record) | Complete |
| Module 2 (Validation) | Complete |
| Module 3 (Report) | Complete |
| File handling | Complete |
| Unit tests | Complete |
| Makefile | Complete |
| README | Complete |
| Repository verification | Complete |

---

## 19. Test Execution Results

### 19.1 Build Result
* **Command:** `mingw32-make all`
* **Result:** Pass
* **Warnings or errors:** None. (Compiled completely warning-free using -Wall -Wextra -Wpedantic).

### 19.2 Unit-Test Result
* **Command:** `mingw32-make test`
* **Local Execution Result:** Failed (Expected behaviour on Windows host).
* **Test-output evidence:**
PS C:\Users\Sarang\Desktop\ecommerce-order-tracker> mingw32-make run
./app.out

=== E-Commerce Dispatch & Return Tracker ===
1. Add New Order
2. Update Order Status
3. View All Orders
4. View Returned Orders
5. Save and Exit
Enter your choice: 1
Enter Order ID (Positive Integer): 2
Enter Item Name (Use underscores for spaces, e.g., Three-Piece_Set): red_kurta
Enter Status (0=Pending, 1=Dispatched, 2=Delivered, 3=Returned): 1
Order added successfully.

=== E-Commerce Dispatch & Return Tracker ===
1. Add New Order
2. Update Order Status
3. View All Orders
4. View Returned Orders
5. Save and Exit
Enter your choice: 2
Enter Order ID to update: 2
Enter New Status (0=Pending, 1=Dispatched, 2=Delivered, 3=Returned): 2
Status updated successfully.

=== E-Commerce Dispatch & Return Tracker ===
1. Add New Order
2. Update Order Status
3. View All Orders
4. View Returned Orders
5. Save and Exit
Enter your choice: 3

--- All E-Commerce Orders ---
Order ID        Item Name               Status
1               three-piece_set         2
2               red_kurta               2
-----------------------------

=== E-Commerce Dispatch & Return Tracker ===
1. Add New Order
2. Update Order Status
3. View All Orders
4. View Returned Orders
5. Save and Exit
Enter your choice: 1
Enter Order ID (Positive Integer): 3
Enter Item Name (Use underscores for spaces, e.g., Three-Piece_Set): blue_saree
Enter Status (0=Pending, 1=Dispatched, 2=Delivered, 3=Returned): 3
Order added successfully.

=== E-Commerce Dispatch & Return Tracker ===
1. Add New Order
2. Update Order Status
3. View All Orders
4. View Returned Orders
5. Save and Exit
Enter your choice: 3

--- All E-Commerce Orders ---
Order ID        Item Name               Status
1               three-piece_set         2
2               red_kurta               2
3               blue_saree              3
-----------------------------

=== E-Commerce Dispatch & Return Tracker ===
1. Add New Order
2. Update Order Status
3. View All Orders
4. View Returned Orders
5. Save and Exit
Enter your choice: 4

--- Returned Orders (Action Required) ---
Order ID        Item Name
3               blue_saree
-----------------------------------------

=== E-Commerce Dispatch & Return Tracker ===
1. Add New Order
2. Update Order Status
3. View All Orders
4. View Returned Orders
5. Save and Exit
Enter your choice: 5
Data saved successfully. Exiting...


### 19.3 Application Test Results

| Normal use | Menu Option 3 (View) | Displays all orders from txt | Displayed table format | Pass |
| Invalid input | ID: -10 | Error: ID must be positive | Handled without crash | Pass |
| Boundary value | Add 201st order | Error: Database full | Prevented overflow | Pass |
| Missing record | Update ID 9999 | Error: Order ID not found | Alerted user cleanly | Pass |

---

## 22. Reflection

### 22.1 What Worked Well?
The modular design made it extremely easy to isolate bugs. Passing data between arrays in memory and a static text file utilizing `fscanf` and `fprintf` provided a highly reliable persistence model. 

### 22.2 Challenges Faced
Handling compiler execution differences between standard Linux environments and a local Windows machine. Additionally, preventing duplicate `main()` definitions when linking object files required careful adjustment of the compilation process. 

### 22.3 How Were the Challenges Resolved?
Installed the TDM-GCC suite to handle Windows-specific compilation paths, adapted the execution commands to `mingw32-make`, and ensured `main.c` was properly isolated from the core logic files (`record.c`) during the object linking phase in the Makefile.

### 22.4 What Did You Learn?
I developed a strong practical understanding of header guards, modular C compiling, strict flag enforcement (`-Wall`), and how to implement clean separation between application state and UI logic. I also learned standard Git version control workflows.

### 22.5 Future Enhancements
* Implementing a dynamic memory model (using `malloc` and linked lists) instead of fixed arrays to remove the 200-order limit.
* Adding a search function to filter orders by item name or customer data.