#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void getName(char *buffer[]);
bool Login(FILE *fptr, char *userbuff[]);
bool Register(FILE *fptr, char *userbuff[]);
void LoginSuccess(FILE *fptr, char *userbuff[]);

int main()

{
    //Choose login or registration
    //Login: Ask for username
    //Open username file or return -1
    //Ask for password, check. Return yes/no

    //Registration: Ask for username
    //If exists return -1
    //Make new file with username
    //Ask for password, write to username file

    //Exit
    int Choice;
    FILE *fptr;
    printf("1.) Login\n2.) Register\nOption: ");
    scanf("%1d", &Choice);

    char userbuff[15];
    printf("Username: ");
    scanf("%15s", userbuff);

    switch (Choice)
    {
    case 1: //Login
        if (Login(fptr, userbuff) == 0)
        {
            LoginSuccess(fptr, userbuff);
            return 0; //Success
        }
        else
        {
            return -1; //Failure
        }
        break;
    case 2: //Register
        if (Register(fptr, userbuff) == 0)
        {
            return 0; //Success
        }
        else
        {
            return -1; //Failure
        }
        break;
    default:
        printf("Error, option unknown. Exiting...\n\n");
        return -1;
        break;
    }
}

bool Login(FILE *fptr, char *userbuff[])
{
    if (access(userbuff, F_OK) == 0)
    {
        char passbuff[15];
        char password[15];

        printf("Enter Password: ");
        scanf("%15s", &password);

        fptr = fopen(userbuff, "r");
        fgets(passbuff, 15, fptr);
        fclose(fptr);
        if (strcmp(password, passbuff) == 0)
        {
            printf("Password accepted, welcome %s\n\n", userbuff);
            return 0;
        }
        else
        {
            printf("Password denied, unwelcome %s\n\n", userbuff);
            return -1;
        }

    }
    else
    {
        printf("Error, User does not exist. Exiting...\n\n");
        return -1;
    }
}

bool Register(FILE *fptr, char *userbuff[])
{
    if ( ! access(userbuff, F_OK) == 0 )
    {
        char passbuff[15];
        printf("Enter password: ");
        scanf("%15s", &passbuff);
        fptr = fopen(userbuff, "w");
        fprintf(fptr, passbuff);
        fclose(fptr);
        return 0;
    }
    else
    {
        printf("Error, user already exists. Exiting...\n\n");
        return -1;
    }
}

void LoginSuccess(FILE *fptr, char *userbuff[])
{
    int Choice;
    printf("1.) Change Password\n2.) Delete Account\n3.) End Session\nOption: ");
    scanf("%d", &Choice);

    switch (Choice)
    {
        case 1: //Change Pass
            char passbuff[15];
            printf("New Password: ");
            scanf("%15s", &passbuff);

            fptr = fopen(userbuff, "w");
            fprintf(fptr, &passbuff);
            fclose(fptr);
            break;
        case 2: //Delete Account
            remove(userbuff);
            printf("Account Deleted.\n\n");
            break;
        case 3: //Exit
        return;
            break;
        default:
        printf("Error, option unknown. Exiting...\n\n");
            break;
    }
    
}