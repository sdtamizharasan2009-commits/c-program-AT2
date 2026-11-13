#include <stdio.h>

struct Account {
    int number;
    float balance;
};

void addInterest(struct Account *a, float rate) {
    printf("Address inside function: %p\n", (void *)a);
    a->balance = a->balance + a->balance * rate / 100;
}

int main(void) {
    struct Account list[3] = {
        {101, 5000},
        {102, 12000},
        {103, 800}
    };

    struct Account *p = list;

    printf("Address in main: %p\n", (void *)p);

    for (int i = 0; i < 3; i++)
        addInterest(&list[i], 4);

    printf("\nUpdated Account Balances\n");

    for (int i = 0; i < 3; i++)
        printf("%d %.2f\n", p[i].number, p[i].balance);

    return 0;
}