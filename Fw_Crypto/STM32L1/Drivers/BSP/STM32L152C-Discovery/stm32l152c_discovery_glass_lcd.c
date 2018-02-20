/**
  ******************************************************************************
  * @file    stm32l152c_discovery_glass_lcd.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   This file includes the LCD Glass driver for LCD Module of 
  *          STM32L152C-Discovery board.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l152c_discovery_glass_lcd.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32L152C_DISCOVERY
  * @{
  */
  
/** @defgroup STM32L152C_DISCOVERY_GLASS_LCD STM32L152C-Discovery Glass LCD
  * @brief This file includes the LCD Glass driver for LCD Module of 
  *        STM32L152C-DISCOVERY board.
  * @{
  */ 

/** @defgroup STM32L152C_DISCOVERY_GLASS_LCD_Private_Defines Private Defines
  * @{
  */
#define ASCII_CHAR_0                  0x30  /* 0 */
#define ASCII_CHAR_AT_SYMBOL          0x40  /* @ */
#define ASCII_CHAR_LEFT_OPEN_BRACKET  0x5B  /* [ */
#define ASCII_CHAR_APOSTROPHE         0x60  /* ` */
#define ASCII_CHAR_LEFT_OPEN_BRACE    0x7B  /* ( */
/**
  * @}
  */   


/** @defgroup STM32L152C_DISCOVERY_GLASS_LCD_Private_Variables Private Variables
  * @{
  */ 

/* this variable can be used for accelerate the scrolling exit when push user button */
__IO uint8_t bLCDGlass_KeyPressed = 0; 

/**
  @verbatim
================================================================================
                              GLASS LCD MAPPING
================================================================================
      A
     _  ----------
COL |_| |\   |J  /|
       F| H  |  K |B
     _  |  \ | /  |
COL |_| --G-- --M--
        |   /| \  |
       E|  Q |  N |C
     _  | /  |P  \|   
DP  |_| -----------  
      D         

 An LCD character coding is based on the following matrix:
      { E , D , P , N   }
      { M , C , COL , DP}
      { B , A , K , J   }
      { G , F , Q , H   }

 The character 'A' for example is:
  -------------------------------
LSB   { 1 , 0 , 0 , 0   }
      { 1 , 1 , 0 , 0   }
      { 1 , 1 , 0 , 0   }
MSB   { 1 , 1 , 0 , 0   }
      -------------------
  'A' =  F    E   0   0 hexa

  @endverbatim
*/

LCD_HandleTypeDef LCDHandle;

/* Constant table for cap characters 'A' --> 'Z' */
const uint16_t CapLetterMap[26]=
    {
        /* A      B      C      D      E      F      G      H      I  */
        0xFE00,0x6714,0x1d00,0x4714,0x9d00,0x9c00,0x3f00,0xfa00,0x0014,
        /* J      K      L      M      N      O      P      Q      R  */
        0x5300,0x9841,0x1900,0x5a48,0x5a09,0x5f00,0xFC00,0x5F01,0xFC01,
        /* S      T      U      V      W      X      Y      Z  */
        0xAF00,0x0414,0x5b00,0x18c0,0x5a81,0x00c9,0x0058,0x05c0
    };

/* Constant table for number '0' --> '9' */
const uint16_t NumberMap[10]=
    {
        /* 0      1      2      3      4      5      6      7      8      9  */
        0x5F00,0x4200,0xF500,0x6700,0xEa00,0xAF00,0xBF00,0x04600,0xFF00,0xEF00
    };

uint32_t Digit[4];     /* Digit frame buffer */

/* LCD BAR status: To save the bar setting after writing in LCD RAM memory */
uint8_t LCDBar = BATTERYLEVEL_FULL;

/**
  * @}
  */

/** @defgroup STM32L152C_DISCOVERY_LCD_Private_Functions Private Functions
  * @{
  */
static void Convert(uint8_t* Char, Point_Typedef Point, DoublePoint_Typedef DoublePoint);
static void LCD_MspInit(LCD_HandleTypeDef *hlcd);

