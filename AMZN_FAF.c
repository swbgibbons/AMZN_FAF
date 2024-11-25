#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// LA start
typedef struct {
    char CustomerName[100];
    char Address[100];
    char ZipCode[15];
    char PhoneNumber[15];
    bool DeliveryStatus;
} Client;

// Function prototypes
void ChangeAddress(Client clients[], int records);
void ChangeDeliveryStatus(Client clients[], int records);
void DisplayClientInfo(Client *client);
void AddNewRecord(Client clients[], int *records);
void RemoveRecord(Client clients[], int *records);
int FindClientIndex(Client clients[], int records, const char *name);
void UpdateCSVFile(Client clients[], int records);

int main() {
    FILE *CSV_FILE = fopen("FAF.csv", "r");
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
        if (token != NULL) strcpy(clients[records].ZipCode, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(clients[records].PhoneNumber, token);

        token = strtok(NULL, ",");
        if (token != NULL) {
            clients[records].DeliveryStatus = strcmp(token, "Delivered\r\n") == 0;
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
        printf("3. Display Client Info\n");
        printf("4. Add New Record\n");
        printf("5. Remove Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                ChangeAddress(clients, records);
                UpdateCSVFile(clients, records);
                break;
            case 2:
                ChangeDeliveryStatus(clients, records);
                UpdateCSVFile(clients, records);
                break;
            case 3:
                for (int i = 0; i < records; i++) {
                    DisplayClientInfo(&clients[i]);
                }
                break;
            case 4:
                AddNewRecord(clients, &records);
                UpdateCSVFile(clients, records);
                break;
            case 5:
                RemoveRecord(clients, &records);
                UpdateCSVFile(clients, records);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}

//LA end
//KE start

void ChangeAddress(Client clients[], int records) {
    char name[100];
    printf("Enter client name: ");
    getchar(); // Consume newline
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline

    int index = FindClientIndex(clients, records, name);
    if (index != -1) {
        printf("Current Address: %s\n", clients[index].Address);
        printf("Enter new address: ");
        fgets(clients[index].Address, sizeof(clients[index].Address), stdin);
        clients[index].Address[strcspn(clients[index].Address, "\n")] = '\0'; // Remove newline

        printf("Current Zip Code: %s\n", clients[index].ZipCode);
        printf("Enter new zip code: ");
        fgets(clients[index].ZipCode, sizeof(clients[index].ZipCode), stdin);
        clients[index].ZipCode[strcspn(clients[index].ZipCode, "\n")] = '\0'; // Remove newline

        printf("Address and zip code updated to: %s, %s\n", clients[index].Address, clients[index].ZipCode);
    } else {
        printf("No record found for %s.\n", name);
    }
}

void ChangeDeliveryStatus(Client clients[], int records) {
    char name[100];
    printf("Enter client name: ");
    getchar(); // Consume newline
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline

    int index = FindClientIndex(clients, records, name);
    if (index != -1) {
        printf("Current Delivery Status: %s\n", clients[index].DeliveryStatus ? "Delivered" : "In Transit");
        printf("Enter new status (1 for Delivered, 0 for In Transit): ");
        int status;
        scanf("%d", &status);
        clients[index].DeliveryStatus = (status == 1);
        printf("Delivery status updated.\n");
    } else {
        printf("No record found for %s.\n", name);
    }
}

void DisplayClientInfo(Client *client) {
    printf("Name: %s\n", client->CustomerName);
    printf("Address: %s\n", client->Address);
    printf("Zip Code: %s\n", client->ZipCode);
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

    printf("Enter Zip Code: ");
    fgets(newClient->ZipCode, sizeof(newClient->ZipCode), stdin);
    newClient->ZipCode[strcspn(newClient->ZipCode, "\n")] = '\0';

    printf("Enter Phone Number: ");
    fgets(newClient->PhoneNumber, sizeof(newClient->PhoneNumber), stdin);
    newClient->PhoneNumber[strcspn(newClient->PhoneNumber, "\n")] = '\0';

    printf("Enter Delivery Status (1 for Delivered, 0 for In Transit): ");
    int status;
    scanf("%d", &status);
    newClient->DeliveryStatus = (status == 1);

    (*records)++;
    printf("New record added.\n");
}

void RemoveRecord(Client clients[], int *records) {
    char name[100];
    printf("Enter client name: ");
    getchar(); // Consume newline
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline

    int index = FindClientIndex(clients, *records, name);
    if (index != -1) {
        for (int i = index; i < *records - 1; i++) {
            clients[i] = clients[i + 1];
        }
        (*records)--;
        printf("Record for %s removed.\n", name);
    } else {
        printf("No record found for %s.\n", name);
    }
}

int FindClientIndex(Client clients[], int records, const char *name) {
    for (int i = 0; i < records; i++) {
        if (strcasecmp(clients[i].CustomerName, name) == 0) {
            return i;
        }
    }
    return -1;
}

void UpdateCSVFile(Client clients[], int records) {
    FILE *CSV_FILE = fopen("FAF.csv", "w");
    if (CSV_FILE == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < records; i++) {
        fprintf(CSV_FILE, "%s,%s,%s,%s,%s\n",
                clients[i].CustomerName,
                clients[i].Address,
                clients[i].ZipCode,
                clients[i].PhoneNumber,
                clients[i].DeliveryStatus ? "Delivered" : "In Transit");
    }

    fclose(CSV_FILE);
    printf("CSV file updated.\n");
}

