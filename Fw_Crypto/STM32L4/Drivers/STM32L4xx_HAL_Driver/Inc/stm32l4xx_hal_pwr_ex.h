/**
  ******************************************************************************
  * @file    stm32l4xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @version V0.5.0
  * @date    10-February-2015
  * @brief   Header file of PWR HAL Extension module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L4xx_HAL_PWR_EX_H
#define __STM32L4xx_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal_def.h"

/** @addtogroup STM32L4xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */


/* Exported types ------------------------------------------------------------*/

/**
  * @brief  PWR PVM configuration structure definition
  */
typedef struct
{
  uint32_t PVMType;   /*!< PVMType: Specifies which voltage is monitored and against which threshold.
                           This parameter can be a value of @ref PWR_PVM_Type 
                           PWR_PVM_1: Peripheral voltage monitoring 1 enable: VDDUSB vs. 1.2V (applicable when USB feature is supported)
                           PWR_PVM_2: Peripheral voltage monitoring 2 enable: VDDIO2 vs. 0.9V
                           PWR_PVM_3: Peripheral voltage monitoring 3 enable: VDDA vs. 1.62V
                           PWR_PVM_4: Peripheral voltage monitoring 4 enable: VDDA vs. 2.2V */

  uint32_t Mode;      /*!< Mode: Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref PWR_PVM_Mode */
}PWR_PVMTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_WUP_Polarity Shift to apply to retrieve polarity information from PWR_WAKEUP_PINy_xxx constants
  * @{
  */
#define PWR_WUP_POLARITY_SHIFT                  0x05
/**
  * @}
  */  


/** @defgroup PWR_WakeUp_Pins  PWR Wake-up pins
  * @{
  */                                                      
#define PWR_WAKEUP_PIN1                 PWR_CR3_EWUP1
#define PWR_WAKEUP_PIN2                 PWR_CR3_EWUP2
#define PWR_WAKEUP_PIN3                 PWR_CR3_EWUP3
#define PWR_WAKEUP_PIN4                 PWR_CR3_EWUP4
#define PWR_WAKEUP_PIN5                 PWR_CR3_EWUP5
#define PWR_WAKEUP_PIN1_HIGH            PWR_CR3_EWUP1
#define PWR_WAKEUP_PIN2_HIGH            PWR_CR3_EWUP2
#define PWR_WAKEUP_PIN3_HIGH            PWR_CR3_EWUP3
#define PWR_WAKEUP_PIN4_HIGH            PWR_CR3_EWUP4
#define PWR_WAKEUP_PIN5_HIGH            PWR_CR3_EWUP5
#define PWR_WAKEUP_PIN1_LOW             (uint32_t)((PWR_CR4_WP1<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP1)
#define PWR_WAKEUP_PIN2_LOW             (uint32_t)((PWR_CR4_WP2<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP2)
#define PWR_WAKEUP_PIN3_LOW             (uint32_t)((PWR_CR4_WP3<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP3)
#define PWR_WAKEUP_PIN4_LOW             (uint32_t)((PWR_CR4_WP4<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP4)
#define PWR_WAKEUP_PIN5_LOW             (uint32_t)((PWR_CR4_WP5<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP5)
/**
  * @}
  */

/** @defgroup PWR_PVM_Type Peripheral Voltage Monitoring type
  * @{
  */
#if defined(STM32L476xx) || defined(STM32L486xx)  
#define PWR_PVM_1                  PWR_CR2_PVME1
#endif
#define PWR_PVM_2                  PWR_CR2_PVME2
#define PWR_PVM_3                  PWR_CR2_PVME3
#define PWR_PVM_4                  PWR_CR2_PVME4
/**
  * @}
  */  
  
/** @defgroup PWR_PVM_Mode  PWR PVM interrupt and event mode
  * @{
  */
#define PWR_PVM_MODE_NORMAL                 ((uint32_t)0x00000000)   /*!< basic mode is used */
#define PWR_PVM_MODE_IT_RISING              ((uint32_t)0x00010001)   /*!< External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVM_MODE_IT_FALLING             ((uint32_t)0x00010002)   /*!< External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVM_MODE_IT_RISING_FALLING      ((uint32_t)0x00010003)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVM_MODE_EVENT_RISING           ((uint32_t)0x00020001)   /*!< Event Mode with Rising edge trigger detection */
#define PWR_PVM_MODE_EVENT_FALLING          ((uint32_t)0x00020002)   /*!< Event Mode with Falling edge trigger detection */
#define PWR_PVM_MODE_EVENT_RISING_FALLING   ((uint32_t)0x00020003)   /*!< Event Mode with Rising/Falling edge trigger detection */                              
/**
  * @}
  */
  
  

/** @defgroup PWR_Regulator_Voltage_Scale  PWR Regulator voltage scale
  * @{
  */
#define PWR_REGULATOR_VOLTAGE_SCALE1       PWR_CR1_VOS_0
#define PWR_REGULATOR_VOLTAGE_SCALE2       PWR_CR1_VOS_1
/**
  * @}
  */

  
/** @defgroup PWR_VBAT_Battery_Charging_Selection PWR battery charging resistor selection
  * @{
  */
#define PWR_BATTERY_CHARGING_RESISTOR_5          ((uint32_t)0x00000000)
#define PWR_BATTERY_CHARGING_RESISTOR_1_5         PWR_CR4_VBRS                                                                                                                                                                                                                                                                                                                                                                              
/**
  * @}
  */
  
/** @defgroup PWR_VBAT_Battery_Charging PWR battery charging
  * @{
  */
#define PWR_BATTERY_CHARGING_DISABLE        ((uint32_t)0x00000000)
#define PWR_BATTERY_CHARGING_ENABLE         PWR_CR4_VBE                                                                                                                                                                                                                                                                                                                                                                               
/**
  * @}
  */ 
  
/** @defgroup PWR_GPIO_Bit_Number GPIO bit number for Standby mode setting
  * @{
  */
#define PWR_GPIO_BIT_0   PWR_PUCRA_PA0
#define PWR_GPIO_BIT_1   PWR_PUCRA_PA1
#define PWR_GPIO_BIT_2   PWR_PUCRA_PA2
#define PWR_GPIO_BIT_3   PWR_PUCRA_PA3
#define PWR_GPIO_BIT_4   PWR_PUCRA_PA4
#define PWR_GPIO_BIT_5   PWR_PUCRA_PA5
#define PWR_GPIO_BIT_6   PWR_PUCRA_PA6
#define PWR_GPIO_BIT_7   PWR_PUCRA_PA7
#define PWR_GPIO_BIT_8   PWR_PUCRA_PA8
#define PWR_GPIO_BIT_9   PWR_PUCRA_PA9
#define PWR_GPIO_BIT_10  PWR_PUCRA_PA10
#define PWR_GPIO_BIT_11  PWR_PUCRA_PA11
#define PWR_GPIO_BIT_12  PWR_PUCRA_PA12
#define PWR_GPIO_BIT_13  PWR_PUCRA_PA13
#define PWR_GPIO_BIT_14  PWR_PUCRA_PA14
#define PWR_GPIO_BIT_15  PWR_PUCRA_PA15                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
/**
  * @}
  */ 
  
/** @defgroup PWR_GPIO GPIO port
  * @{
  */
#define PWR_GPIO_A   0x00000000
#define PWR_GPIO_B   0x00000001
#define PWR_GPIO_C   0x00000002
#define PWR_GPIO_D   0x00000003
#define PWR_GPIO_E   0x00000004
#define PWR_GPIO_F   0x00000005
#define PWR_GPIO_G   0x00000006
#define PWR_GPIO_H   0x00000007                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
/**
  * @}
  */   
 
  

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWREx_Exported macro
 * @{
 */


#if defined(STM32L476xx) || defined(STM32L486xx)
#define PWR_EXTI_LINE_PVM1  ((uint32_t)0x00000008)  /*!< External interrupt line 35 Connected to the PVM1 EXTI Line   */
#endif
#define PWR_EXTI_LINE_PVM2  ((uint32_t)0x00000010)  /*!< External interrupt line 36 Connected to the PVM2 EXTI Line   */
#define PWR_EXTI_LINE_PVM3  ((uint32_t)0x00000020)  /*!< External interrupt line 37 Connected to the PVM3 EXTI Line   */
#define PWR_EXTI_LINE_PVM4  ((uint32_t)0x00000040)  /*!< External interrupt line 38 Connected to the PVM4 EXTI Line   */
#if defined(STM32L476xx) || defined(STM32L486xx)
#define PWR_EVENT_LINE_PVM1 ((uint32_t)0x00000008)  /*!< Event line 35 Connected to the PVM1 EXTI Line */
#endif
#define PWR_EVENT_LINE_PVM2 ((uint32_t)0x00000010)  /*!< Event line 36 Connected to the PVM2 EXTI Line */
#define PWR_EVENT_LINE_PVM3 ((uint32_t)0x00000020)  /*!< Event line 37 Connected to the PVM3 EXTI Line */
#define PWR_EVENT_LINE_PVM4 ((uint32_t)0x00000040)  /*!< Event line 38 Connected to the PVM4 EXTI Line */


#if defined(STM32L476xx) || defined(STM32L486xx)
/**
  * @brief Enable the PVM1 Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Disable the PVM1 Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Enable the PVM1 Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM1)

/**
  * @brief Disable the PVM1 Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM1)

/**
  * @brief Enable the PVM1 Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Disable the PVM1 Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Enable the PVM1 Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM1)


/**
  * @brief Disable the PVM1 Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM1)


/**
  * @brief  PVM1 EXTI line configuration: set rising & falling edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_RISING_FALLING_EDGE()   __HAL_PWR_PVM1_EXTI_ENABLE_RISING_EDGE();__HAL_PWR_PVM1_EXTI_ENABLE_FALLING_EDGE();

/**
  * @brief Disable the PVM1 Extended Interrupt Rising & Falling Trigger.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_RISING_FALLING_EDGE()  __HAL_PWR_PVM1_EXTI_DISABLE_RISING_EDGE();__HAL_PWR_PVM1_EXTI_DISABLE_FALLING_EDGE()();


/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Checks whether the specified PVM1 Exti interrupt flag is set or not.
  * @retval EXTI PVM1 Line Status.
  */
#define __HAL_PWR_PVM1_EXTI_GET_FLAG()  (EXTI->PR2 & PWR_EXTI_LINE_PVM1)

/**
  * @brief Clear the PVM1 Exti flag.
  * @retval None.
  */
#define __HAL_PWR_PVM1_EXTI_CLEAR_FLAG()  WRITE_REG(EXTI->PR2, PWR_EXTI_LINE_PVM1)

#endif /* defined(STM32L476xx) || defined(STM32L486xx) */



/**
  * @brief Enable the PVM2 Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Disable the PVM2 Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Enable the PVM2 Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM2)

/**
  * @brief Disable the PVM2 Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM2)

/**
  * @brief Enable the PVM2 Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Disable the PVM2 Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Enable the PVM2 Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM2)


/**
  * @brief Disable the PVM2 Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM2)


/**
  * @brief  PVM2 EXTI line configuration: set rising & falling edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_RISING_FALLING_EDGE()   __HAL_PWR_PVM2_EXTI_ENABLE_RISING_EDGE();__HAL_PWR_PVM2_EXTI_ENABLE_FALLING_EDGE();

/**
  * @brief Disable the PVM2 Extended Interrupt Rising & Falling Trigger.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_RISING_FALLING_EDGE()  __HAL_PWR_PVM2_EXTI_DISABLE_RISING_EDGE();__HAL_PWR_PVM2_EXTI_DISABLE_FALLING_EDGE()();


/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Checks whether the specified PVM2 Exti interrupt flag is set or not.
  * @retval EXTI PVM2 Line Status.
  */
#define __HAL_PWR_PVM2_EXTI_GET_FLAG()  (EXTI->PR2 & PWR_EXTI_LINE_PVM2)

/**
  * @brief Clear the PVM2 Exti flag.
  * @retval None.
  */
#define __HAL_PWR_PVM2_EXTI_CLEAR_FLAG()  WRITE_REG(EXTI->PR2, PWR_EXTI_LINE_PVM2)




/**
  * @brief Enable the PVM3 Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Disable the PVM3 Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Enable the PVM3 Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM3)

/**
  * @brief Disable the PVM3 Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM3)

/**
  * @brief Enable the PVM3 Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Disable the PVM3 Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Enable the PVM3 Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM3)


/**
  * @brief Disable the PVM3 Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM3)


/**
  * @brief  PVM3 EXTI line configuration: set rising & falling edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_RISING_FALLING_EDGE()   __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE();__HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE();

/**
  * @brief Disable the PVM3 Extended Interrupt Rising & Falling Trigger.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_RISING_FALLING_EDGE()  __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE();__HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE()();


/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Checks whether the specified PVM3 Exti interrupt flag is set or not.
  * @retval EXTI PVM3 Line Status.
  */
#define __HAL_PWR_PVM3_EXTI_GET_FLAG()  (EXTI->PR2 & PWR_EXTI_LINE_PVM3)

/**
  * @brief Clear the PVM3 Exti flag.
  * @retval None.
  */
#define __HAL_PWR_PVM3_EXTI_CLEAR_FLAG()  WRITE_REG(EXTI->PR2, PWR_EXTI_LINE_PVM3)




/**
  * @brief Enable the PVM4 Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Disable the PVM4 Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Enable the PVM4 Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM4)

/**
  * @brief Disable the PVM4 Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM4)

/**
  * @brief Enable the PVM4 Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Disable the PVM4 Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Enable the PVM4 Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM4)


/**
  * @brief Disable the PVM4 Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM4)


/**
  * @brief  PVM4 EXTI line configuration: set rising & falling edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_RISING_FALLING_EDGE()   __HAL_PWR_PVM4_EXTI_ENABLE_RISING_EDGE();__HAL_PWR_PVM4_EXTI_ENABLE_FALLING_EDGE();

/**
  * @brief Disable the PVM4 Extended Interrupt Rising & Falling Trigger.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_RISING_FALLING_EDGE()  __HAL_PWR_PVM4_EXTI_DISABLE_RISING_EDGE();__HAL_PWR_PVM4_EXTI_DISABLE_FALLING_EDGE()();


/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Checks whether the specified PVM4 Exti interrupt flag is set or not.
  * @retval EXTI PVM4 Line Status.
  */
#define __HAL_PWR_PVM4_EXTI_GET_FLAG()  (EXTI->PR2 & PWR_EXTI_LINE_PVM4)

/**
  * @brief Clear the PVM4 Exti flag.
  * @retval None.
  */
#define __HAL_PWR_PVM4_EXTI_CLEAR_FLAG()  WRITE_REG(EXTI->PR2, PWR_EXTI_LINE_PVM4)



/**
  * @}
  */
  
/* Private macros --------------------------------------------------------*/
/** @addtogroup  PWREx_Private_Macros   PWREx Private Macros
  * @{
  */

#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1) || \
                                ((PIN) == PWR_WAKEUP_PIN2) || \
                                ((PIN) == PWR_WAKEUP_PIN3) || \
                                ((PIN) == PWR_WAKEUP_PIN4) || \
                                ((PIN) == PWR_WAKEUP_PIN5) || \
                                ((PIN) == PWR_WAKEUP_PIN1_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN2_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN3_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN4_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN5_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN1_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN2_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN3_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN4_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN5_LOW))
                                
#define IS_PWR_PVM_TYPE(TYPE)     ((TYPE) & PWR_CR2_PVME)

#define IS_PWR_PVM_MODE(MODE)  (((MODE) == PWR_PVM_MODE_NORMAL)              ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING)           ||\
                                ((MODE) == PWR_PVM_MODE_IT_FALLING)          ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING_FALLING)   ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING)        ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_FALLING)       ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING_FALLING))  
                                
