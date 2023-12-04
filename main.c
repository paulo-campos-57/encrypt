#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "library.h"

int main() {
    clearScreen();
    printf("\033[1;32m");
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
        printWithDelay("All your data is saved, finish the program and enter again to use it.\n");
        activateLogin();
    } else if (!verifyLogin()) {
        char *user = getUsername();
        char *pass = getPassword();
        char *check;
        size_t checkLen = 0;
        printWithDelay("Welcome ");
        printWithDelay(user);
        printf("\n");
        while(1) {
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
        while (op != 0) {
            menu();
            scanf("%d", &op);
            switch (op) {
            case 1:
                printWithDelay("Option 1\n");
                break;
            case 2:
                printWithDelay("Option 2\n");
                break;
            default:
                printWithDelay("Invalid option\n");
                break;
            }
            pauseSystem();
            clearScreen();
        }
    } else {
        printWithDelay("Unexpected values found in the file firstLogin.txt\n");
    }
    printf("\033[0m");
    exit(EXIT_SUCCESS);
}