/**
  * @}
  */ 

/** @defgroup STM32L152C_DISCOVERY_LCD_Exported_Functions Exported Functions
  * @{
  */ 

/**
  * @brief  Configures the LCD GLASS relative GPIO port IOs and LCD peripheral.
  * @retval None
  */
void BSP_LCD_GLASS_Init(void)
{
  LCDHandle.Instance              = LCD;
  LCDHandle.Init.Prescaler        = LCD_PRESCALER_1;
  LCDHandle.Init.Divider          = LCD_DIVIDER_31;
  LCDHandle.Init.Duty             = LCD_DUTY_1_4;
  LCDHandle.Init.Bias             = LCD_BIAS_1_3;
  LCDHandle.Init.VoltageSource    = LCD_VOLTAGESOURCE_INTERNAL;
  LCDHandle.Init.Contrast         = LCD_CONTRASTLEVEL_4;
  LCDHandle.Init.DeadTime         = LCD_DEADTIME_0;
  LCDHandle.Init.PulseOnDuration  = LCD_PULSEONDURATION_4;
  LCDHandle.Init.BlinkMode        = LCD_BLINKMODE_OFF;
  LCDHandle.Init.BlinkFrequency   = LCD_BLINKFREQUENCY_DIV32;
  LCDHandle.Init.MuxSegment       = LCD_MUXSEGMENT_ENABLE;
  
  /* Initialize the LCD */
  LCD_MspInit(&LCDHandle);
  HAL_LCD_Init(&LCDHandle);

  BSP_LCD_GLASS_Clear();
}

/**
  * @brief  Configures the LCD Blink mode and Blink frequency.
  * @param  BlinkMode: specifies the LCD blink mode.
  *   This parameter can be one of the following values:
  *     @arg LCD_BLINKMODE_OFF:           Blink disabled
  *     @arg LCD_BLINKMODE_SEG0_COM0:     Blink enabled on SEG[0], COM[0] (1 pixel)
  *     @arg LCD_BLINKMODE_SEG0_ALLCOM:   Blink enabled on SEG[0], all COM (up to 8 
  *                                       pixels according to the programmed duty)
  *     @arg LCD_BLINKMODE_ALLSEG_ALLCOM: Blink enabled on all SEG and all COM 
  *                                       (all pixels)
  * @param  BlinkFrequency: specifies the LCD blink frequency.
  *     @arg LCD_BLINKFREQUENCY_DIV8:    The Blink frequency = fLcd/8
  *     @arg LCD_BLINKFREQUENCY_DIV16:   The Blink frequency = fLcd/16
  *     @arg LCD_BLINKFREQUENCY_DIV32:   The Blink frequency = fLcd/32
  *     @arg LCD_BLINKFREQUENCY_DIV64:   The Blink frequency = fLcd/64 
  *     @arg LCD_BLINKFREQUENCY_DIV128:  The Blink frequency = fLcd/128
  *     @arg LCD_BLINKFREQUENCY_DIV256:  The Blink frequency = fLcd/256
  *     @arg LCD_BLINKFREQUENCY_DIV512:  The Blink frequency = fLcd/512
  *     @arg LCD_BLINKFREQUENCY_DIV1024: The Blink frequency = fLcd/1024
  * @retval None
  */
void BSP_LCD_GLASS_BlinkConfig(uint32_t BlinkMode, uint32_t BlinkFrequency)
{
  __HAL_LCD_BLINK_CONFIG(&LCDHandle, BlinkMode, BlinkFrequency);
}

/**
  * @brief  LCD contrast setting
  * @param  Contrast: specifies the LCD Contrast.
  *   This parameter can be one of the following values:
  *     @arg LCD_CONTRASTLEVEL_0: Maximum Voltage = 2.60V
  *     @arg LCD_CONTRASTLEVEL_1: Maximum Voltage = 2.73V
  *     @arg LCD_CONTRASTLEVEL_2: Maximum Voltage = 2.86V
  *     @arg LCD_CONTRASTLEVEL_3: Maximum Voltage = 2.99V
  *     @arg LCD_CONTRASTLEVEL_4: Maximum Voltage = 3.12V
  *     @arg LCD_CONTRASTLEVEL_5: Maximum Voltage = 3.25V
  *     @arg LCD_CONTRASTLEVEL_6: Maximum Voltage = 3.38V
  *     @arg LCD_CONTRASTLEVEL_7: Maximum Voltage = 3.51V
  * @retval None
  */
