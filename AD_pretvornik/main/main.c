#include <stdio.h>
#include "driver/gpio.h"

void app_main(void)
{
    gpio_reset_pin(16);
    gpio_set_direction(16, GPIO_MODE_OUTPUT);
    gpio_set_level(16, 1);
    while(1){
        // praskaj se 
    }
}