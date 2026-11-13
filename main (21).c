#include <stdio.h>
#include <string.h>

#define MAX 10

enum ItemType {
    PACKAGED,
    COOKED,
    COMBO
};

struct Date {
    int day, month, year;
};

struct Combo {
    int count;
    int itemIndex[3];
    int quantity[3];
};

struct Item {
    int id;
    char name[30];
    enum ItemType type;
    float price;
    int stock;
    float revenue;

    union {
        struct Date expiry;
        char preparedTime[10];
        struct Combo combo;
    } details;
};

struct Item items[MAX];
int itemCount = 3;

int dateValue(struct Date d) {
    return d.year * 10000 + d.month * 100 + d.day;
}

void recordSale(int index, int quantity) {
    if (index < 0 || index >= itemCount || quantity <= 0) {
        printf("Invalid sale\n");
        return;
    }

    struct Item *item = &items[index];

    if (item->stock < quantity) {
        printf("Not enough stock for %s\n", item->name);
        return;
    }

    if (item->type == COMBO) {
        for (int i = 0; i < item->details.combo.count; i++) {
            int component = item->details.combo.itemIndex[i];
            int required = item->details.combo.quantity[i] * quantity;

            if (items[component].stock < required) {
                printf("Not enough stock for combo\n");
                return;
            }
        }

        for (int i = 0; i < item->details.combo.count; i++) {
            int component = item->details.combo.itemIndex[i];
            int required = item->details.combo.quantity[i] * quantity;
            items[component].stock -= required;
        }
    }

    item->stock -= quantity;
    item->revenue += item->price * quantity;

    printf("Sale successful: %s x %d\n", item->name, quantity);
}

void checkExpiry(struct Date today) {
    int current = dateValue(today);

    printf("\nExpiry Warnings\n");

    for (int i = 0; i < itemCount; i++) {
        if (items[i].type == PACKAGED) {
            int expiry = dateValue(items[i].details.expiry);

            if (expiry >= current && expiry - current <= 2)
                printf("%s is expiring soon\n", items[i].name);
        }
    }
}

void sortRevenue(void) {
    struct Item temp;

    for (int i = 0; i < itemCount - 1; i++) {
        for (int j = i + 1; j < itemCount; j++) {
            if (items[i].revenue < items[j].revenue) {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

void printSummary(void) {
    sortRevenue();

    printf("\nDaily Revenue Summary\n");

    for (int i = 0; i < itemCount; i++) {
        printf("%s: Rs. %.2f\n",
               items[i].name, items[i].revenue);
    }
}

int main(void) {
    items[0].id = 101;
    strcpy(items[0].name, "Rice Packet");
    items[0].type = PACKAGED;
    items[0].price = 50;
    items[0].stock = 10;
    items[0].revenue = 0;
    items[0].details.expiry = (struct Date){15, 11, 2026};

    items[1].id = 102;
    strcpy(items[1].name, "Idli");
    items[1].type = COOKED;
    items[1].price = 30;
    items[1].stock = 20;
    items[1].revenue = 0;
    strcpy(items[1].details.preparedTime, "08:00");

    items[2].id = 103;
    strcpy(items[2].name, "Combo Meal");
    items[2].type = COMBO;
    items[2].price = 100;
    items[2].stock = 5;
    items[2].revenue = 0;
    items[2].details.combo.count = 2;
    items[2].details.combo.itemIndex[0] = 0;
    items[2].details.combo.quantity[0] = 1;
    items[2].details.combo.itemIndex[1] = 1;
    items[2].details.combo.quantity[1] = 2;

    recordSale(0, 2);
    recordSale(1, 3);
    recordSale(2, 1);
    recordSale(2, 10);

    checkExpiry((struct Date){13, 11, 2026});

    printSummary();

    return 0;
}