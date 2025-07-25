#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

static const char *TAG = "ADC";

esp_adc_cal_characteristics_t adc1_chars;
uint32_t voltage;


void app_main(void)
{

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);

    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_12));

    while (1) 
    {
        voltage = esp_adc_cal_raw_to_voltage(adc1_get_raw(ADC1_CHANNEL_6), &adc1_chars);
        ESP_LOGI(TAG, "ADC1_CHANNEL_6: %lu mV", voltage);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}