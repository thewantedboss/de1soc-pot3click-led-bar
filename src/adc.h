/**
 * @file adc.h
 * @brief Header file for Analog-to-Digital Converter (ADC) interface.
 *
 * Provides function declarations for initializing the ADC peripheral
 * and reading raw conversion values via the Linux IIO sysfs interface.
 */
#ifndef ADC_H
#define ADC_H

/**
 * @brief Initializes the ADC device.
 *
 * Dynamically detects and verifies the presence of the required ADC device 
 * in the sysfs filesystem (/sys/bus/iio/devices/).
 *
 * @return 0 on success, -1 if the device was not found or failed to open.
 */
int adc_init(void);
/**
 * @brief Reads the raw digital value from the configured ADC channel.
 *
 * Opens the corresponding sysfs raw attribute file and reads the latest 
 * raw sample value.
 *
 * @return The raw ADC conversion value on success, or -1 on error.
 */
int adc_read_raw(void);

#endif
