/**
  ******************************************************************************
  * @file    AccHw_stm32l0xx_rcc.h
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
#ifndef __AccHw_STM32L0XX_RNG_H
#define __AccHw_STM32L0XX_RNG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32L0xx_StdPeriph_Driver
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

/** @defgroup RNG_Interrupt_definition  RNG Interrupts Definition
  * @{
  */
#define AccHw_RNG_IT_DRDY  AccHw_RNG_SR_DRDY  /*!< Data Ready interrupt  */
#define AccHw_RNG_IT_CEI   AccHw_RNG_SR_CEIS  /*!< Clock error interrupt */
#define AccHw_RNG_IT_SEI   AccHw_RNG_SR_SEIS  /*!< Seed error interrupt  */
/**
  * @}
  */

/** @defgroup RNG_Flag_definition  RNG Flags Definition
  * @{
  */ 
#define AccHw_RNG_FLAG_DRDY   AccHw_RNG_SR_DRDY  /*!< Data ready                 */
#define AccHw_RNG_FLAG_CECS   AccHw_RNG_SR_CECS  /*!< Clock error current status */
#define AccHw_RNG_FLAG_SECS   AccHw_RNG_SR_SECS  /*!< Seed error current status  */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void AccHw_RNG_DeInit(void);
void AccHw_RNG_Cmd(AccHw_FunctionalState NewState);



#ifdef __cplusplus
}
#endif

#endif /* __AccHw_STM32L0XX_RNG_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
