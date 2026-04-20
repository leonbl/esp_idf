#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"  
#include "driver/gpio.h"

#define LED1 GPIO_NUM_16

void led_init(void){
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED1),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void app_main(void)
{
    led_init();
    while(1) {
        gpio_set_level(LED1, 1); // Turn on LED
        vTaskDelay(500 / portTICK_PERIOD_MS); // Wait for 1 second
        gpio_set_level(LED1, 0); // Turn off LED
        vTaskDelay(500 / portTICK_PERIOD_MS); // Wait for 1 second
    }
}