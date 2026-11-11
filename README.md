# E-Commerce Order Dispatch and Return Tracker

## Project Information
* **Engineering Domain:** Inventory and Warehouse Management
* **Student Name:** Sarang Shrihari Gaikwad
* **Roll Number:** 612505087
* **Division / Batch:** SY B.Tech Electrical

## Problem Statement
In small online retail businesses, managing order dispatches, deliveries, and returns using manual spreadsheets leads to frequent errors, lost packages, and delayed customer refunds. The proposed software provides a lightweight, automated C-based tracking system to easily log new orders, update their transit status, and generate immediate reports on returned merchandise to streamline inventory recovery.

## Features
* Add new orders (ID, Item Name, and Status).
* Prevent duplicate order IDs and validate inputs.
* Update order statuses (Pending, Dispatched, Delivered, Returned).
* Generate specific reports for returned items.
* Persistent data storage using file handling.

## Build and Run Instructions
**Prerequisites:** GCC compiler, Make, Google Test (gTest)

* **Build:** `make all`
* **Run:** `make run`
* **Test:** `make test`
* **Clean:** `make clean`