void BSP_LCD_GLASS_Contrast(uint32_t Contrast)
{
  __HAL_LCD_CONTRAST_CONFIG(&LCDHandle, Contrast);
}

/**
  * @brief  This function writes a char in the LCD frame buffer.
  * @param  ch: the character to display.
  * @param Point: a point to add in front of char
  *         This parameter can be: POINT_OFF or POINT_ON
  * @param Column: flag indicating if a column has to be add in front
  *         of displayed character.
  *         This parameter can be: DOUBLEPOINT_OFF or DOUBLEPOINT_ON.           
  * @param Position: position in the LCD of the caracter to write [1:6]
  * @retval None
  * @note  Required preconditions: The LCD should be cleared before to start the
  *         write operation.  
  */
void BSP_LCD_GLASS_WriteChar(uint8_t* ch, uint8_t Point, uint8_t Column, uint8_t Position)
{
  /* To convert displayed character in segment in array digit */
  Convert(ch, (Point_Typedef)Point, (DoublePoint_Typedef)Column);

  switch (Position)
  {
    /* Position 1 on LCD (Digit1)*/
    case 1:
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER0, 0xcffffffc, ((Digit[0]& 0x0c) << 26 ) | (Digit[0]& 0x03)) ; /* 1G 1B 1M 1E */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER2, 0xcffffffc, ((Digit[1]& 0x0c) << 26 ) | (Digit[1]& 0x03)) ; /* 1F 1A 1C 1D  */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xcffffffc, ((Digit[2]& 0x0c) << 26 ) | (Digit[2]& 0x03)) ; /* 1Q 1K 1Col 1P  */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xcffffffc, ((Digit[3]& 0x0c) << 26 ) | (Digit[3]& 0x03)) ; /* 1H 1J 1DP 1N  */
      break;

    /* Position 2 on LCD (Digit2)*/
    case 2:
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER0, 0xf3ffff03, ((Digit[0]& 0x0c) << 24 )|((Digit[0]& 0x02) << 6 )|((Digit[0]& 0x01) << 2 )) ; /* 2G 2B 2M 2E  */   
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER2, 0xf3ffff03, ((Digit[1]& 0x0c) << 24 )|((Digit[1]& 0x02) << 6 )|((Digit[1]& 0x01) << 2 )) ; /* 2F 2A 2C 2D */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xf3ffff03, ((Digit[2]& 0x0c) << 24 )|((Digit[2]& 0x02) << 6 )|((Digit[2]& 0x01) << 2 )) ; /* 2Q 2K 2Col 2P */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xf3ffff03, ((Digit[3]& 0x0c) << 24 )|((Digit[3]& 0x02) << 6 )|((Digit[3]& 0x01) << 2 )) ; /* 2H 2J 2DP 2N */
      break;
    
    /* Position 3 on LCD (Digit3)*/
    case 3:
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER0, 0xfcfffcff, ((Digit[0]& 0x0c) << 22 ) | ((Digit[0]& 0x03) << 8 )) ; /* 3G 3B 3M 3E  */ 
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER2, 0xfcfffcff, ((Digit[1]& 0x0c) << 22 ) | ((Digit[1]& 0x03) << 8 )) ; /* 3F 3A 3C 3D */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xfcfffcff, ((Digit[2]& 0x0c) << 22 ) | ((Digit[2]& 0x03) << 8 )) ; /* 3Q 3K 3Col 3P */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xfcfffcff, ((Digit[3]& 0x0c) << 22 ) | ((Digit[3]& 0x03) << 8 )) ; /* 3H 3J 3DP 3N */
      break;
    
    /* Position 4 on LCD (Digit4)*/
    case 4:
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER0, 0xffcff3ff, ((Digit[0]& 0x0c) << 18 ) | ((Digit[0]& 0x03) << 10 )) ; /* 4G 4B 4M 4E */  
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER2, 0xffcff3ff, ((Digit[1]& 0x0c) << 18 ) | ((Digit[1]& 0x03) << 10 )) ; /* 4F 4A 4C 4D */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xffcff3ff, ((Digit[2]& 0x0c) << 18 ) | ((Digit[2]& 0x03) << 10 )) ; /* 4Q 4K 4Col 4P */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xffcff3ff, ((Digit[3]& 0x0c) << 18 ) | ((Digit[3]& 0x03) << 10 )) ; /* 4H 4J 4DP 4N */
      break;
    
    /* Position 5 on LCD (Digit5)*/
    case 5:
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER0, 0xfff3cfff, ((Digit[0]& 0x0c) << 16 ) | ((Digit[0]& 0x03) << 12 )) ; /* 5G 5B 5M 5E */  
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER2, 0xfff3cfff, ((Digit[1]& 0x0c) << 16 ) | ((Digit[1]& 0x03) << 12 )) ; /* 5F 5A 5C 5D */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xfff3efff, ((Digit[2]& 0x0c) << 16 ) | ((Digit[2]& 0x01) << 12 )) ; /* 5Q 5K   5P */ 
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xfff3efff, ((Digit[3]& 0x0c) << 16 ) | ((Digit[3]& 0x01) << 12 )) ; /* 5H 5J   5N */
      break;
    
    /* Position 6 on LCD (Digit6)*/
    case 6:
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER0, 0xfffc3fff, ((Digit[0]& 0x04) << 15 ) | ((Digit[0]& 0x08) << 13 ) | ((Digit[0]& 0x03) << 14 )) ; /* 6B 6G 6M 6E */  
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER2, 0xfffc3fff, ((Digit[1]& 0x04) << 15 ) | ((Digit[1]& 0x08) << 13 ) | ((Digit[1]& 0x03) << 14 )) ; /* 6A 6F 6C 6D */
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xfffc3fff, ((Digit[2]& 0x04) << 15 ) | ((Digit[2]& 0x08) << 13 ) | ((Digit[2]& 0x01) << 14 )) ; /* 6K 6Q    6P */ 
      HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xfffc3fff, ((Digit[3]& 0x04) << 15 ) | ((Digit[3]& 0x08) << 13 ) | ((Digit[3]& 0x01) << 14 )) ; /* 6J 6H   6N */
      break;
    
     default:
      break;
  }

  /* Refresh LCD  bar */
  BSP_LCD_GLASS_BarLevelConfig(LCDBar);

}

