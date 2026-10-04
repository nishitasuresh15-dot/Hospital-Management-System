#ifndef UI_H
#define UI_H

/* Console UI helpers shared by all modules */
void header(const char title[]);
void successMessage(const char message[]);
void errorMessage(const char message[]);
void getPassword(char password[]);

#endif /* UI_H */
