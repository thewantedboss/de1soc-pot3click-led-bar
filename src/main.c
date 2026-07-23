#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "adc.h"
#include "leds.h"

#define ADC_MIN 24576  // All LEDS turned off
#define ADC_MAX 28270  // All LEDS turned on

static volatile int running = 1;
/**
 * @brief Signal handler for graceful application termination.
 *
 * Catches SIGINT (Ctrl+C) and SIGTERM signals, clearing the global running 
 * flag to allow the main loop to exit naturally and clean up resources.
 *
 * @param sig Signal number received from the operating system.
 */
void handle_sigint(int sig) {
    (void)sig;
    running = 0;
}
/**
 * @brief Main application entry point.
 *
 * Registers signal handlers, initializes ADC and LED subsystems, and runs 
 * a continuous processing loop. Reads raw ADC sample values, normalizes them 
 * to a 0-10 scale, updates the FPGA LED display, and performs cleanup upon exit.
 *
 * @return 0 on success, 1 if ADC initialization fils.
 */
int main(void) {
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigint);

    printf("Reading: %d - %d\n", ADC_MIN, ADC_MAX);

    if (adc_init() < 0) {
        printf("Error: Cannot open ADC sysfs file!\n");
        return 1;
    }

    if (leds_init() < 0) {
        printf("Watch out: fpga_leds sys files not found.\n");
    }

    while (running) {
        int raw = adc_read_raw();
        if (raw < 0) {
            usleep(200000);
            continue;
        }

        int current_raw = raw;
        
        if (current_raw < ADC_MIN) current_raw = ADC_MIN;
        if (current_raw > ADC_MAX) current_raw = ADC_MAX;

        float ratio = (float)(current_raw - ADC_MIN) / (float)(ADC_MAX - ADC_MIN);
        int led_count = (int)(ratio * 10.0f + 0.5f);

        if (led_count < 0) led_count = 0;
        if (led_count > 10) led_count = 10;

        leds_set_count(led_count);

        fflush(stdout);

        usleep(100000);
    }

    printf("\n Shut down!\n");
    leds_cleanup();
    return 0;
}