#define IS_PWR_VOLTAGE_SCALING_RANGE(RANGE) (((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE1) || \
                                             ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE2))
                                             
#define IS_PWR_BATTERY_RESISTOR_SELECT(RESISTOR) (((RESISTOR) == PWR_BATTERY_CHARGING_RESISTOR_5) ||\
                                                  ((RESISTOR) == PWR_BATTERY_CHARGING_RESISTOR_1_5))  
                                                  
#define IS_PWR_BATTERY_CHARGING(CHARGING) (((CHARGING) == PWR_BATTERY_CHARGING_DISABLE) ||\
                                           ((CHARGING) == PWR_BATTERY_CHARGING_ENABLE)) 
                                           
#define IS_PWR_GPIO_BIT_NUMBER(BIT_NUMBER) (((BIT_NUMBER) == PWR_GPIO_BIT_0) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_1) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_2) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_3) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_4) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_5) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_6) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_7) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_8) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_9) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_10) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_11) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_12) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_13) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_14) ||\
                                            ((BIT_NUMBER) == PWR_GPIO_BIT_15))    
                                            
#define IS_PWR_GPIO(GPIO) (((GPIO) == PWR_GPIO_A) ||\
                           ((GPIO) == PWR_GPIO_B) ||\
                           ((GPIO) == PWR_GPIO_C) ||\
                           ((GPIO) == PWR_GPIO_D) ||\
                           ((GPIO) == PWR_GPIO_E) ||\
                           ((GPIO) == PWR_GPIO_F) ||\
                           ((GPIO) == PWR_GPIO_G) ||\
                           ((GPIO) == PWR_GPIO_H))

