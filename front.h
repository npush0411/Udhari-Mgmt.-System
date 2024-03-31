#include <stdio.h>
#include "backend.h"

user u;

void main_menue()
{
    int opt;
    while(1)
    {
        printf("\n-- Udhari Management System --\n1. View UDHARI\n2. Mark Paid\n3. Create Udhari\n4. Delete Record.\n5. Exit\nOption : ");
        scanf("%d", &opt);
        if(opt > 4)
            break;
        switch(opt)
        {
            case 1:
                vUdhari();
                break;
            case 2:
                Markpaid();
                break;
            case 3:
                createNewRecord();
                break;
            case 4:
                printf("\nEnter ID : ");
                scanf("%d", &opt);
                delUdhari(opt);
                break;
        }
    }
}

void login()
{
    printf("\nEnter User ID : ");
    scanf("%d", &u.ID);
    if(sUser(u.ID) == 0)
    {
        printf("\n-- Invalid ID --\n");
        return;
    }
    printf("\nEnter Password : ");
    scanf("%s", u.pass);
    if(iscrct(u.pass))
        main_menue();
    else
        printf("\n-- Invalid Credentials --\n");
}

void login_menue()
{
    int opt;
    while(1)
    {
        printf("\n-- Login --\n1. Create User\n2. Login\n3. Forgot Login Details\n4. Delete User.\n5. Exit\nOption : ");
        scanf("%d", &opt);
        if(opt > 4)
            break;
        switch(opt)
        {
            case 1:
                create_User();
                break;
            case 2:
                login();
                break;
            case 3: 
                Fcread();
                break;
            case 4:
                printf("\nEnter ID : ");
                scanf("%d", &opt);
                delUser(opt);
                break;
        }
    }
}