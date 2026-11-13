#include <stdio.h>

struct Date {
    int day, month, year;
};

struct Address {
    char city[20];
    int pincode;
};

struct Parcel {
    int id;
    float weight;
    struct Address to;
    struct Date booked;
};

void print_parcel(const struct Parcel *p) {
    printf("%d %.1f kg %s-%d %02d/%02d/%04d\n",
           p->id, p->weight, p->to.city,
           p->to.pincode, p->booked.day,
           p->booked.month, p->booked.year);
}

void sort_by_weight(struct Parcel p[], int n) {
    int i, j, min;
    struct Parcel temp;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (p[j].weight < p[min].weight)
                min = j;
        }

        if (min != i) {
            temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

int main(void) {
    struct Parcel list[3] = {
        {501, 4.5, {"Madurai", 625001}, {12, 10, 2026}},
        {502, 1.2, {"Chennai", 600077}, {12, 10, 2026}},
        {503, 2.8, {"Coimbatore", 641001}, {13, 10, 2026}}
    };

    sort_by_weight(list, 3);

    for (int i = 0; i < 3; i++)
        print_parcel(&list[i]);

    printf("Receiver PIN of third parcel: %d\n",
           list[2].to.pincode);

    struct Parcel *ptr = &list[2];
    printf("Using pointer: %d\n", ptr->to.pincode);

    return 0;
}