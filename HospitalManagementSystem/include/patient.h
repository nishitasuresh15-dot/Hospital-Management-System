#ifndef PATIENT_H
#define PATIENT_H

/* Patient record stored in patients.txt */
struct Patient
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    char bloodGroup[5];
    char disease[50];
};

void patientManagement(void);
void addPatient(void);
void viewPatients(void);
void searchPatient(void);
void updatePatient(void);
void deletePatient(void);

#endif /* PATIENT_H */
