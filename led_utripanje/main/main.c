#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"  
#include "driver/gpio.h"

#define LED1 GPIO_NUM_16
#define LED2 GPIO_NUM_17
#define LED3 GPIO_NUM_18

void led_init(void){
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED1)| (1ULL << LED2)| (1ULL << LED3),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void led1_task(void *pvParameter){
    while(1) {
        gpio_set_level(LED1, 1); // Turn on LED
        vTaskDelay(500 / portTICK_PERIOD_MS); // Wait for 1 second
        gpio_set_level(LED1, 0); // Turn off LED
        vTaskDelay(500 / portTICK_PERIOD_MS); // Wait for 1 second
    }
}   

void led2_task(void *pvParameter){
    while(1) {
        gpio_set_level(LED2, 1); // Turn on LED
        vTaskDelay(125 / portTICK_PERIOD_MS); // Wait for 1 second
        gpio_set_level(LED2, 0); // Turn off LED
        vTaskDelay(125 / portTICK_PERIOD_MS); // Wait for 1 second
    }
}

void led3_task(void *pvParameter){
    while(1) {
        gpio_set_level(LED3, 1); // Turn on LED
        vTaskDelay(166 / portTICK_PERIOD_MS); // Wait for 1 second
        gpio_set_level(LED3, 0); // Turn off LED
        vTaskDelay(166 / portTICK_PERIOD_MS); // Wait for 1 second
    }
}

void app_main(void)
{
    led_init();
    xTaskCreate(led1_task, "LED1 Task", 2048, NULL, 5, NULL);
    xTaskCreate(led2_task, "LED2 Task", 2048, NULL, 5, NULL);
    xTaskCreate(led3_task, "LED3 Task", 2048, NULL, 5, NULL);
    
}