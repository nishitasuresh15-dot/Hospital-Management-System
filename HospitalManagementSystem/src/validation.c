#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "validation.h"

int validatePhone(const char phone[])
{
    if(strlen(phone) != 10)
    {
        return 0;
    }

    for(int i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
        {
            return 0;
        }
    }

    return 1;
}

int validateAge(int age)
{
    if(age >= 1 && age <= 120)
    {
        return 1;
    }

    return 0;
}

int validateBloodGroup(const char bloodGroup[])
{
    if(strcmp(bloodGroup, "A+") == 0 ||
        strcmp(bloodGroup, "A-") == 0 ||
        strcmp(bloodGroup, "B+") == 0 ||
        strcmp(bloodGroup, "B-") == 0 ||
        strcmp(bloodGroup, "AB+") == 0 ||
        strcmp(bloodGroup, "AB-") == 0 ||
        strcmp(bloodGroup, "O+") == 0 ||
        strcmp(bloodGroup, "O-") == 0)
    {
        return 1;
    }

    return 0;
}

int validateID(int id)
{
    if(id > 0)
    {
        return 1;
    }

    return 0;
}

int validateDate(const char date[])
{
    int day, month, year;

    if(sscanf(date, "%d-%d-%d", &day, &month, &year) != 3)
    {
        return 0;
    }

    if(day < 1 || day > 31)
    {
        return 0;
    }

    if(month < 1 || month > 12)
    {
        return 0;
    }

    if(year < 2000 || year > 2100)
    {
        return 0;
    }

    return 1;
}

int validateTime(const char time[])
{
    int hour, minute;
    char period[3];

    if(sscanf(time, "%d:%d%2s", &hour, &minute, period) != 3)
    {
        return 0;
    }

    if(hour < 1 || hour > 12)
    {
        return 0;
    }

    if(minute < 0 || minute > 59)
    {
        return 0;
    }

    if(strcmp(period, "AM") != 0 && strcmp(period, "PM") != 0)
    {
        return 0;
    }

    return 1;
}

int validateStatus(const char status[])
{
    if(strcmp(status, "Scheduled") == 0 ||
        strcmp(status, "Completed") == 0 ||
        strcmp(status, "Cancelled") == 0 ||
        strcmp(status, "Pending") == 0)
    {
        return 1;
    }

    return 0;
}

int validateAmount(float amount)
{
    if(amount >= 0)
    {
        return 1;
    }

    return 0;
}

int validatePaymentStatus(const char status[])
{
    if(strcmp(status, "Paid") == 0 ||
        strcmp(status, "Pending") == 0)
    {
        return 1;
    }

    return 0;
}

int validateName(const char name[])
{
    for(int i = 0; name[i] != '\0'; i++)
    {
        if(!isalpha(name[i]) && name[i] != ' ')
        {
            return 0;
        }
    }

    return 1;
}
