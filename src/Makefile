CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -O2
TARGET = adc_led_app

SRCS = main.c adc.c leds.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
