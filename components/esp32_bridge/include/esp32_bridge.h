#ifndef ESP32_BRIDGE_H
#define ESP32_BRIDGE_H

#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/gpio.h"
// #include "freertos/portmacro.h"

// /*!< STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */
// typedef int32_t  s32;
// typedef int16_t s16;
// typedef int8_t  s8;

// typedef const int32_t sc32;  /*!< Read Only */
// typedef const int16_t sc16;  /*!< Read Only */
// typedef const int8_t sc8;   /*!< Read Only */

// typedef __IO int32_t  vs32;
// typedef __IO int16_t  vs16;
// typedef __IO int8_t   vs8;

// typedef __I int32_t vsc32;  /*!< Read Only */
// typedef __I int16_t vsc16;  /*!< Read Only */
// typedef __I int8_t vsc8;   /*!< Read Only */

// typedef uint32_t  u32;
// typedef uint16_t u16;
// typedef uint8_t  u8;

// typedef const uint32_t uc32;  /*!< Read Only */
// typedef const uint16_t uc16;  /*!< Read Only */
// typedef const uint8_t uc8;   /*!< Read Only */

// typedef __IO uint32_t  vu32;
// typedef __IO uint16_t vu16;
// typedef __IO uint8_t  vu8;

// typedef __I uint32_t vuc32;  /*!< Read Only */
// typedef __I uint16_t vuc16;  /*!< Read Only */
// typedef __I uint8_t vuc8;   /*!< Read Only */

#ifndef __cplusplus
//typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#endif

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
/**
  * @brief Inter-integrated Circuit Interface
  */
typedef struct
{

//   __IO uint16_t CR1;  //定义在stm32f10x.h
//   uint16_t  RESERVED0;
//   __IO uint16_t CR2;
//   uint16_t  RESERVED1;
//   __IO uint16_t OAR1;
//   uint16_t  RESERVED2;
//   __IO uint16_t OAR2;
//   uint16_t  RESERVED3;
//   __IO uint16_t DR;
//   uint16_t  RESERVED4;
//   __IO uint16_t SR1;
//   uint16_t  RESERVED5;
//   __IO uint16_t SR2;
//   uint16_t  RESERVED6;
//   __IO uint16_t CCR;
//   uint16_t  RESERVED7;
//   __IO uint16_t TRISE;
//   uint16_t  RESERVED8;
} I2C_TypeDef;

/**
  * @brief General Purpose I/O
  */

typedef struct
{
//   __IO uint32_t CRL;
//   __IO uint32_t CRH;
//   __IO uint32_t IDR;
//   __IO uint32_t ODR;
//   __IO uint32_t BSRR;
//   __IO uint32_t BRR;
//   __IO uint32_t LCKR;
} GPIO_TypeDef;

//freertosconfig
typedef void DMA_Stream_TypeDef;  //stm32f103未定义
typedef int DMA_InitTypeDef; //stm32f103未定义
typedef void * xSemaphoreHandle;
typedef void * SemaphoreHandle_t;
typedef void * xQueueHandle;
typedef void * QueueHandle_t;
typedef void * TaskHandle_t;
typedef void TIM_TypeDef;
typedef void TIM_OCInitTypeDef;
typedef uint32_t TickType_t;
typedef uint32_t portTickType;

#define TASK_LED_ID_NBR         1
#define TASK_RADIO_ID_NBR       2
#define TASK_STABILIZER_ID_NBR  3
#define TASK_ADC_ID_NBR         4
#define TASK_PM_ID_NBR          5
#define TASK_PROXIMITY_ID_NBR   6
// typedef void * esp_timer_handle_t;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;

#define __IO

#ifndef FALSE
# define FALSE 0
#endif

#ifndef TRUE
# define TRUE 1
#endif

#define pdFALSE			( ( BaseType_t ) 0 )
#define pdTRUE			( ( BaseType_t ) 1 )

#define pdPASS			( pdTRUE )
#define pdFAIL			( pdFALSE )
#define errQUEUE_EMPTY	( ( BaseType_t ) 0 )
#define errQUEUE_FULL	( ( BaseType_t ) 0 )

#define M2T(X) ((unsigned int)(X)/ portTICK_PERIOD_MS) //ms to tick
#define F2T(X) ((unsigned int)((configTICK_RATE_HZ/(X))))
#define T2M(X) ((unsigned int)(X)* portTICK_PERIOD_MS)   //tick to ms

//#define DEBUG_PRINT printf

#define assert_param(e)  if (e) ; \
        else assertFail( #e, __FILE__, __LINE__ )

uint64_t usecTimestamp(void);

void sleepus(uint32_t ns);

/* GPIO */

#endif