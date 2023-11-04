#include <stdio.h>
#include <pigpio.h>
#include "led_control.h"

#define LED_PIN 15   // GPIO pin connected to the LED
#define BUTTON_PIN 18 // GPIO pin connected to the button

int led_state = 0; // Variable to track LED state

int initialize_led() {
    if (gpioInitialise() < 0) {
        // Return an error code to indicate initialization failure
        return -1;
    }

    gpioSetMode(LED_PIN, PI_OUTPUT);
    gpioSetMode(BUTTON_PIN, PI_INPUT);

    // Enable the internal pull-up resistor for the button
    gpioSetPullUpDown(BUTTON_PIN, PI_PUD_UP);

    // Return 0 to indicate successful initialization
    return 0;
}

void toggle_led() {
    if (led_state == 0) {
        gpioWrite(LED_PIN, 1); // Turn the LED on
        led_state = 1; // LED is now ON
    } else {
        gpioWrite(LED_PIN, 0); // Turn the LED off
        led_state = 0; // LED is now OFF
    }
}

int is_button_pressed() {
    return !gpioRead(BUTTON_PIN); // Button is pressed when GPIO pin is LOW
}

int main() {
    // Initialize PiGPIO
    if (gpioInitialise() < 0) {
        fprintf(stderr, "PiGPIO initialization failed\n");
        return 1;
    }

    // Initialize LED and Button
    if (initialize_led() < 0) {
        fprintf(stderr, "LED initialization failed\n");
        gpioTerminate();
        return 1;
    }

    printf("Press the button to toggle the LED. Press Ctrl+C to exit.\n");

    while (1) {
        if (is_button_pressed()) {
            toggle_led();
            printf("LED is %s\n", led_state ? "ON" : "OFF");
            // Add a delay to avoid rapid button presses
            gpioDelay(200000); // 200ms
        }
    }

    // Cleanup and terminate PiGPIO
    gpioTerminate();

    return 0;
}


