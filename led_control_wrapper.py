# led_control_wrapper.py

import ctypes

# Load the shared library
led_control = ctypes.CDLL('./libled_control.so')

# Define error code constants
LED_CONTROL_INIT_FAILURE = -1

# Define Python functions to call the C functions
def initialize_led():
    result = led_control.initialize_led()
    if result == LED_CONTROL_INIT_FAILURE:
        raise RuntimeError("LED initialization failed")

def turn_on_led():
    led_control.turn_on_led()

def turn_off_led():
    led_control.turn_off_led()
