# 1. Project Information
* **Project Title:** E-Commerce Order Dispatch and Return Tracker
* **Engineering Domain:** Inventory and Warehouse Management
* **Student Name:** Sarang Shrihari Gaikwad
* **Roll Number:** 612505087
* **Division / Batch:** SY B.Tech Electrical

# 2. Engineering Scenario
In a small online retail business managing women's apparel (dresses, three-piece sets), tracking order dispatches and returns using manual spreadsheets often leads to errors. Returned packages are frequently misplaced, causing delays in refunds and inventory restocking. The proposed software provides a simple C-based application to digitally track the lifecycle of each order from pending to delivered, while specifically keeping a tight watch on returned packages.

# 3. Project Scope
**In-Scope Features:**
* Adding new order records (ID, Item).
* Updating status (Pending, Dispatched, Delivered, Returned).
* Generating an urgent report for "Returned" items to process inventory.
* Data persistence using simple text files.

**Out-of-Scope Features:**
* Payment gateway integrations.
* GUI (Graphical User Interface).

# 4. Requirements
* **FR-01:** The system shall add a new order record with a unique identifier.
* **FR-02:** The system shall validate all inputs.
* **FR-03:** The system shall update the status of existing orders.
* **NFR-01:** The source code shall compile without warnings (-Wall -Wextra).
* **NFR-02:** Core operations shall be validated using Google Test (gTest).