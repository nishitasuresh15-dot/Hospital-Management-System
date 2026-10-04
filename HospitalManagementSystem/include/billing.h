#ifndef BILLING_H
#define BILLING_H

/* Bill record stored in bills.txt */
struct Bill
{
    int billID;
    int patientID;
    float consultationFee;
    float medicineCost;
    float roomCharges;
    float totalAmount;
    char paymentStatus[20];
};

void billingManagement(void);
void generateBill(void);
void viewBills(void);
void searchBill(void);
void updateBill(void);
void deleteBill(void);

#endif /* BILLING_H */