/**
  * @brief Setting bar on LCD, writes bar value in LCD frame buffer 
  * @param BarLevel: specifies the LCD GLASS Batery Level.
  *     This parameter can be one of the following values:
  *     @arg BATTERYLEVEL_OFF: LCD GLASS Batery Empty
  *     @arg BATTERYLEVEL_1_4: LCD GLASS Batery 1/4 Full
  *     @arg BATTERYLEVEL_1_2: LCD GLASS Batery 1/2 Full
  *     @arg BATTERYLEVEL_3_4: LCD GLASS Batery 3/4 Full
  *     @arg BATTERYLEVEL_FULL: LCD GLASS Batery Full
  * @retval None
  */
void BSP_LCD_GLASS_BarLevelConfig(uint8_t BarLevel)
{
  switch (BarLevel)
  {
  /* BATTERYLEVEL_OFF */
  case BATTERYLEVEL_OFF:
    /* Set BAR1 & BAR3 off  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xFFFF5FFF, 0 << (uint32_t)12);    
    /* Set BAR0 & BAR2 off  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xFFFF5FFF, 0 << (uint32_t)12);
    LCDBar = BATTERYLEVEL_OFF;
    break;
    
  /* BARLEVEL 1/4 */
  case BATTERYLEVEL_1_4:
    /* Set BAR1 & BAR3 off  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xFFFF5FFF, 0 << (uint32_t)12);    
    /* Set BAR0 on  */
    /* Set BAR2 off  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xFFFF5FFF, 8 << (uint32_t)12);
    LCDBar = BATTERYLEVEL_1_4;
    break;
    
  /* BARLEVEL 1/2 */
  case BATTERYLEVEL_1_2:
    /* Set BAR1 on  */
    /* Set BAR3 off  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xFFFF5FFF, 8 << (uint32_t)12);    
    /* Set BAR0 on  */
    /* Set BAR2 off  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xFFFF5FFF, 8 << (uint32_t)12);
    LCDBar = BATTERYLEVEL_1_2;
    break;
    
  /* Battery Level 3/4 */
  case BATTERYLEVEL_3_4:
    /* Set BAR1 on  */
    /* Set BAR3 off  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xFFFF5FFF, 8 << (uint32_t)12);    
    /* Set BAR0 on  */
    /* Set BAR2 on  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xFFFF5FFF, 10 << (uint32_t)12);
    LCDBar = BATTERYLEVEL_3_4;
    break;
    
  /* BATTERYLEVEL_FULL */
  case BATTERYLEVEL_FULL:
    /* Set BAR1 on  */
    /* Set BAR3 on  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER4, 0xFFFF5FFF, 10 << (uint32_t)12);    
    /* Set BAR0 on  */
    /* Set BAR2 on  */
    HAL_LCD_Write(&LCDHandle, LCD_RAM_REGISTER6, 0xFFFF5FFF, 10 << (uint32_t)12);
    LCDBar = BATTERYLEVEL_FULL;
    break;
    
  default:
    break;
  }
  
  /* Update the LCD display */
  HAL_LCD_UpdateDisplayRequest(&LCDHandle);
}


