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
 * digital.c - Deck-API digital IO implementation
 */

//#include "deck.h"

//#include "stm32fxxx.h"
#include "driver/gpio.h"
#include "deck_digital.h"
#include "esp_log.h"

void pinMode(uint32_t pin, uint32_t mode)
{
  if (pin > 35 ) {
    return;
  }

  gpio_config_t io_conf;
  //disable interrupt
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
  //bit mask of the pins that you want to set,e.g.GPIO18/19
  io_conf.pin_bit_mask = (1ULL<<pin);
  //disable pull-down mode
  io_conf.pull_down_en = 0;
  //disable pull-up mode
  io_conf.pull_up_en = 0;
  //configure GPIO with the given settings

  //set as output mode
  if (mode == OUTPUT)  {io_conf.mode = GPIO_MODE_OUTPUT;}
  if (mode == INPUT_PULLUP) {io_conf.mode = GPIO_MODE_INPUT; io_conf.pull_up_en = 1;}
  if (mode == INPUT_PULLDOWN) {io_conf.mode = GPIO_MODE_INPUT; io_conf.pull_down_en = 1;}
  gpio_config(&io_conf);
}

void digitalWrite(uint32_t pin, uint32_t val)
{
  if (pin > 35 ) {
    return;
  }

  if (val) val = 1;

  gpio_set_level(pin, val);
  // ESP_LOGI("GPIO","GPIO%d = %d",pin,val);
}

int digitalRead(uint32_t pin)
{
  if (pin > 35) {
    return 0;
  }

  int val = gpio_get_level(pin);
  return val;
}
