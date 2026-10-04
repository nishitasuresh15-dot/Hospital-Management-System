#ifndef VALIDATION_H
#define VALIDATION_H

/* Input validation helpers. Each returns 1 if valid, 0 otherwise. */
int validateName(const char name[]);
int validatePhone(const char phone[]);
int validateAge(int age);
int validateBloodGroup(const char bloodGroup[]);
int validateID(int id);
int validateDate(const char date[]);
int validateTime(const char time[]);
int validateStatus(const char status[]);
int validateAmount(float amount);
int validatePaymentStatus(const char status[]);

#endif /* VALIDATION_H */
