 /**
  ******************************************************************************
  * @file    stm32l152c_discovery_glass_lcd.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file for stm32l152c_discovery_glass_lcd.c module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM32L152C_DISCOVERY
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L152C_DISCOVERY_GLASS_LCD_H
#define __STM32L152C_DISCOVERY_GLASS_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l152c_discovery.h"

/** @addtogroup STM32L152C_DISCOVERY_GLASS_LCD
  * @{
  */ 

/** @defgroup STM32L152C_DISCOVERY_GLASS_LCD_Exported_Types Exported Types
  * @{
  */

/**
  * @brief LCD Glass point
  * Warning: element values correspond to LCD Glass point.
  */

typedef enum
{
  POINT_OFF = 0,
  POINT_ON = 1
}Point_Typedef;

/**
  * @brief LCD Glass Double point
  * Warning: element values correspond to LCD Glass Double point.
  */
typedef enum
{
  DOUBLEPOINT_OFF = 0,
  DOUBLEPOINT_ON = 1
}DoublePoint_Typedef;

/**
  * @}
  */ 

/** @defgroup STM32L152C_DISCOVERY_GLASS_LCD_Exported_Defines Exported Defines
  * @{
  */

/* Define for scrolling sentences*/
#define SCROLL_SPEED    75
#define SCROLL_SPEED_L  600
#define SCROLL_NUM      1

/* Element values correspond to LCD Glass BAR Level. */
#define BATTERYLEVEL_OFF    0
#define BATTERYLEVEL_1_4    1
#define BATTERYLEVEL_1_2    2
#define BATTERYLEVEL_3_4    3
#define BATTERYLEVEL_FULL   4

#define DOT             0x8000 /* for add decimal point in string */
#define DOUBLE_DOT      0x4000 /* for add decimal point in string */

/* code for 'µ' character */
#define C_UMAP          0x6084

/* code for 'm' character */
#define C_MMAP          0xb210

/* code for 'n' character */
#define C_NMAP          0x2210

/* constant code for '*' character */
#define STAR            0xA0DD

/* constant code for '-' character */
#define C_MINUS         0xA000

/* constant code for '/' */
#define C_SLATCH        0x00c0

/* constant code for ° */
#define C_PERCENT_1     0xec00

/* constant code  for small o */
#define C_PERCENT_2     0xb300

#define C_FULL          0xffdd

/**
  * @}
  */   

/** @addtogroup STM32L152C_DISCOVERY_LCD_Exported_Functions
  * @{
  */
void BSP_LCD_GLASS_Init(void);
void BSP_LCD_GLASS_BlinkConfig(uint32_t BlinkMode, uint32_t BlinkFrequency);
void BSP_LCD_GLASS_Contrast(uint32_t Contrast);
void BSP_LCD_GLASS_DisplayChar(uint8_t* ch, Point_Typedef point, DoublePoint_Typedef DoublePoint,uint8_t position);
void BSP_LCD_GLASS_DisplayString(uint8_t* ptr);
void BSP_LCD_GLASS_WriteChar(uint8_t* ch, uint8_t Point, uint8_t Column, uint8_t Position);
void BSP_LCD_GLASS_DisplayStrDeci(uint16_t* ptr);
void BSP_LCD_GLASS_ScrollSentence(uint8_t* ptr, uint16_t nScroll, uint16_t ScrollSpeed);
void BSP_LCD_GLASS_BarLevelConfig(uint8_t BarLevel);
void BSP_LCD_GLASS_Clear(void);

/**
  * @}
  */

/**
  * @}
  */   

#ifdef __cplusplus
}
#endif

#endif /* __STM32L152C_DISCOVERY_GLASS_LCD_H */

/**
  * @}
  */   

/**
  * @}
  */   

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
