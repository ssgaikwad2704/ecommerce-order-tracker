#include <stdio.h>
#include <stdlib.h>
#include "record.h"
#include "validation.h"
#include "file_handler.h"
#include "report.h"

#define DATA_FILE "data/sample_data.txt"

void displayMenu() {
    printf("\n=== E-Commerce Dispatch & Return Tracker ===\n");
    printf("1. Add New Order\n");
    printf("2. Update Order Status\n");
    printf("3. View All Orders\n");
    printf("4. View Returned Orders\n");
    printf("5. Save and Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, id, statusInput;
    char itemName[MAX_STR_LEN];

    loadRecordsFromFile(DATA_FILE);

    while (1) {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter Order ID (Positive Integer): ");
                scanf("%d", &id);
                if (!isValidId(id) || !isUniqueId(id)) {
                    printf("Error: ID must be positive and unique.\n");
                    break;
                }
                printf("Enter Item Name (Use underscores for spaces, e.g., Three-Piece_Set): ");
                scanf("%s", itemName);
                
                printf("Enter Status (0=Pending, 1=Dispatched, 2=Delivered, 3=Returned): ");
                scanf("%d", &statusInput);
                
                if (!isValidStatus(statusInput)) {
                    printf("Error: Invalid status.\n");
                    break;
                }
                
                if (addOrder(id, itemName, (OrderStatus_t)statusInput) == 0) {
                    printf("Order added successfully.\n");
                } else {
                    printf("Error: Database full.\n");
                }
                break;
            case 2:
                printf("Enter Order ID to update: ");
                scanf("%d", &id);
                printf("Enter New Status (0=Pending, 1=Dispatched, 2=Delivered, 3=Returned): ");
                scanf("%d", &statusInput);
                if (isValidStatus(statusInput)) {
                    if (updateOrderStatus(id, (OrderStatus_t)statusInput) == 0) {
                        printf("Status updated successfully.\n");
                    } else {
                        printf("Error: Order ID not found.\n");
                    }
                } else {
                    printf("Error: Invalid status choice.\n");
                }
                break;
            case 3:
                printAllOrders();
                break;
            case 4:
                printReturnedOrders();
                break;
            case 5:
                saveRecordsToFile(DATA_FILE);
                printf("Data saved successfully. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}