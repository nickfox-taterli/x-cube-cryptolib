/**
  ******************************************************************************
  * @file    Examples_Crypto/Inc/main.h 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Header for main.c module
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
#ifndef __MAIN_H
#define __MAIN_H


/** @defgroup AESExample AES Example
  * @{
  */
#define Example_AES128bitsCCM            0x0001 
#define Example_AES128bitsCFB            0x0002
#define Example_AES128bitsCMAC           0x0003
#define Example_AES128bitsGCM            0x0005
#define Example_AES128bitsKEYWRAP        0x0006
#define Example_AES128bitsOFB            0x0007
#define Example_AES256bitsXTS            0x000A
/**
* @}
*/   

/** @defgroup ECCExample ECC Example
  * @{
  */
#define Example_ECCKeyGenSignVerif       0x0070
#define Example_ECCSignVerif             0x0071
/**
* @}
*/   

/** @defgroup POLY1305Example POLY1305 Example
  * @{
  */
#define Example_POLY1305GetMACVerifMAC   0x00A0
/**
* @}
*/   

/** @defgroup RSAExample RSA Example
  * @{
  */
#define Example_RSAEncDec                 0x00C0
/**
* @}
*/   

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "crypto.h"  
#include "AccHw_crypto.h"  

    
#ifdef Example_AES128bitsCFB
#include "example_AES128bits_cfb.h"
#endif

#ifdef Example_AES128bitsOFB
#include "example_aes128bits_ofb.h"
#endif

#ifdef Example_AES128bitsCMAC
#include "example_aes128bits_cmac.h"
#endif

#ifdef Example_AES128bitsCCM
#include "example_aes128bits_ccm.h"
#endif

#ifdef Example_AES128bitsGCM
#include "example_aes128bits_gcm.h"
#endif

#ifdef Example_AES128bitsKEYWRAP
#include "example_aes128bits_keywrap.h"
#endif
 
#ifdef Example_AES256bitsXTS
#include "example_aes256bits_xts.h"
#endif
 
#ifdef Example_POLY1305GetMACVerifMAC
#include "example_poly1305_getmac_verifymac.h"
#endif

#ifdef Example_ECCKeyGenSignVerif 
#include "example_ecc_keygen_sign_verify.h"
#endif

#ifdef Example_ECCSignVerif 
#include "example_ecc_sign_verify.h"
#endif

#ifdef Example_RSAEncDec
#include "example_rsa_encdec.h"
#endif


/* Exported types ------------------------------------------------------------*/
typedef enum {PASSED = 0, FAILED = !PASSED} TestStatus;
/* Exported constants --------------------------------------------------------*/
extern uint32_t Example_Status;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
