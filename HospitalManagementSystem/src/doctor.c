#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "doctor.h"
#include "ui.h"
#include "validation.h"

static struct Doctor d;

void doctorManagement(void)
{
    int choice;

    while(1)
    {
        header("DOCTOR MANAGEMENT");

        printf("\n+--------------------------------------+");
        printf("\n| [1] Add Doctor                       |");
        printf("\n| [2] View Doctors                     |");
        printf("\n| [3] Search Doctor                    |");
        printf("\n| [4] Update Doctor                    |");
        printf("\n| [5] Delete Doctor                    |");
        printf("\n| [6] Back to Dashboard                |");
        printf("\n+--------------------------------------+");

        printf("\n--------------------------------------------------");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            addDoctor();
            break;

        case 2:
            viewDoctors();
            break;

        case 3:
            searchDoctor();
            break;

        case 4:
            updateDoctor();
            break;

        case 5:
            deleteDoctor();
            break;

        case 6:
            return;

        default:
            printf("\nInvalid choice!");
        }
    }
}

void addDoctor(void)
{
    FILE *file;

    file = fopen("doctors.txt", "a");

    do
    {
        printf("\nEnter Doctor ID: ");
        scanf("%d", &d.id);

        if(!validateID(d.id))
        {
            errorMessage("Invalid ID! ID must be greater than 0.");
        }

    } while(!validateID(d.id));

    do
    {
        printf("\nEnter Name: ");
        scanf("%s", d.name);

        if(!validateName(d.name))
        {
            errorMessage("Invalid name! Use only letters.");
        }

    } while(!validateName(d.name));
    do
    {
        printf("\nEnter Age: ");
        scanf("%d", &d.age);

        if(!validateAge(d.age))
        {
            errorMessage("Invalid age! Enter age between 1 and 120.");
        }

    } while(!validateAge(d.age));

    do
    {
        printf("\nEnter Gender (Male/Female): ");
        scanf("%9s", d.gender);

        // Convert input to lowercase
        for(int i = 0; d.gender[i] != '\0'; i++)
        {
            d.gender[i] = tolower((unsigned char)d.gender[i]);
        }

        if(strcmp(d.gender, "male") != 0 &&
            strcmp(d.gender, "female") != 0)
        {
            errorMessage("Invalid gender! Enter Male or Female.");
        }

    } while(strcmp(d.gender, "male") != 0 &&
        strcmp(d.gender, "female") != 0);

    d.gender[0] = toupper((unsigned char)d.gender[0]);

    do
    {
        printf("\nEnter Phone Number (10 digits): ");
        scanf("%s", d.phone);

        if(!validatePhone(d.phone))
        {
            errorMessage("Invalid phone number! Enter exactly 10 digits.");
        }

    } while(!validatePhone(d.phone));

    printf("Enter Specialization: ");
    scanf("%s", d.specialization);

    printf("Enter Experience (Yrs): ");
    scanf("%d", &d.experience);

    fprintf(file, "%d %s %d %s %s %s %d\n",
        d.id,
        d.name,
        d.age,
        d.gender,
        d.phone,
        d.specialization,
        d.experience);

    fclose(file);

    successMessage("Doctor Added Successfully!");
}

void viewDoctors(void)
{
    FILE *file;

    file = fopen("doctors.txt", "r");

    if(file == NULL)
    {
        errorMessage("No doctor records found!");
        return;
    }

    while(fscanf(file, "%d %s %d %s %s %s %d",
        &d.id,
        d.name,
        &d.age,
        d.gender,
        d.phone,
        d.specialization,
        &d.experience) != EOF)
    {

        printf("\n+==================================================+");
        printf("\n|                 DOCTOR DETAILS                   |");
        printf("\n+==================================================+");

        printf("\n| Doctor ID      : %-32d|", d.id);
        printf("\n| Name           : %-32s|", d.name);
        printf("\n| Age            : %-32d|", d.age);
        printf("\n| Gender         : %-32s|", d.gender);
        printf("\n| Phone          : %-32s|", d.phone);
        printf("\n| Specialization : %-32s|", d.specialization);
        printf("\n| Experience(Yrs): %-32d|", d.experience);

        printf("\n+==================================================+\n");
    }

    fclose(file);
}

