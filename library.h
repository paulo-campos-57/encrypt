#ifndef __LIBRARY__
#define __LIBRARY__

void clearScreen();
void pauseSystem();
int verifyLogin();
void printWithDelay(const char *message);
void saveUserName(const char *userName);
void savePassword(const char *password);
void activateLogin();
char *getUsername();
char *getPassword();
void menu();
void saveNewPassword(const char *password);
void getMyPasswords();
char *encrypt(const char *password);
char *reverseEncrypt(const char *password);

#endif