/**
  ******************************************************************************
  * @file    AccHw_stm32l1xx_aes.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   This file contains all the functions prototypes for the AES firmware 
  *          library.
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
#ifndef __AccHw_STM32L1XX_AES_H
#define __AccHw_STM32L1XX_AES_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32L1xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup AES
  * @{
  */

/* Exported types ------------------------------------------------------------*/
    

/**
  * @brief   AES Init structure definition
  */
typedef struct
{
  uint32_t AES_Operation; /*!< Specifies the AES mode of operation.
                               This parameter can be a value of @ref AES_possible_Operation_modes */
  uint32_t AES_Chaining;  /*!< Specifies the AES Chaining modes: ECB, CBC or CTR.
                               This parameter can be a value of @ref AES_possible_chaining_modes */
  uint32_t AES_DataType;  /*!< Specifies the AES data swapping: 32-bit, 16-bit, 8-bit or 1-bit.
                               This parameter can be a value of @ref AES_Data_Types */
}AccHw_AES_InitTypeDef;

/** 
  * @brief   AES Key(s) structure definition
  */ 
typedef struct
{
  uint32_t AES_Key0;  /*!< Key[31:0]   */
  uint32_t AES_Key1;  /*!< Key[63:32]  */
  uint32_t AES_Key2;  /*!< Key[95:64]  */
  uint32_t AES_Key3;  /*!< Key[127:96] */
}AccHw_AES_KeyInitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup AES_Exported_Constants
  * @{
  */ 

/** @defgroup AES_possible_Operation_modes
  * @{
  */  
#define AccHw_AES_Operation_Encryp               ((uint32_t)0x00000000) /*!< AES in Encryption mode */
#define AccHw_AES_Operation_KeyDeriv             AccHw_AES_CR_MODE_0          /*!< AES in Key Derivation mode */
#define AccHw_AES_Operation_Decryp               AccHw_AES_CR_MODE_1          /*!< AES in Decryption mode */
#define AccHw_AES_Operation_KeyDerivAndDecryp    AccHw_AES_CR_MODE            /*!< AES in Key Derivation and Decryption mode */



/**
  * @}
  */ 

/** @defgroup AES_possible_chaining_modes
  * @{
  */ 
#define AccHw_AES_Chaining_ECB                   ((uint32_t)0x00000000) /*!< AES in ECB chaining mode */

/**
  * @}
  */

/** @defgroup AES_Data_Types
  * @{
  */ 
#define AccHw_AES_DataType_32b                   ((uint32_t)0x00000000) /*!< 32-bit data. No swapping */
#define AccHw_AES_DataType_8b                    AccHw_AES_CR_DATATYPE_1      /*!< 8-bit data. All bytes are swapped */


/**
  * @}
  */

/** @defgroup AES_Flags
  * @{
  */ 
#define AccHw_AES_FLAG_CCF                       AccHw_AES_SR_CCF    /*!< Computation Complete Flag */

/**
  * @}
  */ 


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and configuration functions *********************************/
void AccHw_AES_DeInit(void);
void AccHw_AES_Init(AccHw_AES_InitTypeDef* AES_InitStruct);
void AccHw_AES_KeyInit(AccHw_AES_KeyInitTypeDef* AES_KeyInitStruct);


/* Structures initialization functions ****************************************/
void AccHw_AES_StructInit(AccHw_AES_InitTypeDef* AES_InitStruct);
void AccHw_AES_KeyStructInit(AccHw_AES_KeyInitTypeDef* AES_KeyInitStruct);


#ifdef __cplusplus
}
#endif


#endif /*__AccHw_STM32L1XX_AES_H */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
