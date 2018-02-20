/**
  ******************************************************************************
  * @file    stm32f2xx_cryp.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   This file contains all the functions prototypes for the Cryptographic
  *          processor(CRYP) firmware library.
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
#ifndef __STM32F2XX_AccHw_CRYP_H
#define __STM32F21x_AccHw_CRYP_H

#ifdef __cplusplus
extern "C"
{
#endif

  /* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_AccHw.h"

  /** @addtogroup STM32F2xx_StdPeriph_Driver
    * @{
    */

  /** @addtogroup CRYP
    * @{
    */

  /* Exported types ------------------------------------------------------------*/

  /**
    * @brief   CRYP Init structure definition
    */
  typedef struct
  {
    uint16_t CRYP_AlgoDir;   /*!< Encrypt or Decrypt. This parameter can be a
                                    value of @ref CRYP_Algorithm_Direction */
    uint16_t CRYP_AlgoMode;  /*!< TDES-ECB, TDES-CBC, DES-ECB, DES-CBC, AES-ECB,
                                    AES-CBC, AES-CTR, AES-Key. This parameter can be
                                    a value of @ref CRYP_Algorithm_Mode */
    uint16_t CRYP_DataType;  /*!< 32-bit data, 16-bit data, bit data or bit-string.
                                    This parameter can be a value of @ref CRYP_Data_Type */
    uint16_t CRYP_KeySize;   /*!< Used only in AES mode only : 128, 192 or 256 bit
                                    key length. This parameter can be a value of
                                    @ref CRYP_Key_Size_for_AES_only */
  }
  AccHw_CRYP_InitTypeDef;

  /**
    * @brief   CRYP Key(s) structure definition
    */
  typedef struct
  {
    uint32_t CRYP_Key0Left;  /*!< Key 0 Left  */
    uint32_t CRYP_Key0Right; /*!< Key 0 Right */
    uint32_t CRYP_Key1Left;  /*!< Key 1 left  */
    uint32_t CRYP_Key1Right; /*!< Key 1 Right */
    uint32_t CRYP_Key2Left;  /*!< Key 2 left  */
    uint32_t CRYP_Key2Right; /*!< Key 2 Right */
    uint32_t CRYP_Key3Left;  /*!< Key 3 left  */
    uint32_t CRYP_Key3Right; /*!< Key 3 Right */
  }
  AccHw_CRYP_KeyInitTypeDef;
  /**
    * @brief   CRYP Initialization Vectors (IV) structure definition
    */
  typedef struct
  {
    uint32_t CRYP_IV0Left;  /*!< Init Vector 0 Left  */
    uint32_t CRYP_IV0Right; /*!< Init Vector 0 Right */
    uint32_t CRYP_IV1Left;  /*!< Init Vector 1 left  */
    uint32_t CRYP_IV1Right; /*!< Init Vector 1 Right */
  }
  AccHw_CRYP_IVInitTypeDef;

  /**
    * @brief  CRYP context swapping structure definition
    */
  typedef struct
  {
    /*!< Configuration */
    uint32_t CR_bits9to2;
    /*!< KEY */
    uint32_t CRYP_IV0LR;
    uint32_t CRYP_IV0RR;
    uint32_t CRYP_IV1LR;
    uint32_t CRYP_IV1RR;
    /*!< IV */
    uint32_t CRYP_K0LR;
    uint32_t CRYP_K0RR;
    uint32_t CRYP_K1LR;
    uint32_t CRYP_K1RR;
    uint32_t CRYP_K2LR;
    uint32_t CRYP_K2RR;
    uint32_t CRYP_K3LR;
    uint32_t CRYP_K3RR;
  }
  AccHw_CRYP_Context;

  /**
    * @}
    */

  /* Exported constants --------------------------------------------------------*/

  /** @defgroup CRYP_Exported_Constants
    * @{
    */

  /** @defgroup CRYP_Algorithm_Direction
    * @{
    */
#define AccHw_CRYP_AlgoDir_Encrypt      ((uint16_t)0x0000)
#define AccHw_CRYP_AlgoDir_Decrypt      ((uint16_t)0x0004)


  /**
    * @}
    */

  /** @defgroup CRYP_Algorithm_Mode
    * @{
    */


  /*!< AES Modes */
#define AccHw_CRYP_AlgoMode_AES_ECB     ((uint16_t)0x0020)
#define AccHw_CRYP_AlgoMode_AES_Key     ((uint16_t)0x0038)

  /**
    * @}
    */

  /** @defgroup CRYP_flags_definition
    * @{
    */
#define AccHw_CRYP_FLAG_BUSY            ((uint8_t)0x10)  /*!< The CRYP core is currently processing a block of data or a key preparation (for AES decryption).*/
  
  /**
    * @}
    */


  /** @defgroup CRYP_Data_Type
    * @{
    */
#define AccHw_CRYP_DataType_32b         ((uint16_t)0x0000)
#define AccHw_CRYP_DataType_8b          ((uint16_t)0x0080)

  /**
    * @}
    */

  /** @defgroup CRYP_Key_Size_for_AES_only
    * @{
    */
#define AccHw_CRYP_KeySize_128b         ((uint16_t)0x0000)
#define AccHw_CRYP_KeySize_192b         ((uint16_t)0x0100)
#define AccHw_CRYP_KeySize_256b         ((uint16_t)0x0200)

  /**
    * @}
    */

  /** @defgroup CRYP_flags_definition
    * @{
    */

#define AccHw_CRYP_FLAG_OFNE            ((uint8_t)0x04)  /*!< Input Fifo service raw interrupt status */
#define AccHw_CRYP_FLAG_OFFU            ((uint8_t)0x08)  /*!< Output Fifo is Full */
  /**
    * @}
    */

  /**
    * @}
    */

  /* Exported macro ------------------------------------------------------------*/
  /* Exported functions --------------------------------------------------------*/

  /*  Function used to set the CRYP configuration to the default reset state ****/
  void AccHw_CRYP_DeInit(void);

  /* CRYP Initialization and Configuration functions ****************************/
  void AccHw_CRYP_Init(AccHw_CRYP_InitTypeDef* CRYP_InitStruct);
  void AccHw_CRYP_StructInit(AccHw_CRYP_InitTypeDef* CRYP_InitStruct);
  void AccHw_CRYP_KeyInit(AccHw_CRYP_KeyInitTypeDef* CRYP_KeyInitStruct);
  void AccHw_CRYP_KeyStructInit(AccHw_CRYP_KeyInitTypeDef* CRYP_KeyInitStruct);
  void AccHw_CRYP_Cmd(AccHw_FunctionalState NewState);

  /* CRYP Data processing functions *********************************************/
  void AccHw_CRYP_FIFOFlush(void);


#endif /*__STM32F2XX_AccHw_CRYP_H */

  /**
    * @}
    */

  /**
    * @}
    */

  /************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
