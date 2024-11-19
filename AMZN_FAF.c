#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// LA start
typedef struct {
    char CustomerName[100];
    char Address[100];
    char PhoneNumber[15];
    bool DeliveryStatus;
} Client;

// Function prototypes
void ChangeAddress(Client *client);
void ChangeDeliveryStatus(Client *client);
void DisplayClientInfo(Client *client);
void AddNewRecord(Client clients[], int *records);
void RemoveRecord(Client clients[], int *records);

int main() {
    FILE *CSV_FILE = fopen("AMZN_DATA.csv", "r");
    if (CSV_FILE == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    Client clients[150];
    int records = 0;

    // Read CSV file
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), CSV_FILE)) {
        char *token = strtok(buffer, ",");
        if (token != NULL) strcpy(clients[records].CustomerName, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(clients[records].Address, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(clients[records].PhoneNumber, token);

        token = strtok(NULL, ",");
        if (token != NULL) {
            clients[records].DeliveryStatus = strcmp(token, "Delivered") == 0;
        }

        records++;
    }
    fclose(CSV_FILE);

    // Menu system
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Change Address\n");
        printf("2. Change Delivery Status\n");
        printf("3. Remove Client ");
        printf("3. Display Client Info\n");
        printf("4. Add New Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int clientIndex;
                printf("Enter client index (0 to %d): ", records - 1);
                scanf("%d", &clientIndex);
                if (clientIndex >= 0 && clientIndex < records) {
                    ChangeAddress(&clients[clientIndex]);
                } else {
                    printf("Invalid index.\n");
                }
                break;
            }
            case 2: {
                int clientIndex;
                printf("Enter client index (0 to %d): ", records - 1);
                scanf("%d", &clientIndex);
                if (clientIndex >= 0 && clientIndex < records) {
                    ChangeDeliveryStatus(&clients[clientIndex]);
                } else {
                    printf("Invalid index.\n");
                }
                break;
            }
            case 3: {
                for (int i = 0; i < records; i++) {
                    DisplayClientInfo(&clients[i]);
                }
                break;
            }
            case 4:
                AddNewRecord(clients, &records);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}

//LA end
//KE start

void ChangeAddress(Client *client) {
    printf("Current Address: %s\n", client->Address);
    printf("Enter new address: ");
    getchar(); // Consume newline
    fgets(client->Address, sizeof(client->Address), stdin);
    client->Address[strcspn(client->Address, "\n")] = '\0'; // Remove newline
    printf("Address updated to: %s\n", client->Address);
}

void ChangeDeliveryStatus(Client *client) {
    printf("Current Delivery Status: %s\n", client->DeliveryStatus ? "Delivered" : "In Transit");
    printf("Enter new status (1 for Delivered, 0 for In Transit): ");
    int status;
    scanf("%d", &status);
    client->DeliveryStatus = status;
    printf("Delivery status updated.\n");
}

void DisplayClientInfo(Client *client) {
    printf("Name: %s\n", client->CustomerName);
    printf("Address: %s\n", client->Address);
    printf("Phone: %s\n", client->PhoneNumber);
    printf("Delivery Status: %s\n", client->DeliveryStatus ? "Delivered" : "In Transit");
    printf("-----------------------------\n");
}

void AddNewRecord(Client clients[], int *records) {
    if (*records >= 150) {
        printf("Client list is full.\n");
        return;
    }
    Client *newClient = &clients[*records];
    printf("Enter Customer Name: ");
    getchar(); // Consume newline
    fgets(newClient->CustomerName, sizeof(newClient->CustomerName), stdin);
    newClient->CustomerName[strcspn(newClient->CustomerName, "\n")] = '\0'; // Remove newline

    printf("Enter Address: ");
    fgets(newClient->Address, sizeof(newClient->Address), stdin);
    newClient->Address[strcspn(newClient->Address, "\n")] = '\0';

    printf("Enter Phone Number: ");
    fgets(newClient->PhoneNumber, sizeof(newClient->PhoneNumber), stdin);
    newClient->PhoneNumber[strcspn(newClient->PhoneNumber, "\n")] = '\0';

    printf("Enter Delivery Status (1 for Delivered, 0 for In Transit): ");
    int status;
    scanf("%d", &status);
    newClient->DeliveryStatus = status;

    (*records)++;
    printf("New record added.\n");
}

void RemoveRecord(Client clients[], int* Records)
{

}


// remove client option
