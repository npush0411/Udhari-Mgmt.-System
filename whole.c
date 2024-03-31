#include <stdio.h>
#include <ctype.h>
#include <string.h>

FILE *fu;
FILE *frec;

typedef struct record {
    int ID;
    char name[15];
    int amount;
    long int entry;
    long int dead;
    int flg;
} record;

typedef struct user {
    int ID;
    char name[20];
    char pass[10];
} user;

user x;

void initDB() {
    fu = fopen("User.dat", "r+b");
    if (fu == NULL) {
        fu = fopen("User.dat", "wb");
        fclose(fu);
        fu = fopen("User.dat", "r+b");
    }
    frec = fopen("Rec.dat", "r+b");
    if (frec == NULL) {
        frec = fopen("Rec.dat", "wb");
        fclose(frec);
        frec = fopen("Rec.dat", "r+b");
    }
}

int iscrct(char *pass) {
    return !strcmp(pass, x.pass);
}

int isValid(const char *password) {
    int hasUppercase = 0;
    int hasSpecialChar = 0;
    int hasNumericChar = 0;
    int length = strlen(password);
    
    if (length < 8)
        return 0;

    for (int i = 0; password[i] != '\0'; i++) {
        char c = password[i];
        if (isupper(c))
            hasUppercase = 1;
        else if (isdigit(c))
            hasNumericChar = 1;
        else if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*')
            hasSpecialChar = 1;

        if (hasUppercase && hasNumericChar && hasSpecialChar)
            return 1;
    }
    return 0;
}

int sRec(int id) {
    rewind(frec);
    record t;
    while (1) {
        if (feof(frec))
            break;
        fread(&t, sizeof(record), 1, frec);
        if (t.ID == id)
            break;
    }
    return t.ID == id;
}

void vUdhari() {
    rewind(frec);
    record t;
    while (fread(&t, sizeof(record), 1, frec))
        printf("\nID : %d\tName : %s\nAmount : %d\nEntry Date : %ld\t Deadline : %ld\n Status : %s\n", t.ID, t.name, t.amount, t.entry, t.dead, (t.flg ? "Paid" : "Udhari -_-"));
}

void Markpaid() {
    int id;
    record d;
    printf("\nEnter Record ID : ");
    scanf("%d", &id);
    if (sRec(id)) {
        fseek(frec, -sizeof(record), SEEK_CUR);
        fread(&d, sizeof(record), 1, frec);
        if (d.flg)
            printf("\n-- Already Paid --\n");
        else {
            d.flg = 1;
            printf("\n-- Marked Paid --\n");
            fseek(frec, -sizeof(record), SEEK_CUR);
            fwrite(&d, sizeof(record), 1, frec);
        }
    } else
        printf("\n-- ID not Found --\n");
}

void createNewRecord() {
    record t;
    printf("\n-- Enter Record ID : ");
    scanf("%d", &t.ID);
    if (sRec(t.ID)) {
        printf("\n-- ID Exits --\n-- Record Creation Failed --\n");
        return;
    }
    printf("\n-- Enter Name : ");
    scanf("%s", t.name);
    printf("-- Enter Amount : ");
    scanf("%d", &t.amount);
    printf("\n\n-- Date Entry format - DDMMYY --\n\n");
    printf("Enter Entry Date : ");
    scanf("%ld", &t.entry);
    printf("\nEnter Deadline Date : ");
    scanf("%ld", &t.dead);
    t.flg = 0;
    fseek(frec, 0, SEEK_END);
    fwrite(&t, sizeof(record), 1, frec);
}

int sUser(int id) {
    user t;
    int flg = 0;
    int a = 1;
    rewind(fu);
    while (a) {
        if (t.ID == id) {
            flg = 1;
            x = t;
            break;
        }
        a = fread(&t, sizeof(user), 1, fu);
    }
    return flg;
}

void create_User() {
    user temp;
    printf("\n-- Enter User ID : ");
    scanf("%d", &temp.ID);
    if (sUser(temp.ID)) {
        printf("\n-- ID Exits --\n-- Record Creation Failed --\n");
        return;
    }
    printf("\n-- Enter User Name : ");
    scanf("%s", temp.name);
    while (1) {
        printf("\n-- Enter Password : ");
        scanf("%s", temp.pass);
        if (isValid(temp.pass))
            break;
        else
            printf("\n-- Enter a Valid Password --\n");
    }
    fseek(fu, 0, SEEK_END);
    fwrite(&temp, sizeof(user), 1, fu);
}

void Fcread() {
    user t;
    printf("\nEnter User ID : ");
    scanf("%d", &t.ID);
    if (sUser(t.ID)) {
        printf("\nEnter Username : ");
        scanf("%s", t.name);
        while (1) {
            printf("\nEnter Password : ");
            scanf("%s", t.pass);
            if (isValid(t.pass))
                break;
            else
                printf("\n-- Password Doesn't meet requirements --\n-- Please Retype --\n");
        }
        fseek(fu, -sizeof(user), SEEK_CUR);
    } else
        printf("\n-- User not Found --\n");
}

void delUdhari(int id) {
    remove("Rec.dat");
    fclose(fu);
    fclose(frec);
    initDB();
}

void delUser(int id) {
    remove("User.dat");
    fclose(fu);
    fclose(frec);
    initDB();
}

user u;

void main_menue() {
    int opt;
    while (1) {
        printf("\n-- Udhari Management System --\n1. View UDHARI\n2. Mark Paid\n3. Create Udhari\n4. Delete Record.\n5. Exit\nOption : ");
        scanf("%d", &opt);
        if (opt > 4)
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
            case 4:
                printf("\nEnter ID : ");
                scanf("%d", &opt);
                delUdhari(opt);
                break;
        }
    }
}

void login() {
    printf("\nEnter User ID : ");
    scanf("%d", &u.ID);
    if (sUser(u.ID) == 0) {
        printf("\n-- Invalid ID --\n");
        return;
    }
    printf("\nEnter Password : ");
    scanf("%s", u.pass);
    if (iscrct(u.pass))
        main_menue();
    else
        printf("\n-- Invalid Credentials --\n");
}

void login_menue() {
    int opt;
    while (1) {
        printf("\n-- Login --\n1. Create User\n2. Login\n3. Forgot Login Details\n4. Delete User.\n5. Exit\nOption : ");
        scanf("%d", &opt);
        if (opt > 4)
            break;
        switch (opt) {
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

int main() {
    printf("\n-- Welcome to Udhari Management system ! --\n");

    initDB();

    login_menue();

    fclose(fu);
    fclose(frec);
    return 0;
}
