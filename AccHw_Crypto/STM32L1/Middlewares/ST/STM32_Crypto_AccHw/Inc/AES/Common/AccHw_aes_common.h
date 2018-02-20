/**
  ******************************************************************************
  * @file    AccHw_aes_common.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   AES common functions and definitions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
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
  *******************************************************************************/
#ifndef __AES_AccHw_COMMON_H__
#define __AES_AccHw_COMMON_H__

#ifdef __cplusplus
 extern "C" {
#endif

/*----------------- Types declaration -------------*/
/** @addtogroup AES
  * @{
  */

#define CRL_AES128_KEY   16 /*!< Number of bytes (uint8_t) necessary to store an AES key of 128 bits. */
#define CRL_AES128_EXPANDED_KEY  44 /*!< Number of ints (uint32_t) necessary to store an expanded AES key of 128 bits. */
#define AES_TIMEOUT    ((uint32_t) 0x00010000)*4


#define CRL_AES_BLOCK     16 /*!< Number of bytes (uint8_t) necessary to store an AES block. */


#define AccHw_CRL_AES_MAX_EXPKEY_SIZE 44 /*!< The max size of the AES expanded key (in uint32_t) according to the INCLUDE OPTIONS */


 /**
  * @}
  */


/** @addtogroup AESCBC
  * @{
  */  
typedef struct
{  
  uint32_t   mContextId; /*!< Unique ID of this context. \b Not \b used in current implementation. */  
  AccHw_SKflags_et mFlags; /*!< 32 bit mFlags, used to perform keyschedule, choose betwen hw/sw and future use */  
  const uint8_t *pmKey; /*!< Pointer to original Key buffer */  
  const uint8_t *pmIv; /*!< Pointer to original Initialization Vector buffer */  
  int32_t   mIvSize; /*!< Size of the Initialization Vector in bytes */  
  uint32_t   amIv[4]; /*!< Temporary result/IV */  
  int32_t   mKeySize; /*!< Key length in bytes */
  uint32_t   amExpKey[AccHw_CRL_AES_MAX_EXPKEY_SIZE]; /*!< Expanded AES key */
} AccHw_AESECBctx_stt; /*!< AES context structure for CBC mode */


 /**
  * @}
  */


/** @addtogroup AESlowlevel AES
  * @{
  */
  


typedef struct
{  
  uint32_t   mContextId;  /*!< Unique ID of this context. \b Not \b used in current implementation. */ 
  AccHw_SKflags_et mFlags;  /*!< 32 bit mFlags, used to perform keyschedule, choose betwen hw/sw and future use */
  const uint8_t *pmKey; /*!< Pointer to original Key buffer */
  const uint8_t *pmIv;   /*!< Pointer to original Initialization Vector buffer */
  int32_t   mIvSize; /*!< Size of the Initialization Vector in bytes */
  uint32_t   amIv[4];   /*!< This is the current IV value. Attention should be made to not overflow this, as in DES it
                             has only 2 words */
} SKctx_stt;   /*!< AES and DES context structure can be safely casted to SKctx_stt for usage with hw engines
                    This features allows to not duplicate hw code for different algorithms */

 /**
  * @}
  */

  
#ifdef __cplusplus
}
#endif

#endif  /*__AES_AccHw_COMMON_H__*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