/**
  * @brief  This function writes a char in the LCD RAM.
  * @param  ch: The character to display.
  * @param  point: A point to add in front of char.
  *          This parameter  can be one of the following values:  
  *              @arg POINT_OFF: No point to add in front of char.
  *              @arg POINT_ON: Add a point in front of char.
  * @param  DoublePoint: Flag indicating if a apostrophe has to be add in front 
  *                     of displayed character.
  *          This parameter  can be one of the following values:
  *              @arg DOUBLEPOINT_OFF: No colon to add in back of char.
  *              @arg DOUBLEPOINT_ON: Add an colon in back of char.
  * @param  position: Position in the LCD of the caracter to write.
  *                   This parameter can be any value in range [1:6].
  * @retval None
  */
void BSP_LCD_GLASS_DisplayChar(uint8_t* ch, Point_Typedef point, DoublePoint_Typedef DoublePoint, uint8_t position)
{
  /*!< LCD Write Char */
  BSP_LCD_GLASS_WriteChar(ch, point, DoublePoint, position);

  /* Update the LCD display */
  HAL_LCD_UpdateDisplayRequest(&LCDHandle);
}

/**
  * @brief  This function writes a char in the LCD RAM.
  * @param  ptr: Pointer to string to display on the LCD Glass.
  * @retval None
  */
void BSP_LCD_GLASS_DisplayString(uint8_t* ptr)
{
  uint8_t position = 0x01;

  /* Send the string character by character on lCD */
  while ((*ptr != 0) & (position < 7))
  {
    /* Display one character on LCD */
    BSP_LCD_GLASS_WriteChar(ptr, 0, 0, position);

    /* Point on the next character */
    ptr++;

    /* Increment the character counter */
    position++;
  }


}

/**
  * @brief  This function writes a char in the LCD RAM.
  * @param  ptr: Pointer to string to display on the LCD Glass.
  * @retval None
  * @note Required preconditions: Char is ASCCI value "Ored" with decimal point or Column flag
  */
