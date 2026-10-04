#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "patient.h"
#include "ui.h"
#include "validation.h"

static struct Patient p;

void patientManagement(void)
{
    int choice;

    while(1)
    {
        header("PATIENT MANAGEMENT");

        printf("\n+--------------------------------------+");
        printf("\n| [1] Add Patient                      |");
        printf("\n| [2] View Patients                    |");
        printf("\n| [3] Search Patient                   |");
        printf("\n| [4] Update Patient                   |");
        printf("\n| [5] Delete Patient                   |");
        printf("\n| [6] Back to Dashboard                |");
        printf("\n+--------------------------------------+");

        printf("\n--------------------------------------------------");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            addPatient();
            break;

        case 2:
            viewPatients();
            break;

        case 3:
            searchPatient();
            break;

        case 4:
            updatePatient();
            break;

        case 5:
            deletePatient();
            break;

        case 6:
            return;

        default:
            printf("\nInvalid choice!");
        }
    }
}

void addPatient(void)
{
    FILE *file;
    int exists = 0;
    int newID;

    file = fopen("patients.txt", "a+");

    do
    {
        printf("\nEnter Patient ID: ");
        scanf("%d", &p.id);

        if(!validateID(p.id))
        {
            errorMessage("Invalid ID! ID must be greater than 0.");
        }

    } while(!validateID(p.id));

    newID = p.id;

    rewind(file);

    while(fscanf(file, "%d %s %d %s %s %s %s",
        &p.id,
        p.name,
        &p.age,
        p.gender,
        p.phone,
        p.bloodGroup,
        p.disease) != EOF)
    {
        if(p.id == newID)
        {
            exists = 1;
            break;
        }
    }

    if(exists)
    {
        printf("\nPatient ID already exists!");
        fclose(file);
        return;
    }

    p.id = newID;

    do
    {
        printf("\nEnter Name: ");
        scanf("%s", p.name);

        if(!validateName(p.name))
        {
            errorMessage("Invalid name! Use only letters.");
        }

    } while(!validateName(p.name));

    do
    {
        printf("\nEnter Age: ");
        scanf("%d", &p.age);

        if(!validateAge(p.age))
        {
            errorMessage("Invalid age! Enter age between 1 and 120.");
        }

    } while(!validateAge(p.age));

    do
    {
        printf("\nEnter Gender (Male/Female): ");
        scanf("%9s", p.gender);

        for(int i = 0; p.gender[i] != '\0'; i++)
        {
            p.gender[i] = tolower((unsigned char)p.gender[i]);
        }

        if(strcmp(p.gender, "male") != 0 &&
            strcmp(p.gender, "female") != 0)
        {
            errorMessage("Invalid gender! Enter Male or Female.");
        }

    } while(strcmp(p.gender, "male") != 0 &&
        strcmp(p.gender, "female") != 0);

    p.gender[0] = toupper((unsigned char)p.gender[0]);

    do
    {
        printf("\nEnter Phone Number (10 digits): ");
        scanf("%s", p.phone);

        if(!validatePhone(p.phone))
        {
            errorMessage("Invalid phone number! Enter exactly 10 digits.");
        }

    } while(!validatePhone(p.phone));

    do
    {
        printf("\nEnter Blood Group (A+/A-/B+/B-/AB+/AB-/O+/O-): ");
        scanf("%s", p.bloodGroup);

        if(!validateBloodGroup(p.bloodGroup))
        {
            errorMessage("Invalid blood group!");
        }

    } while(!validateBloodGroup(p.bloodGroup));

    printf("Enter Disease: ");
    scanf("%s", p.disease);

    fprintf(file, "%d %s %d %s %s %s %s\n",
        p.id,
        p.name,
        p.age,
        p.gender,
        p.phone,
        p.bloodGroup,
        p.disease);

    fclose(file);

    successMessage("Patient Added Successfully!");
}

void viewPatients(void)
{
    FILE *file;

    file = fopen("patients.txt", "r");

    if(file == NULL)
    {
        errorMessage("No patient records found!");
        return;
    }

    while(fscanf(file, "%d %s %d %s %s %s %s",
        &p.id,
        p.name,
        &p.age,
        p.gender,
        p.phone,
        p.bloodGroup,
        p.disease) != EOF)
    {

        printf("\n\n+==================================================+");
        printf("\n|                PATIENT DETAILS                   |");
        printf("\n+==================================================+");

        printf("\n| Patient ID  : %-35d |", p.id);
        printf("\n| Name        : %-35s |", p.name);
        printf("\n| Age         : %-35d |", p.age);
        printf("\n| Gender      : %-35s |", p.gender);
        printf("\n| Phone       : %-35s |", p.phone);
        printf("\n| Blood Group : %-35s |", p.bloodGroup);
        printf("\n| Disease     : %-35s |", p.disease);

        printf("\n+==================================================+\n");
    }

    fclose(file);
}

