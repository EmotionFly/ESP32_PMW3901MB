/* vl53l1 Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "flowdeck_v1v2.h"
#include "driver/gpio.h"
#include "esp32_bridge.h"
//#include "esp_log.h"

#define TAG "PMW3901"

void app_main(void)
{
    // Initialize NVS

    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = (1ULL << CONFIG_LED_RED_IO) | (1ULL << CONFIG_LED_BLUE_IO);
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
    bool trigger = true;

    for (size_t i = 0; i < 2; i++)
    {

        vTaskDelay(M2T(1000));
        ESP_LOGI(TAG, "Waiting pmw3901 power ON %d.", 1 - i);
        gpio_set_level(CONFIG_LED_RED_IO, trigger);

        if (trigger)
        {
            trigger = FALSE;
        }
        else
        {
            trigger = TRUE;
        }
    }

    flowdeck2Init();

    if (flowdeck2Test() == true)
    {
        ESP_LOGI(TAG, "PMW3901 SPI connection [OK].\n");
    }
    else
    {
        //TODO: Should sensor test fail hard if no connection
        ESP_LOGI(TAG, "PMW3901 SPI connection [FAIL].\n");
    }

    gpio_set_level(CONFIG_LED_RED_IO, false);

    while (1)
    {
        vTaskDelay(M2T(1000));
        gpio_set_level(CONFIG_LED_BLUE_IO, trigger);

        if (trigger)
        {
            trigger = FALSE;
        }
        else
        {
            trigger = TRUE;
        }
    }
}
