#include <stdio.h>
#include <string.h>

#include "appointment.h"
#include "ui.h"
#include "validation.h"

static struct Appointment a;

void appointmentManagement(void)
{
    int choice;

    while(1)
    {
        header("APPOINTMENT MANAGEMENT");

        printf("\n+--------------------------------------+");
        printf("\n| [1] Add Appointment                  |");
        printf("\n| [2] View Appointments                |");
        printf("\n| [3] Search Appointment               |");
        printf("\n| [4] Update Appointment               |");
        printf("\n| [5] Delete Appointment               |");
        printf("\n| [6] Back to Dashboard                |");
        printf("\n+--------------------------------------+");

        printf("\n--------------------------------------------------");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            addAppointment();
            break;

        case 2:
            viewAppointments();
            break;

        case 3:
            searchAppointment();
            break;

        case 4:
            updateAppointment();
            break;

        case 5:
            deleteAppointment();
            break;

        case 6:
            return;

        default:
            printf("\nInvalid choice!");
        }
    }
}

void addAppointment(void)
{
    FILE *file;

    file = fopen("appointments.txt", "a");

    do
    {
        printf("\nEnter Appointment ID: ");
        scanf("%d", &a.appointmentID);

        if(!validateID(a.appointmentID))
        {
            errorMessage("Invalid ID! ID must be greater than 0.");
        }

    } while(!validateID(a.appointmentID));

    printf("Enter Patient ID: ");
    scanf("%d", &a.patientID);

    printf("Enter Doctor ID: ");
    scanf("%d", &a.doctorID);

    do
    {
        printf("Enter Date (DD-MM-YYYY): ");
        scanf("%s", a.date);

        if(!validateDate(a.date))
        {
            errorMessage("Invalid date! Use DD-MM-YYYY.");
        }

    } while(!validateDate(a.date));

    do
    {
        printf("Enter Time (HH:MMAM/PM): ");
        scanf("%s", a.time);

        if(!validateTime(a.time))
        {
            errorMessage("Invalid time! Use HH:MMAM/PM format.");
        }

    } while(!validateTime(a.time));

    do
    {
        printf("Enter Status (Scheduled/Completed/Cancelled/Pending): ");
        scanf("%s", a.status);

        if(!validateStatus(a.status))
        {
            errorMessage("Invalid status!");
        }

    } while(!validateStatus(a.status));

    fprintf(file, "%d %d %d %s %s %s\n",
        a.appointmentID,
        a.patientID,
        a.doctorID,
        a.date,
        a.time,
        a.status);

    fclose(file);

    successMessage("Appointment Added Successfully!");
}

void viewAppointments(void)
{
    FILE *file;

    file = fopen("appointments.txt", "r");

    if(file == NULL)
    {
        errorMessage("No appointment records found!");
        return;
    }

    while(fscanf(file, "%d %d %d %s %s %s",
        &a.appointmentID,
        &a.patientID,
        &a.doctorID,
        a.date,
        a.time,
        a.status) != EOF)
    {

        printf("\n\n+==================================================+");
        printf("\n|              APPOINTMENT DETAILS                 |");
        printf("\n+==================================================+");

        printf("\n| Appointment ID : %-32d |", a.appointmentID);
        printf("\n| Patient ID     : %-32d |", a.patientID);
        printf("\n| Doctor ID      : %-32d |", a.doctorID);
        printf("\n| Date           : %-32s |", a.date);
        printf("\n| Time           : %-32s |", a.time);
        printf("\n| Status         : %-32s |", a.status);

        printf("\n+==================================================+\n");
    }

    fclose(file);
}

void searchAppointment(void)
{
    FILE *file;
    int searchID;
    int found = 0;

    file = fopen("appointments.txt", "r");

    if(file == NULL)
    {
        printf("\nNo appointment records found!");
        return;
    }

    printf("\nEnter Appointment ID to search: ");
    scanf("%d", &searchID);

    while(fscanf(file, "%d %d %d %s %s %s",
        &a.appointmentID,
        &a.patientID,
        &a.doctorID,
        a.date,
        a.time,
        a.status) != EOF)
    {

        if(a.appointmentID == searchID)
        {
            printf("\nAppointment Found!");
            printf("\n--------------------------------");
            printf("\nAppointment ID : %d", a.appointmentID);
            printf("\nPatient ID     : %d", a.patientID);
            printf("\nDoctor ID      : %d", a.doctorID);
            printf("\nDate           : %s", a.date);
            printf("\nTime           : %s", a.time);
            printf("\nStatus         : %s", a.status);
            printf("\n--------------------------------");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        errorMessage("Appointment not found!");
    }

    fclose(file);
}

void updateAppointment(void)
{
    FILE *file, *temp;
    int updateID;
    int found = 0;

    file = fopen("appointments.txt", "r");

    if(file == NULL)
    {
        printf("\nNo appointment records found!");
        return;
    }

    temp = fopen("temp.txt", "w");

    printf("\nEnter Appointment ID to update: ");
    scanf("%d", &updateID);

    while(fscanf(file, "%d %d %d %s %s %s",
        &a.appointmentID,
        &a.patientID,
        &a.doctorID,
        a.date,
        a.time,
        a.status) != EOF)
    {

        if(a.appointmentID == updateID)
        {
            found = 1;

            printf("\nCurrent Appointment Details");
            printf("\n-----------------------------");
            printf("\nPatient ID : %d", a.patientID);
            printf("\nDoctor ID  : %d", a.doctorID);
            printf("\nDate       : %s", a.date);
            printf("\nTime       : %s", a.time);
            printf("\nStatus     : %s", a.status);

            printf("\n\nEnter New Date: ");
            scanf("%s", a.date);

            printf("Enter New Time: ");
            scanf("%s", a.time);

            printf("Enter New Status: ");
            scanf("%s", a.status);
        }

        fprintf(temp, "%d %d %d %s %s %s\n",
            a.appointmentID,
            a.patientID,
            a.doctorID,
            a.date,
            a.time,
            a.status);
    }

    fclose(file);
    fclose(temp);

    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");

    if(found)
    {
        successMessage("Appointment Updated Successfully!");
    }
    else
    {
        errorMessage("Appointment ID Not Found!");
    }
}

void deleteAppointment(void)
{
    FILE *file, *temp;
    int deleteID;
    int found = 0;

    file = fopen("appointments.txt", "r");

    if(file == NULL)
    {
        printf("\nNo appointment records found!");
        return;
    }

    temp = fopen("temp.txt", "w");

    printf("\nEnter Appointment ID to delete: ");
    scanf("%d", &deleteID);

    while(fscanf(file, "%d %d %d %s %s %s",
        &a.appointmentID,
        &a.patientID,
        &a.doctorID,
        a.date,
        a.time,
        a.status) != EOF)
    {

        if(a.appointmentID == deleteID)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d %d %d %s %s %s\n",
            a.appointmentID,
            a.patientID,
            a.doctorID,
            a.date,
            a.time,
            a.status);
    }

    fclose(file);
    fclose(temp);

    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");

    if(found)
    {
        successMessage("Appointment deleted successfully!");
    }
    else
    {
        errorMessage("Appointment not found!");
    }
}
