#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"



void app_main(void)
{
    gpio_reset_pin(16);
    gpio_set_direction(16, GPIO_MODE_OUTPUT);
    gpio_set_level(16, 1);

    adc_oneshot_unit_handle_t adc_handle;
    adc_oneshot_unit_init_cfg_t init_config = {.unit_id = ADC_UNIT_2};
    adc_oneshot_new_unit(&init_config, &adc_handle);

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_6, &config);

    while(1){
        int value;
        adc_oneshot_read(adc_handle, ADC_CHANNEL_6, &value);
        printf("ADC: %d\n", value);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}