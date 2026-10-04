#include <stdio.h>
#include <string.h>

#include "billing.h"
#include "ui.h"
#include "validation.h"

static struct Bill b;

void billingManagement(void)
{
    int choice;

    while(1)
    {
        header("BILLING MANAGEMENT");

        printf("\n+--------------------------------------+");
        printf("\n| [1] Generate Bill                    |");
        printf("\n| [2] View Bills                       |");
        printf("\n| [3] Search Bill                      |");
        printf("\n| [4] Update Bill                      |");
        printf("\n| [5] Delete Bill                      |");
        printf("\n| [6] Back to Dashboard                |");
        printf("\n+--------------------------------------+");

        printf("\n--------------------------------------------------");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            generateBill();
            break;

        case 2:
            viewBills();
            break;

        case 3:
            searchBill();
            break;

        case 4:
            updateBill();
            break;

        case 5:
            deleteBill();
            break;

        case 6:
            return;

        default:
            printf("\nInvalid choice!");
        }
    }
}

void generateBill(void)
{
    FILE *file;

    file = fopen("bills.txt", "a");

    do
    {
        printf("\nEnter Bill ID: ");
        scanf("%d", &b.billID);

        if(!validateID(b.billID))
        {
            errorMessage("Invalid ID! ID must be greater than 0.");
        }

    } while(!validateID(b.billID));

    printf("Enter Patient ID: ");
    scanf("%d", &b.patientID);

    do
    {
        printf("\nEnter Consultation Fee: ");
        scanf("%f", &b.consultationFee);

        if(!validateAmount(b.consultationFee))
        {
            errorMessage("Amount cannot be negative!");
        }

    } while(!validateAmount(b.consultationFee));

    do
    {
        printf("\nEnter Medicine Cost: ");
        scanf("%f", &b.medicineCost);

        if(!validateAmount(b.medicineCost))
        {
            errorMessage("Amount cannot be negative!");
        }

    } while(!validateAmount(b.medicineCost));

    do
    {
        printf("\nEnter Room Charges: ");
        scanf("%f", &b.roomCharges);

        if(!validateAmount(b.roomCharges))
        {
            errorMessage("Amount cannot be negative!");
        }

    } while(!validateAmount(b.roomCharges));

    b.totalAmount = b.consultationFee +
    b.medicineCost +
    b.roomCharges;

    do
    {
        printf("\nEnter Payment Status (Paid/Pending): ");
        scanf("%s", b.paymentStatus);

        if(!validatePaymentStatus(b.paymentStatus))
        {
            errorMessage("Invalid payment status! Enter Paid or Pending.");
        }

    } while(!validatePaymentStatus(b.paymentStatus));

    fprintf(file, "%d %d %.2f %.2f %.2f %.2f %s\n",
        b.billID,
        b.patientID,
        b.consultationFee,
        b.medicineCost,
        b.roomCharges,
        b.totalAmount,
        b.paymentStatus);

    fclose(file);

    successMessage("Bill Generated Successfully!");
    printf("\nTotal Amount: %.2f", b.totalAmount);
}

void viewBills(void)
{
    FILE *file;

    file = fopen("bills.txt", "r");

    if(file == NULL)
    {
        errorMessage("No bill records found!");
        return;
    }

    while(fscanf(file, "%d %d %f %f %f %f %s",
        &b.billID,
        &b.patientID,
        &b.consultationFee,
        &b.medicineCost,
        &b.roomCharges,
        &b.totalAmount,
        b.paymentStatus) != EOF)
    {

        printf("\n\n+==================================================+");
        printf("\n|                 BILL DETAILS                     |");
        printf("\n+==================================================+");

        printf("\n| Bill ID            : %-29d |", b.billID);
        printf("\n| Patient ID         : %-29d |", b.patientID);
        printf("\n| Consultation Fee   : %-29.2f |", b.consultationFee);
        printf("\n| Medicine Cost      : %-29.2f |", b.medicineCost);
        printf("\n| Room Charges       : %-29.2f |", b.roomCharges);
        printf("\n| Total Amount       : %-29.2f |", b.totalAmount);
        printf("\n| Payment Status     : %-29s |", b.paymentStatus);

        printf("\n+==================================================+\n");

    }

    fclose(file);
}

