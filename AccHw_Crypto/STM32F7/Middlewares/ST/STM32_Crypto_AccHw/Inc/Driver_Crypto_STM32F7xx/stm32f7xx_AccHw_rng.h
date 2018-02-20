/**
  ******************************************************************************
  * @file    stm32f2xx_rng.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   This file contains all the functions prototypes for the Random
  *          Number Generator(RNG) firmware library.
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
#ifndef __STM32F21x_AccHw_RNG_H
#define __STM32F21x_AccHw_RNG_H

#ifdef __cplusplus
extern "C"
{
#endif

  /* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_AccHw.h"

  /** @addtogroup STM32F2xx_StdPeriph_Driver
    * @{
    */

  /** @addtogroup RNG
    * @{
    */

  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/

  /** @defgroup RNG_Exported_Constants
    * @{
    */

  /**
    * @}
    */

  /** @defgroup RNG_flags_definition
    * @{
    */
#define AccHw_RNG_FLAG_DRDY               ((uint8_t)0x0001) /*!< Data ready */
#define AccHw_RNG_FLAG_CECS               ((uint8_t)0x0002) /*!< Clock error current status */
#define AccHw_RNG_FLAG_SECS               ((uint8_t)0x0004) /*!< Seed error current status */

  /**
    * @}
    */

  /** @defgroup RNG_interrupts_definition
    * @{
    */
#define AccHw_RNG_IT_CEI                  ((uint8_t)0x20) /*!< Clock error interrupt */
#define AccHw_RNG_IT_SEI                  ((uint8_t)0x40) /*!< Seed error interrupt */

  /**
    * @}
    */

  /**
    * @}
    */

  /* Exported macro ------------------------------------------------------------*/
  /* Exported functions --------------------------------------------------------*/

  /*  Function used to set the RNG configuration to the default reset state *****/
  void AccHw_RNG_DeInit(void);
  /* Configuration function *****************************************************/
  void AccHw_RNG_Cmd(AccHw_FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F2xx_AccHw_RNG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
