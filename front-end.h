#include <stdio.h>
#include "backend.h"

user u;

void displayFrame(const char* title) {
    int width = 40; // Adjust width for the frame
    printf("\n*");
    for (int i = 0; i < width - 2; i++)
        printf("=");
    printf("*\n");

    printf("|%*s%*s|\n", ((width - 2 + strlen(title)) / 2), title, (width - 2 - (width - 2 + strlen(title)) / 2), "");

    printf("*");
    for (int i = 0; i < width - 2; i++)
        printf("=");
    printf("*\n");
}

void main_menue() 
{
    int opt;
    while (1) {
        displayFrame("Udhari Management System");
        printf("1. View UDHARI\n2. Mark Paid\n3. Create Udhari\n4. Exit\nOption: ");
        scanf("%d", &opt);
        if (opt > 3)
            break;

        switch (opt) {
            case 1:
                vUdhari();
                break;
            case 2:
                Markpaid();
                break;
            case 3:
                createNewRecord();
                break;
        }
    }
}

void login() {
    displayFrame("Login");
    printf("1. Create User\n2. Login\n3. Forgot Login Details\n4. Exit\nOption: ");
    int opt;
    while (1) {
        scanf("%d", &opt);
        if (opt > 3)
            break;
        switch (opt) {
            case 1:
                create_User();
                break;
            case 2:
                printf("\nEnter User ID: ");
                scanf("%d", &u.ID);
                printf("Enter Password: ");
                scanf("%s", &u.pass);
                if (iscrct(u.pass) && sID(u.ID) == 0) {
                    printf("\n-- Invalid Credential --\n");
                } else {
                    main_menue();
                }
                break;
            case 3:
                Fcread();
                break;
        }
    }
}
