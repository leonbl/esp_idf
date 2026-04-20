#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>
#include <stdio.h>

#define LED 16
#define KEY 15

uint32_t led_freq = 0;

void io_init() {
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = (1ULL << LED);
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;
  gpio_config(&io_conf);
  gpio_config_t key_conf = {.intr_type = GPIO_INTR_DISABLE,
                            .mode = GPIO_MODE_INPUT,
                            .pin_bit_mask = (1ULL << KEY),
                            .pull_down_en = 0,
                            .pull_up_en = 0};
  gpio_config(&key_conf);
}

void led_task(void *pvParameter) {
  while (1) {
    switch (led_freq) {
    case 0:
      gpio_set_level(LED, 1);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      gpio_set_level(LED, 0);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      break;
    case 1:
      gpio_set_level(LED, 1);
      vTaskDelay(250 / portTICK_PERIOD_MS);
      gpio_set_level(LED, 0);
      vTaskDelay(250 / portTICK_PERIOD_MS);
      break;
    }
  }
}

void usart_task(void *pvParameter) {
  while (1) {
    switch (led_freq) {
    case 0:
        printf("LED frequency: 1Hz\n");
        break;
    case 1:
        printf("LED frequency: 2Hz\n");
        break;
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void key_task(void *pvParameter) {
  while (1) {
    if (gpio_get_level(KEY) == 0) {
      led_freq = !led_freq;
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void app_main(void) {
    io_init();
    xTaskCreate(led_task, "led_task", 2048, NULL, 1, NULL);
    xTaskCreate(usart_task, "usart_task", 2048, NULL, 1, NULL);
    xTaskCreate(key_task, "key_task", 2048, NULL, 1, NULL);
}