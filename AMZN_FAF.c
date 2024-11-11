#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


    // Create the parameters for the project. Name, addy (changeable), phone
    // delivery status, change address

typedef struct 
{
    char CustomerName[100];
    char Address[50];
    char PhoneNumber[15];
    bool DeliveryStatus = False;
} Client;

/*

Features to implement: 

-authentication
-delivery status 
-store data into an array 
-case switch menu(order number 1-10 style)
-update records 
-add a new record 

*/


/*
Data must be consistent with formatting. 
Luis Arredondo, 793 Houston St, 75054, 972-783-6457, In Transit

use struct array 
When using structures, to access args via array

strcpy(arr[i].name, strtok)

Two while loops
While Loop (fgets)

strtok(char *str, cons char *delimimter (comma value))
strcpy()
atoi(): converts char array into integer (for numbers)

strcpy, tokenizer, fgets

*/


int main()
{
    char Infilename[20] = {};
    // bool AddressChange = False;
    FILE *CSV_FILE;
    // It would be better to use a txt file. 
    // 
    CSV_FILE = fopen("AMZN_DATA.csv", "r");
    if (CSV_FILE == NULL)
    {
        printf("Error opening file.. \n");
        return 1;
    }

    Client Clients[150];
    int Read, Records = 0;
    do
    {   
        Read = fscanf(CSV_FILE, "");
        &Clients[Records].CustomerName,
        &Clients[Records].Address,
        &Clients[Records].PhoneNumber,
        &Clients[Records].DeliveryStatus);
        if (Read == 4) Records++;

        if (Read != 4 && !feof(CSV_FILE))
        {
            printf("File Format incorrect \n");
            return 1;
        }
    } while(!feof(CSV_FILE));



    char ClientParser[200] = {};
    char Delimiter = ", ";
    StrTok(ClientParser, Delimiter);


      int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Change Address\n");
        printf("2. Change Delivery Status\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
               
                break;
            }
            case 2: {
               
                break;
            }
            case 3: {

                break;
            }
            case 4: {

                break;
            }
            case 5: {

                break;
            }
            case 6: {

                break;
            }
            case 7: {

                break;
            }
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    
    
    /* check parameters for fopen in file handling
    I have to consider exactly what will be put into file handling
    Client files may be generated. using "," as the tockenizer


    Below are Fxn name w parameters
    ChangeAddress and DeliveryStatus do what follows. 
    */


    // ClientInfo = fopen("insert filename here", );


    // ChangeAddress(char A);
    // ChangeDeliveryStatus(char DS);

}