/**
  * @}
  */  
  

/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */
  
/** @addtogroup PWREx_Exported_Functions_Group1 Extended Peripheral Control functions 
  * @{
  */


/* Peripheral Control functions  **********************************************/
uint32_t HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorSelection);
void HAL_PWREx_DisableBatteryCharging(void);
#if defined(STM32L476xx) || defined(STM32L486xx)
void HAL_PWREx_EnableVddUSB(void);
void HAL_PWREx_DisableVddUSB(void);
#endif /* STM32L476xx || STM32L486xx */
void HAL_PWREx_EnableVddIO2(void);
void HAL_PWREx_DisableVddIO2(void);
void HAL_PWREx_EnableInternalWakeUpLine(void);
void HAL_PWREx_DisableInternalWakeUpLine(void);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
void HAL_PWREx_EnablePullUpPullDownConfig(void);
void HAL_PWREx_DisablePullUpPullDownConfig(void);
void HAL_PWREx_EnableSRAM2ContentRetention(void);
void HAL_PWREx_DisableSRAM2ContentRetention(void);
#if defined(STM32L476xx) || defined(STM32L486xx)
void HAL_PWREx_EnablePVM1(void);
void HAL_PWREx_DisablePVM1(void);
#endif /* STM32L476xx || STM32L486xx */
void HAL_PWREx_EnablePVM2(void);
void HAL_PWREx_DisablePVM2(void);
void HAL_PWREx_EnablePVM3(void);
void HAL_PWREx_DisablePVM3(void);
void HAL_PWREx_EnablePVM4(void);
void HAL_PWREx_DisablePVM4(void);
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(PWR_PVMTypeDef *sConfigPVM);


/* Low Power modes configuration functions ************************************/
void HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);
void HAL_PWREx_EnterSTOP1Mode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWREx_EnterSTOP2Mode(uint8_t STOPEntry);
void HAL_PWREx_EnterSHUTDOWNMode(void);

void HAL_PWREx_PVD_PVM_IRQHandler(void);
#if defined(STM32L476xx) || defined(STM32L486xx)
void HAL_PWREx_PVM1Callback(void);
#endif /* STM32L476xx || STM32L486xx */
void HAL_PWREx_PVM2Callback(void);
void HAL_PWREx_PVM3Callback(void);
void HAL_PWREx_PVM4Callback(void);


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

#ifdef __cplusplus
}
#endif


#endif /* __STM32L4xx_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
