/**
 * @file leds.h
 * @brief Header file for controlling FPGA user LEDs via Linux sysfs.
 *
 * Provides function declarations for initializing, setting, and turning off
 * the FPGA LEDs using the kernel LED subsystem interface.
 */
#ifndef LEDS_H
#define LEDS_H

/**
 * @brief Initializes the FPGA LED subsystem.
 *
 * Checks for the presence of LED sysfs nodes (/sys/class/leds/fpga_ledX)
 * and prepares the driver for operation.
 *
 * @return 0 on success, or -1 if no LED sysfs entries are found.
 */
int leds_init(void);
/**
 * @brief Sets the number of active LEDs.
 *
 * Illuminates 'count' number of LEDs sequentially (from LED 0 up to count - 1)
 * and turns off the rest, creating a bar-graph display effect.
 *
 * @param count Number of LEDs to turn on (range: 0 to 10).
 * @return 0 on success, or -1 if the count value is out of range.
 */
int leds_set_count(int count);
/**
 * @brief Turns off all LEDs and performs subsystem cleanup.
 *
 * Resets all FPGA LED brightness attributes to 0 to leave the board 
 * in a safe state before application shutdown.
 */
void leds_cleanup(void);

#endif
