#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <sys/_intsup.h>
#define LEVO 15
#define DESNO 4

// Todo: uporabljaj jezik Slovenščina!

void app_main(void) {
  // Configure GPIO pin 2 as an output
  gpio_reset_pin(19);
  gpio_set_direction(19, GPIO_MODE_OUTPUT);
  gpio_reset_pin(18);
  gpio_set_direction(18, GPIO_MODE_OUTPUT);
  gpio_reset_pin(17);
  gpio_set_direction(17, GPIO_MODE_OUTPUT);
  gpio_reset_pin(16);
  gpio_set_direction(16, GPIO_MODE_OUTPUT);
  gpio_reset_pin(15);
  gpio_set_direction(15, GPIO_MODE_INPUT);
  gpio_reset_pin(4);
  gpio_set_direction(4, GPIO_MODE_INPUT);
  int stanje = 0;
  while (1) {
    int levo = gpio_get_level(LEVO);
    int desno = gpio_get_level(DESNO);

    if (levo != desno) {
      if (levo == 0) {
        stanje -= 1; // Levo
        if (stanje == -1) {
          stanje = 0;
        }
      } else if (desno == 0) {
        stanje += 1; // Desno
        if (stanje == 4) {
          stanje = 3;
        }
      }
      printf("Stanje: %d\n", stanje);

      gpio_set_level(16, (stanje == 0));
      gpio_set_level(17, (stanje == 1));
      gpio_set_level(18, (stanje == 2));
      gpio_set_level(19, (stanje == 3));

      vTaskDelay(100 / portTICK_PERIOD_MS); // Delay for a short period
    }
  }
}