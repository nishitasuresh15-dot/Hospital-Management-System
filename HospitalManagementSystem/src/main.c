#include <stdio.h>
#include <string.h>

#include "appointment.h"
#include "billing.h"
#include "doctor.h"
#include "patient.h"
#include "ui.h"

static void login(void);
static void dashboard(void);

int main(void)
{
    login();

    return 0;
}

static void login(void)
{
    char username[20];
    char password[20];

    printf("\n\n");
    printf("==================================================\n");
    printf("                                                  \n");
    printf("              + CITY CARE HOSPITAL +              \n");
    printf("                                                  \n");
    printf("           HOSPITAL MANAGEMENT SYSTEM             \n");
    printf("                                                  \n");
    printf("==================================================\n");

    printf("\n");
    printf("                 +--------------+\n");
    printf("                 |  ADMIN LOGIN |\n");
    printf("                 +--------------+\n");

    printf("\n--------------------------------------------------\n");

    printf("\nEnter Username : ");
    scanf("%s", username);

    printf("Enter Password : ");
    getPassword(password);

    printf("\n--------------------------------------------------");

    if(strcmp(username, "admin") == 0 &&
        strcmp(password, "1234") == 0)
    {
        printf("\n\nACCESS GRANTED!");
        dashboard();
    }
    else
    {
        printf("\n\nACCESS DENIED!");
    }
}

static void dashboard(void)
{
    int choice;

    while(1)
    {
        header("HOSPITAL DASHBOARD");

        printf("\n+--------------------------------------+");
        printf("\n| [1] Patient Management               |");
        printf("\n| [2] Doctor Management                |");
        printf("\n| [3] Appointment Management           |");
        printf("\n| [4] Billing Management               |");
        printf("\n| [5] Logout                           |");
        printf("\n+--------------------------------------+");

        printf("\n--------------------------------------------------");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            patientManagement();
            break;

        case 2:
            doctorManagement();
            break;

        case 3:
            appointmentManagement();
            break;

        case 4:
            billingManagement();
            break;

        case 5:
            printf("\nLogged out successfully!");
            login();
            return;

        default:
            printf("\nInvalid choice!");
        }
    }
}
