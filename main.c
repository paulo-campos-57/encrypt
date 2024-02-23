#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "library.h"

int main()
{
    clearScreen();
    int running = 1;
    printf("\033[1;32m");
    while (running) {
        if (verifyLogin()) {
            char *userName;
            size_t len = 0;
            printWithDelay("Welcome to the encrypt\n");
            printWithDelay("Enter your data to finish your register\n");
            printWithDelay("Type here your username: ");
            getline(&userName, &len, stdin);
            if (userName[strlen(userName) - 1] == '\n')
                userName[strlen(userName) - 1] = '\0';
            printWithDelay("Welcome ");
            printWithDelay(userName);
            printf("\n");
            saveUserName(userName);
            printWithDelay("Your username is saved\n");
            sleep(1);
            clearScreen();
            char *password;
            size_t passwordLen = 0;
            printWithDelay("Define a password: ");
            getline(&password, &passwordLen, stdin);
            if (password[strlen(password) - 1] == '\n')
                password[strlen(password) - 1] = '\0';
            savePassword(password);
            printWithDelay("Your password is saved\n");
            sleep(1);
            clearScreen();
            printWithDelay("All your data is saved. Now you can login to the encrypt.\n");
            activateLogin();
            pauseSystem();
            clearScreen();
        } else if (!verifyLogin()) {
            char *user = getUsername();
            char *pass = getPassword();
            char *check;
            size_t checkLen = 0;
            printWithDelay("Welcome ");
            printWithDelay(user);
            printf("\n");
            while (1) {
                printWithDelay("Type your password to login: ");
                getline(&check, &checkLen, stdin);
                if (check[strlen(check) - 1] == '\n')
                    check[strlen(check) - 1] = '\0';
                if (strcmp(pass, check) == 0) {
                    printWithDelay("Correct password\n");
                    sleep(1);
                    break;
                } else {
                    printWithDelay("Wrong password, try again\n");
                    sleep(1);
                }
                clearScreen();
            }
            clearScreen();
            int op = -1;
            int end = 0;
            while (op != 0) {
                char *newPasswords;
                size_t newPasswordsLen = 0;
                menu();
                scanf("%d", &op);
                clearScreen();
                switch (op) {
                case 1:
                    printWithDelay("Type the password you'd like to save: ");
                    getchar(); // clear line
                    getline(&newPasswords, &newPasswordsLen, stdin);
                    if (newPasswords[strlen(newPasswords) - 1] == '\n')
                        newPasswords[strlen(newPasswords) - 1] = '\0';
                    printWithDelay("Encrypting your password...\n");
                    char *encrypted;
                    encrypted = encrypt(newPasswords, 3);
                    saveNewPassword(encrypted);
                    printWithDelay("\nYour password is saved\n");
                    break;
                case 2:
                    getMyPasswords();
                    break;
                case 0:
                    printWithDelay("Operation terminated\n");
                    end = 1;
                    break;
                default:
                    printWithDelay("Invalid option\n");
                    break;
                }
                if (end == 0) {
                    pauseSystem();
                    clearScreen();
                    running = 0;
                }
            }
        } else {
            printWithDelay("Unexpected values found in the file firstLogin.txt\n");
            running = 0;
        }
    }
    printf("\033[0m");
    exit(EXIT_SUCCESS);
}