void BSP_LCD_GLASS_DisplayStrDeci(uint16_t* ptr)
{
  uint8_t index = 1;
  uint8_t tmpchar = 0;
  
  /* Send the string character by character on lCD */
  while((*ptr != 0) & (index < 7))
  {      
    tmpchar = (*ptr) & 0x00FF;
    
    switch((*ptr) & 0xF000)
    {
    case DOT:
      /* Display one character on LCD with decimal point */
      BSP_LCD_GLASS_WriteChar(&tmpchar, POINT_ON, DOUBLEPOINT_OFF, index);
      break;
    case DOUBLE_DOT:
      /* Display one character on LCD with decimal point */
      BSP_LCD_GLASS_WriteChar(&tmpchar, POINT_OFF, DOUBLEPOINT_ON, index);
      break;
    default:
      BSP_LCD_GLASS_WriteChar(&tmpchar, POINT_OFF, DOUBLEPOINT_OFF, index);    
      break;
    }/* Point on the next character */
    ptr++;
    
    /* Increment the character counter */
    index++;
  }
}

/**
  * @brief  This function Clear the whole LCD RAM.
  * @retval None
  */
void BSP_LCD_GLASS_Clear(void)
{
  HAL_LCD_Clear(&LCDHandle); 
}

/**
  * @brief  Display a string in scrolling mode
  * @param  ptr: Pointer to string to display on the LCD Glass.
  * @param  nScroll: Specifies how many time the message will be scrolled
  * @param  ScrollSpeed : Specifies the speed of the scroll, low value gives
  *         higher speed 
  * @retval None
  * @note    Required preconditions: The LCD should be cleared before to start the
  *         write operation.
  */
void BSP_LCD_GLASS_ScrollSentence(uint8_t* ptr, uint16_t nScroll, uint16_t ScrollSpeed)
{
  uint8_t repetition = 0, nbrchar = 0, sizestr = 0;
  uint8_t* ptr1;
  uint8_t str[6] = "";
  
  if(ptr == 0)
  {
    return;
  }
  
  /* To calculate end of string */
  for(ptr1 = ptr, sizestr = 0; *ptr1 != 0; sizestr++, ptr1++);
  
  ptr1 = ptr;
  
  BSP_LCD_GLASS_DisplayString(ptr);
  HAL_Delay(ScrollSpeed);
  
  /* To shift the string for scrolling display*/
  for (repetition = 0; repetition < nScroll; repetition++)
  {
    for(nbrchar = 0; nbrchar < sizestr; nbrchar++)
    {
      *(str) =* (ptr1+((nbrchar+1)%sizestr));
      *(str+1) =* (ptr1+((nbrchar+2)%sizestr));
      *(str+2) =* (ptr1+((nbrchar+3)%sizestr));
      *(str+3) =* (ptr1+((nbrchar+4)%sizestr));
      *(str+4) =* (ptr1+((nbrchar+5)%sizestr));
      *(str+5) =* (ptr1+((nbrchar+6)%sizestr));
      BSP_LCD_GLASS_Clear();
      BSP_LCD_GLASS_DisplayString(str);
      
      /* user button pressed stop the scrolling sentence */
      if (bLCDGlass_KeyPressed)
      {
         return;
      }
       HAL_Delay(ScrollSpeed);
    }  
  }
}

/**
  * @}
  */

/** @addtogroup STM32L152C_DISCOVERY_LCD_Private_Functions
  * @{
  */

/**
  * @brief  LCD MSP Init.
  * @param  hlcd: LCD handle
  * @retval None
  */
