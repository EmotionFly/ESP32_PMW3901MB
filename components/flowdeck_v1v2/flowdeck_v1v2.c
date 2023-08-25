/*
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * LPS node firmware.
 *
 * Copyright 2017, Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */
/* flowdeck.c: Flow deck driver */
#define TAG "FLOW"
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

//#include "deck.h"
#include "pmw3901.h"
#include "esp32_bridge.h"

#define AVERAGE_HISTORY_LENGTH 4
#define OULIER_LIMIT 100
#define LP_CONSTANT 0.8f
// #define USE_LP_FILTER
// #define USE_MA_SMOOTHING

float dpixelx_previous = 0;
float dpixely_previous = 0;

// static uint8_t outlierCount = 0;

static bool isInit1 = false;
static bool isInit2 = false;

motionBurst_t currentMotion;

// Disables pushing the flow measurement in the EKF
// static bool useFlowDisabled = false;

#define NCS_PIN 15

static void flowdeckTask(void *param)
{
    //systemWaitStart();

    while(1)
    {
        vTaskDelay(500);

        pmw3901ReadMotion(NCS_PIN, &currentMotion);

        // Flip motion information to comply with sensor mounting
        // (might need to be changed if mounted differently)
        int16_t accpx = -currentMotion.deltaY;
        int16_t accpy = -currentMotion.deltaX;

        printf("accpx = %d  accpy = %d\n", accpx, accpy);
    }
}

void flowdeck2Init()
{
    if (isInit1 || isInit2) {
        return;
    }

    // Initialize the VL53L1 sensor using the zRanger deck driver
    // const DeckDriver *zRanger = deckFindDriverByName("bcZRanger2");
    // zRanger->init(NULL);

    if (pmw3901Init(NCS_PIN))
    {
        xTaskCreate(flowdeckTask,"FLOW", 4096, NULL,3, NULL);

        isInit2 = true;
    }
}

bool flowdeck2Test()
{
    if (!isInit2) {
        ESP_LOGW(TAG,"Error while initializing the PMW3901 sensor.\n");
    } else
    {
        ESP_LOGW(TAG,"Initialed the PMW3901 sensor.\n");
    }

    // Test the VL53L1 driver
    //const DeckDriver *zRanger = deckFindDriverByName("bcZRanger2");

    return isInit2;//zRanger->test();
}
