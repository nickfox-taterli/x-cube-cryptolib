/**
  ******************************************************************************
  * @file    AccHw_stm32l1xx_rcc.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   This file contains all the functions prototypes for the RCC 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AccHw_STM32L1XX_RCC_H
#define __AccHw_STM32L1XX_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32L1xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup RCC_AHB_Peripherals 
  * @{
  */

#define AccHw_RCC_AHBPeriph_AES                 AccHw_RCC_AHBENR_AESEN



/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */




/* Peripheral clocks configuration functions **********************************/

void AccHw_RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, AccHw_FunctionalState NewState);
void AccHw_RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, AccHw_FunctionalState NewState);





#ifdef __cplusplus
}
#endif

#endif /* __AccHw_STM32L1XX_RCC_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
