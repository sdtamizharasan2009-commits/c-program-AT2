#include <stdio.h>

enum kind {
    TEMPERATURE,
    HUMIDITY,
    STATUS
};

struct Reading {
    enum kind type;
    union {
        float celsius;
        int percent;
        char status[8];
    } value;
};

void show(const struct Reading *r) {
    switch (r->type) {
        case TEMPERATURE:
            printf("Temp %.1f C\n", r->value.celsius);
            break;
        case HUMIDITY:
            printf("Humidity %d %%\n", r->value.percent);
            break;
        case STATUS:
            printf("Status %s\n", r->value.status);
            break;
    }
}

int main(void) {
    struct Reading log[3] = {
        {TEMPERATURE, {.celsius = 31.5}},
        {HUMIDITY, {.percent = 68}},
        {STATUS, {.status = "OK"}}
    };

    printf("sizeof union = %zu, sizeof struct reading = %zu\n",
           sizeof log[0].value, sizeof log[0]);

    for (int i = 0; i < 3; i++)
        show(&log[i]);

    return 0;
}