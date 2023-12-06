#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "library.h"

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    printf("\033[H\033[J");
    #endif
}

void pauseSystem() {
    printWithDelay("\n\ntype ENTER to continue...\n\n");
    while (getchar() != '\n');
    getchar();
}

int verifyLogin() {
    FILE *file = fopen("firstLogin.txt", "r");

    if (file == NULL) {
        printWithDelay("Error while opening firstLogin.txt\n");
        exit(EXIT_FAILURE);
    }

    int flag;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '1')
            flag = 1; // it's the first login
        else if (c == '0')
            flag = 0; // it's not the first login
        else
            flag = -1; // not an expected value
    }

    fclose(file);
    return flag;
}

void printWithDelay(const char *message) {
    for (int i = 0; message[i] != '\0'; ++i) {
        putchar(message[i]);
        fflush(stdout);
        usleep(50000);
    }
}

void activateLogin() {
    FILE *file = fopen("firstLogin.txt", "w");

    if (file == NULL) {
        printWithDelay("Error while opening firstLogin.txt\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d", 0);

    fclose(file);
}

void saveUserName(const char *userName) {
    FILE *file = fopen("user.txt", "w");

    if (file == NULL) {
        printWithDelay("Error while opening user.txt\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", userName);

    fclose(file);
}

void savePassword(const char *password) {
    FILE *file = fopen("password.txt", "w");

    if (file == NULL) {
        printWithDelay("Error while opening password.txt\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", password);

    fclose(file);
}

char *getUsername() {
    FILE *file = fopen("user.txt", "r");

    if (file == NULL) {
        printWithDelay("Error while opening user.txt\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(fileSize + 1);

    if (content == NULL) {
        printWithDelay("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    fread(content, sizeof(char), fileSize, file);
    content[fileSize] = '\0';

    fclose(file);
    return content;
}

char *getPassword() {
        FILE *file = fopen("password.txt", "r");

    if (file == NULL) {
        printWithDelay("Error while opening password.txt\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(fileSize + 1);

    if (content == NULL) {
        printWithDelay("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    fread(content, sizeof(char), fileSize, file);
    content[fileSize] = '\0';

    fclose(file);
    return content;
}

void menu() {
    printWithDelay("MENU\n");
    printWithDelay("1 - Save new password\n");
    printWithDelay("2 - View my passwords\n");
    printWithDelay("0 - Exit\n");
}

void saveNewPassword(const char *password) {
    FILE *file = fopen("myPasswords.txt", "a");

    if (file == NULL) {
        printWithDelay("Error while opening myPasswords.txt\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", password);
    fprintf(file, "\n");

    fclose(file);
}

void getMyPasswords() {
    FILE *file = fopen("myPasswords.txt", "r");

    if (file == NULL) {
        printWithDelay("Error while opening myPasswords.txt\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize <= 0) {
        printWithDelay("No passwords saved yet\n");
        fclose(file);
        return;
    }

    char *password = NULL;
    size_t passwordLen = 0;

    while (getline(&password, &passwordLen, file) != -1) {
        int len = strlen(password);
        if (len > 0 && password[len - 1] == '\n')
            password[len - 1] = '\0';
        char *reverseEncryptedPassword = reverseDecrypt(password, 3);
        printWithDelay(reverseEncryptedPassword);
        printf("\n");

        free(reverseEncryptedPassword);
    }

    free(password);
    fclose(file);
}


char *encrypt(const char *password, int shift) {
    int length = strlen(password);
    char *encryptedPassword = (char *)malloc(length + 1);

    if (encryptedPassword == NULL) {
        printWithDelay("Failed to allocate memory for encryptedPassword\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < length; i++) {
        char currentChar = password[i];

        if (currentChar >= 'A' && currentChar <= 'Z')
            encryptedPassword[i] = ((currentChar - 'A' + shift) % 26) + 'A';
        else if (currentChar >= 'a' && currentChar <= 'z')
            encryptedPassword[i] = ((currentChar - 'a' + shift) % 26) + 'a';
        else if (currentChar >= '0' && currentChar <= '9')
            encryptedPassword[i] = ((currentChar - '0' + shift) % 10) + '0';
        else
            encryptedPassword[i] = currentChar;
    }

    encryptedPassword[length] = '\0';
    return encryptedPassword;
}

char *reverseDecrypt(const char *encryptedMessage, int shift) {
    int length = strlen(encryptedMessage);
    char *decryptedMessage = (char *)malloc(length + 1);

    if (decryptedMessage == NULL) {
        printWithDelay("Failed to allocate memory for decryptedMessage\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < length; i++) {
        char currentChar = encryptedMessage[i];

        if (currentChar >= 'A' && currentChar <= 'Z')
            decryptedMessage[i] = ((currentChar - 'A' - shift + 26) % 26) + 'A';
        else if (currentChar >= 'a' && currentChar <= 'z')
            decryptedMessage[i] = ((currentChar - 'a' - shift + 26) % 26) + 'a';
        else if (currentChar >= '0' && currentChar <= '9')
            decryptedMessage[i] = ((currentChar - '0' - shift + 10) % 10) + '0';
        else
            decryptedMessage[i] = currentChar;
    }

    decryptedMessage[length] = '\0';

    return decryptedMessage;
}