static void LCD_MspInit(LCD_HandleTypeDef *hlcd)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /*##-1- Enable PWR  peripheral Clock #######################################*/
  __PWR_CLK_ENABLE();
  
  /*##-2- Allow Access and Reset the Backup Domaine ##########################*/ 
  /* Allow Access to Backup Domaine */
  HAL_PWR_EnableBkUpAccess();

  /* Reset the Backup Domaine */
  __HAL_RCC_BACKUPRESET_FORCE(); 
  __HAL_RCC_BACKUPRESET_RELEASE();
  
  /*##-3- Configue LSE as RTC clock soucre ###################################*/ 
  oscinitstruct.OscillatorType  =  RCC_OSCILLATORTYPE_LSE;
  oscinitstruct.PLL.PLLState    = RCC_PLL_NONE;
  oscinitstruct.LSEState        = RCC_LSE_ON;
  if(HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
  { 
    while(1);
  }
  
 __HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);


  /*##-4- Enable LCD GPIO Clocks #############################################*/
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();

  
  /*##-5- Configure peripheral GPIO ##########################################*/
  /* Configure Output for LCD */
  /* Port A */  
  gpioinitstruct.Pin       = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_8 | GPIO_PIN_9 |\
                             GPIO_PIN_10 |GPIO_PIN_15;
  gpioinitstruct.Mode      = GPIO_MODE_AF_PP;
  gpioinitstruct.Pull      = GPIO_NOPULL;
  gpioinitstruct.Speed     = GPIO_SPEED_MEDIUM;
  gpioinitstruct.Alternate = GPIO_AF11_LCD;
  HAL_GPIO_Init(GPIOA, &gpioinitstruct);

  /* Configure Output for LCD */
  /* Port B */  
  gpioinitstruct.Pin       = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 | \
                             GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                             GPIO_PIN_15;
  HAL_GPIO_Init(GPIOB, &gpioinitstruct);
  
  
  /* Configure Output for LCD */
  /* Port C*/  
  gpioinitstruct.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6 | \
                             GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |GPIO_PIN_11;
  HAL_GPIO_Init(GPIOC, &gpioinitstruct);

  /*##-6- Enable LCD peripheral Clock ########################################*/
  __LCD_CLK_ENABLE();
}

/**
  * @brief  Converts an ascii char to the a LCD digit.
  * @param  Char: a char to display.
  * @param  Point: a point to add in front of char
  *         This parameter can be: POINT_OFF or POINT_ON
  * @param  DoublePoint : flag indicating if a column has to be add in front
  *         of displayed character.
  *         This parameter can be: DOUBLEPOINT_OFF or DOUBLEPOINT_ON.
  * @retval None
  */
static void Convert(uint8_t* Char, Point_Typedef Point, DoublePoint_Typedef DoublePoint)
{
  uint16_t ch = 0 ;
  uint8_t loop = 0, index = 0;
  
  switch (*Char)
    {
    case ' ' :
      ch = 0x00;
      break;

    case '*':
      ch = STAR;
      break;

    case 'µ' :
      ch = C_UMAP;
      break;

    case 'm' :
      ch = C_MMAP;
      break;

    case 'n' :
      ch = C_NMAP;
      break;

    case '-' :
      ch = C_MINUS;
      break;

    case '/' :
      ch = C_SLATCH;
      break;  
      
    case '°' :
      ch = C_PERCENT_1;
      break;  
    case '%' :
      ch = C_PERCENT_2; 
      break;
    case 255 :
      ch = C_FULL;
      break ;
    
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':      
      ch = NumberMap[*Char - ASCII_CHAR_0];    
      break;
          
    default:
      /* The character Char is one letter in upper case*/
      if ( (*Char < ASCII_CHAR_LEFT_OPEN_BRACKET) && (*Char > ASCII_CHAR_AT_SYMBOL) )
      {
        ch = CapLetterMap[*Char - 'A'];
      }
      /* The character Char is one letter in lower case*/
      if ( (*Char < ASCII_CHAR_LEFT_OPEN_BRACE) && ( *Char > ASCII_CHAR_APOSTROPHE) )
      {
        ch = CapLetterMap[*Char - 'a'];
      }
      break;
  }
       
  /* Set the digital point can be displayed if the point is on */
  if (Point == POINT_ON)
  {
    ch |= 0x0002;
  }

  /* Set the "COL" segment in the character that can be displayed if the column is on */
  if (DoublePoint == DOUBLEPOINT_ON)
  {
    ch |= 0x0020;
  }    

  for (loop = 12,index=0 ;index < 4; loop -= 4,index++)
  {
    Digit[index] = (ch >> loop) & 0x0f; /*To isolate the less signifiant dibit */
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

