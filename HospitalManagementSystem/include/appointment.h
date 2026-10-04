#ifndef APPOINTMENT_H
#define APPOINTMENT_H

/* Appointment record stored in appointments.txt */
struct Appointment
{
    int appointmentID;
    int patientID;
    int doctorID;
    char date[15];
    char time[10];
    char status[20];
};

void appointmentManagement(void);
void addAppointment(void);
void viewAppointments(void);
void searchAppointment(void);
void updateAppointment(void);
void deleteAppointment(void);

#endif /* APPOINTMENT_H */
