#include <stdio.h>
#include <stdlib.h>
#include "adc.h"

//#define ADC_RAW_PATH "/sys/bus/iio/devices/iio:device%d/in_voltage0-voltage1_raw"

/*
 * During Linux boot, IIO devices (e.g., /sys/bus/iio/devices/iio:deviceX) 
 * can be assigned dynamic index numbers depending on the driver probing order. 
 * To avoid hardcoding static paths, this implementation scans all available 
 * IIO devices at startup, reads their 'name' attribute, and dynamically matches 
 * the target converter (in this case: "mcp3201"). Once found, it constructs the absolute path 
 * to the differential voltage channel for subsequent raw reads.
 */

#define TARGET_ADC_NAME "mcp3201"

static char actual_adc_path[256] = "";

int adc_init(void) {
    char name_path[128];
    char device_name[64];

    for (int i = 0; i < 5; i++) {
        snprintf(name_path, sizeof(name_path), "/sys/bus/iio/devices/iio:device%d/name", i);
        FILE *fp = fopen(name_path, "r");
        if (fp) {
            if (fscanf(fp, "%63s", device_name) == 1) {
                if (strstr(device_name, TARGET_ADC_NAME) != NULL) {
                    snprintf(actual_adc_path, sizeof(actual_adc_path), 
                             "/sys/bus/iio/devices/iio:device%d/in_voltage0-voltage1_raw", i);
                    fclose(fp);
                    printf("ADC found at: %s\n", actual_adc_path);
                    return 0;
                }
            }
            fclose(fp);
        }
    }

    printf("Error: ADC device '%s' not found!\n", TARGET_ADC_NAME);
    return -1;
}

int adc_read_raw(void) {
    if (actual_adc_path[0] == '\0') return -1;

    FILE *fp = fopen(actual_adc_path, "r");
    if (!fp) return -1;

    int raw_val = 0;
    if (fscanf(fp, "%d", &raw_val) != 1) {
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return raw_val;
}