void searchPatient(void)
{
    FILE *file;
    int searchID;
    int found = 0;

    file = fopen("patients.txt", "r");

    if(file == NULL)
    {
        printf("\nNo patient records found!");
        return;
    }

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &searchID);

    while(fscanf(file, "%d %s %d %s %s %s %s",
        &p.id,
        p.name,
        &p.age,
        p.gender,
        p.phone,
        p.bloodGroup,
        p.disease) != EOF)
    {

        if(p.id == searchID)
        {
            printf("\nPatient Found!");
            printf("\n--------------------------------");
            printf("\nID          : %d", p.id);
            printf("\nName        : %s", p.name);
            printf("\nAge         : %d", p.age);
            printf("\nGender      : %s", p.gender);
            printf("\nPhone       : %s", p.phone);
            printf("\nBlood Group : %s", p.bloodGroup);
            printf("\nDisease     : %s", p.disease);
            printf("\n--------------------------------");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        errorMessage("Patient Not Found!");
    }

    fclose(file);
}

void updatePatient(void)
{
    FILE *file, *temp;
    int updateID;
    int found = 0;
    int choice;

    file = fopen("patients.txt", "r");

    if(file == NULL)
    {
        printf("\nNo patient records found!");
        return;
    }

    temp = fopen("temp.txt", "w");

    printf("\nEnter Patient ID to update: ");
    scanf("%d", &updateID);

    while(fscanf(file, "%d %s %d %s %s %s %s",
        &p.id,
        p.name,
        &p.age,
        p.gender,
        p.phone,
        p.bloodGroup,
        p.disease) != EOF)
    {

        if(p.id == updateID)
        {
            found = 1;

            printf("\nCurrent Patient Details");
            printf("\n----------------------------");
            printf("\nName        : %s", p.name);
            printf("\nAge         : %d", p.age);
            printf("\nGender      : %s", p.gender);
            printf("\nPhone       : %s", p.phone);
            printf("\nBlood Group : %s", p.bloodGroup);
            printf("\nDisease     : %s", p.disease);

            printf("\n\nWhat do you want to update?");
            printf("\n1. Name");
            printf("\n2. Age");
            printf("\n3. Gender");
            printf("\n4. Phone");
            printf("\n5. Disease");
            printf("\n6. Blood Group");
            printf("\n7. Update All");

            printf("\n\nEnter choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
            case 1:
                printf("Enter New Name: ");
                scanf("%s", p.name);
                break;

            case 2:
                printf("Enter New Age: ");
                scanf("%d", &p.age);
                break;

            case 3:
                printf("Enter New Gender: ");
                scanf("%s", p.gender);
                break;

            case 4:
                printf("Enter New Phone: ");
                scanf("%s", p.phone);
                break;

            case 5:
                printf("Enter New Disease: ");
                scanf("%s", p.disease);
                break;

            case 6:
                printf("Enter New Blood Group: ");
                scanf("%s", p.bloodGroup);
                break;

            case 7:
                printf("Enter New Name: ");
                scanf("%s", p.name);

                printf("Enter New Age: ");
                scanf("%d", &p.age);

                printf("Enter New Gender: ");
                scanf("%s", p.gender);

                printf("Enter New Phone: ");
                scanf("%s", p.phone);

                printf("Enter New Blood Group: ");
                scanf("%s", p.bloodGroup);

                printf("Enter New Disease: ");
                scanf("%s", p.disease);
                break;

            default:
                printf("\nInvalid choice!");
            }
        }

        fprintf(temp, "%d %s %d %s %s %s %s\n",
            p.id,
            p.name,
            p.age,
            p.gender,
            p.phone,
            p.bloodGroup,
            p.disease);
    }

    fclose(file);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if(found)
    {
        successMessage("Patient Updated Successfully!");
    }
    else
    {
        printf("\nPatient ID Not Found!");
    }
}

void deletePatient(void)
{
    FILE *file, *temp;
    int deleteID;
    int found = 0;

    file = fopen("patients.txt", "r");

    if(file == NULL)
    {
        printf("\nNo patient records found!");
        return;
    }

    temp = fopen("temp.txt", "w");

    printf("\nEnter Patient ID to delete: ");
    scanf("%d", &deleteID);

    while(fscanf(file, "%d %s %d %s %s %s %s",
        &p.id,
        p.name,
        &p.age,
        p.gender,
        p.phone,
        p.bloodGroup,
        p.disease) != EOF)
    {

        if(p.id == deleteID)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d %s %d %s %s %s %s\n",
            p.id,
            p.name,
            p.age,
            p.gender,
            p.phone,
            p.bloodGroup,
            p.disease);
    }

    fclose(file);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if(found)
    {
        successMessage("Patient Deleted Successfully!");
    }
    else
    {
        errorMessage("Patient Not Found!");
    }
}