void searchDoctor(void)
{
    FILE *file;
    int searchID;
    int found = 0;

    file = fopen("doctors.txt", "r");

    if(file == NULL)
    {
        printf("\nNo doctor records found!");
        return;
    }

    printf("\nEnter Doctor ID to search: ");
    scanf("%d", &searchID);

    while(fscanf(file, "%d %s %d %s %s %s %d",
        &d.id,
        d.name,
        &d.age,
        d.gender,
        d.phone,
        d.specialization,
        &d.experience) != EOF)
    {

        if(d.id == searchID)
        {
            printf("\nDoctor Found!");
            printf("\n--------------------------------");
            printf("\nID             : %d", d.id);
            printf("\nName           : %s", d.name);
            printf("\nAge            : %d", d.age);
            printf("\nGender         : %s", d.gender);
            printf("\nPhone          : %s", d.phone);
            printf("\nSpecialization : %s", d.specialization);
            printf("\nExperience(Yrs): %d years", d.experience);
            printf("\n--------------------------------");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nDoctor not found!");
    }

    fclose(file);
}

void updateDoctor(void)
{
    FILE *file, *temp;
    int updateID;
    int found = 0;
    int choice;

    file = fopen("doctors.txt", "r");

    if(file == NULL)
    {
        printf("\nNo doctor records found!");
        return;
    }

    temp = fopen("temp.txt", "w");

    printf("\nEnter Doctor ID to update: ");
    scanf("%d", &updateID);

    while(fscanf(file, "%d %s %d %s %s %s %d",
        &d.id,
        d.name,
        &d.age,
        d.gender,
        d.phone,
        d.specialization,
        &d.experience) != EOF)
    {

        if(d.id == updateID)
        {
            found = 1;

            printf("\nCurrent Doctor Details");
            printf("\n--------------------------------");
            printf("\nName           : %s", d.name);
            printf("\nAge            : %d", d.age);
            printf("\nGender         : %s", d.gender);
            printf("\nPhone          : %s", d.phone);
            printf("\nSpecialization : %s", d.specialization);
            printf("\nExperience(Yrs): %d", d.experience);

            printf("\n\nWhat do you want to update?");
            printf("\n1. Name");
            printf("\n2. Age");
            printf("\n3. Gender");
            printf("\n4. Phone");
            printf("\n5. Specialization");
            printf("\n6. Experience");
            printf("\n7. Update All");

            printf("\n\nEnter choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
            case 1:
                printf("Enter New Name: ");
                scanf("%s", d.name);
                break;

            case 2:
                printf("Enter New Age: ");
                scanf("%d", &d.age);
                break;

            case 3:
                printf("Enter New Gender: ");
                scanf("%s", d.gender);
                break;

            case 4:
                printf("Enter New Phone: ");
                scanf("%s", d.phone);
                break;

            case 5:
                printf("Enter New Specialization: ");
                scanf("%s", d.specialization);
                break;

            case 6:
                printf("Enter New Experience(Yrs): ");
                scanf("%d", &d.experience);
                break;

            case 7:

                printf("Enter New Name: ");
                scanf("%s", d.name);

                printf("Enter New Age: ");
                scanf("%d", &d.age);

                printf("Enter New Gender: ");
                scanf("%s", d.gender);

                printf("Enter New Phone: ");
                scanf("%s", d.phone);

                printf("Enter New Specialization: ");
                scanf("%s", d.specialization);

                printf("Enter New Experience(Yrs): ");
                scanf("%d", &d.experience);

                break;

            default:
                printf("\nInvalid choice!");
            }
        }

        fprintf(temp, "%d %s %d %s %s %s %d\n",
            d.id,
            d.name,
            d.age,
            d.gender,
            d.phone,
            d.specialization,
            d.experience);
    }

    fclose(file);
    fclose(temp);

    remove("doctors.txt");
    rename("temp.txt", "doctors.txt");

    if(found)
    {
        successMessage("Doctor Updated Successfully!");
    }
    else
    {
        printf("\nDoctor ID Not Found!");
    }
}

void deleteDoctor(void)
{
    FILE *file, *temp;
    int deleteID;
    int found = 0;

    file = fopen("doctors.txt", "r");

    if(file == NULL)
    {
        printf("\nNo doctor records found!");
        return;
    }

    temp = fopen("temp.txt", "w");

    printf("\nEnter Doctor ID to delete: ");
    scanf("%d", &deleteID);

    while(fscanf(file, "%d %s %d %s %s %s %d",
        &d.id,
        d.name,
        &d.age,
        d.gender,
        d.phone,
        d.specialization,
        &d.experience) != EOF)
    {

        if(d.id == deleteID)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d %s %d %s %s %s %d\n",
            d.id,
            d.name,
            d.age,
            d.gender,
            d.phone,
            d.specialization,
            d.experience);
    }

    fclose(file);
    fclose(temp);

    remove("doctors.txt");
    rename("temp.txt", "doctors.txt");

    if(found)
    {
        successMessage("Doctor Deleted Successfully!");
    }
    else
    {
        printf("\nDoctor not found!");
    }
}
