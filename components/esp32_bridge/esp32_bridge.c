#include "esp32_bridge.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

// static bool isInit = false;

uint64_t usecTimestamp(void)
{

    return (uint64_t)esp_timer_get_time();
}

void sleepus(uint32_t us)
{

    uint64_t start = usecTimestamp();

    while ((start + us) > usecTimestamp())
    {
        vTaskDelay(1);
    };
}