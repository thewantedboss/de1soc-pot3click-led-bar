#include <stdio.h>
#include <stdlib.h>
#include "leds.h"

int leds_init(void) {

    FILE *fp = fopen("/sys/class/leds/fpga_led0/brightness", "w");
    if (!fp) {
        printf("Error opening -> /sys/class/leds/fpga_led0/brightness\n");
        return -1;
    }
    fclose(fp);
    return 0;
}

int leds_set_count(int count) {
    if (count < 0) count = 0;
    if (count > 10) count = 10;

    for (int i = 0; i < 10; i++) {
        char path[64];

        snprintf(path, sizeof(path), "/sys/class/leds/fpga_led%d/brightness", i);
        
        FILE *fp = fopen(path, "w");
        if (fp) {
            fprintf(fp, "%d", (i < count) ? 1 : 0);
            fclose(fp);
        }
    }
    return 0;
}

void leds_cleanup(void) {
    leds_set_count(0);
}
