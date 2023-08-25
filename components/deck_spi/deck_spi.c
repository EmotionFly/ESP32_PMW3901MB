/*
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2015 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * deck_spi.c - Deck-API SPI communication implementation
 */

//#include "deck.h"

/*ESP includes */
#include "deck_spi.h"
#include "driver/spi_master.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"

#define TAG "DECK_SPI"

#define SPI                   SPI1

#define SPI_SCK_PIN           14
#define SPI_MISO_PIN          12
#define SPI_MOSI_PIN          13
#define SPI_CS_PIN            15

#define DUMMY_BYTE            0xA5

static bool isInit = false;

// static SemaphoreHandle_t txComplete;
// static SemaphoreHandle_t rxComplete;
static SemaphoreHandle_t spiMutex;

// static void spiDMAInit();
static void spiConfigureWithSpeed(uint16_t baudRatePrescaler);

static spi_device_handle_t spi;

void spiBegin(void)
{

    if(isInit){
        return;
    }
    //GPIO_InitTypeDef GPIO_InitStructure;

    // binary semaphores created using xSemaphoreCreateBinary() are created in a state
    // such that the the semaphore must first be 'given' before it can be 'taken'
    // txComplete = xSemaphoreCreateBinary();
    // rxComplete = xSemaphoreCreateBinary();
    spiMutex = xSemaphoreCreateMutex();

    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .miso_io_num = SPI_MISO_PIN,
        .mosi_io_num = SPI_MOSI_PIN,
        .sclk_io_num = SPI_SCK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0};//Defaults to 4094 if 0
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = SPI_BAUDRATE_2MHZ,    // Clock out at 10 MHz
        .mode = 0,                              // SPI mode 0
        .spics_io_num = -1,                     // CS pin
        .queue_size = 8,                        // We want to be able to queue 7 transactions at a time
        /*.pre_cb = lcd_spi_pre_transfer_callback, //Specify pre-transfer callback to handle D/C line*/
    };

    //Initialize the SPI bus
    ret = spi_bus_initialize(HSPI_HOST, &buscfg, 1);
    ESP_ERROR_CHECK(ret);

    //Attach the pmw3901 to the SPI bus
    ret = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);

    isInit = true;
}

// static void spiDMAInit()
// {
//   //TODO: removed

// }

static void spiConfigureWithSpeed(uint16_t baudRatePrescaler)
{
  //TODO: do not support

}

bool spiTest(void)
{
    return isInit;
}

bool spiExchange(size_t length, bool is_tx , const uint8_t * data_tx, uint8_t * data_rx)
{
    if (isInit != true)
    {
        return false;
    }

    if (length == 0)
        return 0; //no need to send anything
    esp_err_t ret;

    if (is_tx == true)
    {
        static spi_transaction_t t;
        memset(&t, 0, sizeof(t));                   //Zero out the transaction
        t.length = length * 8;                      //Len is in bytes, transaction length is in bits.
        t.tx_buffer = data_tx;                      //Data
        ret = spi_device_polling_transmit(spi, &t); //Transmit!
        assert(ret == ESP_OK);                      //Should have had no issues.
        // ESP_LOGW(TAG,"spi send = %d",t.length);
        return true;
    }

    static spi_transaction_t r;
    memset(&r, 0, sizeof(r));
    r.length = length * 8;
    r.flags = SPI_TRANS_USE_RXDATA;
    ret = spi_device_polling_transmit(spi, &r);
    assert(ret == ESP_OK);

    if (r.rxlength > 0)
    {
        // ESP_LOGW(TAG,"rxlength = %d",r.rxlength);
        memcpy(data_rx,r.rx_data,length);
    }
    // // Wait for completion
    // bool result = (xSemaphoreTake(txComplete, portMAX_DELAY) == pdTRUE)
    //          && (xSemaphoreTake(rxComplete, portMAX_DELAY) == pdTRUE);

    return true;
}

void spiBeginTransaction(uint32_t baudRatePrescaler)
{
    xSemaphoreTake(spiMutex, portMAX_DELAY);
    spiConfigureWithSpeed(baudRatePrescaler);
}

void spiEndTransaction()
{
    xSemaphoreGive(spiMutex);
}

void __attribute__((used)) SPI_TX_DMA_IRQHandler(void)
{
    // TODO: removed

    // xSemaphoreGiveFromISR(txComplete, &xHigherPriorityTaskWoken);
}

void __attribute__((used)) SPI_RX_DMA_IRQHandler(void)
{
    // TODO: removed
    // xSemaphoreGiveFromISR(rxComplete, &xHigherPriorityTaskWoken);
}