void searchBill(void)
{
    FILE *file;
    int searchID;
    int found = 0;

    file = fopen("bills.txt", "r");

    if(file == NULL)
    {
        printf("\nNo bill records found!");
        return;
    }

    printf("\nEnter Bill ID to search: ");
    scanf("%d", &searchID);

    while(fscanf(file, "%d %d %f %f %f %f %s",
        &b.billID,
        &b.patientID,
        &b.consultationFee,
        &b.medicineCost,
        &b.roomCharges,
        &b.totalAmount,
        b.paymentStatus) != EOF)
    {

        if(b.billID == searchID)
        {
            printf("\nBill Found!");
            printf("\n--------------------------------");
            printf("\nBill ID            : %d", b.billID);
            printf("\nPatient ID         : %d", b.patientID);
            printf("\nConsultation Fee   : %.2f", b.consultationFee);
            printf("\nMedicine Cost      : %.2f", b.medicineCost);
            printf("\nRoom Charges       : %.2f", b.roomCharges);
            printf("\nTotal Amount       : %.2f", b.totalAmount);
            printf("\nPayment Status     : %s", b.paymentStatus);
            printf("\n--------------------------------");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nBill not found!");
    }

    fclose(file);
}

void updateBill(void)
{
    FILE *file, *temp;
    int updateID;
    int found = 0;
    int choice;

    file = fopen("bills.txt", "r");

    if(file == NULL)
    {
        printf("\nNo bill records found!");
        return;
    }

    temp = fopen("temp.txt", "w");

    printf("\nEnter Bill ID to update: ");
    scanf("%d", &updateID);

    while(fscanf(file, "%d %d %f %f %f %f %s",
        &b.billID,
        &b.patientID,
        &b.consultationFee,
        &b.medicineCost,
        &b.roomCharges,
        &b.totalAmount,
        b.paymentStatus) != EOF)
    {

        if(b.billID == updateID)
        {
            found = 1;

            printf("\nCurrent Bill Details");
            printf("\n--------------------------------");
            printf("\nConsultation Fee : %.2f", b.consultationFee);
            printf("\nMedicine Cost    : %.2f", b.medicineCost);
            printf("\nRoom Charges     : %.2f", b.roomCharges);
            printf("\nTotal Amount     : %.2f", b.totalAmount);
            printf("\nPayment Status   : %s", b.paymentStatus);
            printf("\n--------------------------------");

            printf("\n\nWhat do you want to update?");
            printf("\n1. Consultation Fee");
            printf("\n2. Medicine Cost");
            printf("\n3. Room Charges");
            printf("\n4. Payment Status");
            printf("\n5. Update All");

            printf("\n\nEnter choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
            case 1:
                printf("Enter New Consultation Fee: ");
                scanf("%f", &b.consultationFee);
                break;

            case 2:
                printf("Enter New Medicine Cost: ");
                scanf("%f", &b.medicineCost);
                break;

            case 3:
                printf("Enter New Room Charges: ");
                scanf("%f", &b.roomCharges);
                break;

            case 4:
                printf("Enter New Payment Status: ");
                scanf("%s", b.paymentStatus);
                break;

            case 5:

                printf("Enter New Consultation Fee: ");
                scanf("%f", &b.consultationFee);

                printf("Enter New Medicine Cost: ");
                scanf("%f", &b.medicineCost);

                printf("Enter New Room Charges: ");
                scanf("%f", &b.roomCharges);

                printf("Enter New Payment Status: ");
                scanf("%s", b.paymentStatus);

                break;

            default:
                printf("\nInvalid choice!");
            }

            b.totalAmount = b.consultationFee +
            b.medicineCost +
            b.roomCharges;
        }

        fprintf(temp, "%d %d %.2f %.2f %.2f %.2f %s\n",
            b.billID,
            b.patientID,
            b.consultationFee,
            b.medicineCost,
            b.roomCharges,
            b.totalAmount,
            b.paymentStatus);

    }

    fclose(file);
    fclose(temp);

    remove("bills.txt");
    rename("temp.txt", "bills.txt");

    if(found)
    {
        successMessage("Bill Updated Successfully!");
    }
    else
    {
        errorMessage("Bill ID Not Found!");
    }
}

void deleteBill(void)
{
    FILE *file, *temp;
    int deleteID;
    int found = 0;

    file = fopen("bills.txt", "r");

    if(file == NULL)
    {
        printf("\nNo bill records found!");
        return;
    }

    temp = fopen("temp.txt", "w");

    printf("\nEnter Bill ID to delete: ");
    scanf("%d", &deleteID);

    while(fscanf(file, "%d %d %f %f %f %f %s",
        &b.billID,
        &b.patientID,
        &b.consultationFee,
        &b.medicineCost,
        &b.roomCharges,
        &b.totalAmount,
        b.paymentStatus) != EOF)
    {

        if(b.billID == deleteID)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d %d %.2f %.2f %.2f %.2f %s\n",
            b.billID,
            b.patientID,
            b.consultationFee,
            b.medicineCost,
            b.roomCharges,
            b.totalAmount,
            b.paymentStatus);
    }

    fclose(file);
    fclose(temp);

    remove("bills.txt");
    rename("temp.txt", "bills.txt");

    if(found)
    {
        successMessage("Bill Deleted Successfully!");
    }
    else
    {
        printf("\nBill not found!");
    }
}
