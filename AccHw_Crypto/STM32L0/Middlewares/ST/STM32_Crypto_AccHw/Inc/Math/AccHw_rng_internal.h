/**
  ******************************************************************************
  * @file    AccHw_ecc.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Provides Elliptic Curve Cryptography (ECC) primitives.
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
  
/* Includes ------------------------------------------------------------------*/

typedef struct
{  
  uint8_t mRNGstate[36u];  /*!< Underlying DRBG context. It is initialized by \ref RNGinit */

  uint32_t mFlag;        /*!< Used to check if the random state has been mFlag */
} AccHw_RNGstate_stt;

/** 
  * @brief  Structure used by RNGgenBytes or RNGgenWords to provide the optional additional input
  */
typedef struct
{    
  uint8_t* pmAddInput;      /*!< Additional input */
  
  int32_t mAddInputSize;    /*!< Size of additional input */
} AccHw_RNGaddInput_stt;

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
