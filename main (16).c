#include <stdio.h>
#define MAX 100

struct Date {
    int day, month, year;
};

struct BloodPressure {
    int systolic, diastolic;
};

struct Patient {
    char name[50];
    int age;
    char phone[11];
    struct BloodPressure bp;
    struct Date visitDate;
};

struct Patient patients[MAX];
int count = 0;

void addPatient(struct Patient *p, struct Patient newPatient) {
    if (count >= MAX)
        return;
    *p = newPatient;
    count++;
}

int main(void) {
    struct Patient p = {
        "Arun", 35, "9876543210",
        {120, 80}, {12, 11, 2026}
    };

    addPatient(&patients[count], p);

    printf("Patient Name: %s\n", patients[0].name);
    printf("Age: %d\n", patients[0].age);
    printf("Phone: %s\n", patients[0].phone);
    printf("Blood Pressure: %d/%d\n",
           patients[0].bp.systolic,
           patients[0].bp.diastolic);
    printf("Visit Date: %02d/%02d/%04d\n",
           patients[0].visitDate.day,
           patients[0].visitDate.month,
           patients[0].visitDate.year);

    return 0;
}