#ifndef DOCTOR_H
#define DOCTOR_H

/* Doctor record stored in doctors.txt */
struct Doctor
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    char specialization[50];
    int experience;
};

void doctorManagement(void);
void addDoctor(void);
void viewDoctors(void);
void searchDoctor(void);
void updateDoctor(void);
void deleteDoctor(void);

#endif /* DOCTOR_H */
