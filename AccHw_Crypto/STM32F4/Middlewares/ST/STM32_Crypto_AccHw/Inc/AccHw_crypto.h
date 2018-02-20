/**
  ******************************************************************************
  * @file    AccHw_crypto.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   This file contains all the functions prototypes for the config firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Image SW License Agreement V2, (the "License");
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

#include "AccHw_config.h"
#include "Driver_Crypto_STM32F4xx\stm32f4xx_AccHw.h"


/* List of automatically enabled defines and checks */
#if  defined ( __GNUC__ )
#ifndef __weak
#define __weak   __attribute__((weak))
#endif /* __weak */
#endif

#if defined(INCLUDE_AccHw_AES128) || defined(INCLUDE_AccHw_AES192) ||  defined(INCLUDE_AccHw_AES256)
#define INCLUDE_AccHw_AES /*!< Automatically defined if AES has been selected */
#endif

#if defined(INCLUDE_AccHw_RSA) || defined (INCLUDE_AccHw_ECC)
#define INCLUDE_AccHw_MATH /*!< The Multiprecision Math engine is included */
#endif

/*************************************************************************************************
***-*-*-*-*--**- SOME CHECKS, DON'T MODIFY -**--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**
*************************************************************************************************/
#if (defined(INCLUDE_AccHw_ENCRYPTION) || defined(INCLUDE_AccHw_DECRYPTION)) && !(defined(INCLUDE_AccHw_AES) || defined(INCLUDE_ARC4))
#error "Either encryption or decryption has been specified but no AES are present"
#elif (!defined(INCLUDE_AccHw_ENCRYPTION) && !defined(INCLUDE_AccHw_DECRYPTION)) && (defined(INCLUDE_AccHw_AES) || defined(INCLUDE_DES_CORE))
#error "AES present but without encryption or decryption functionalities!"
#endif

#ifdef AccHw_CRL_CPU_SUPPORT_MISALIGNED
#ifndef AccHw_CRL_ENDIANNESS
#error "With AccHw_CRL_CPU_SUPPORT_MISALIGNED=1 a definition for AccHw_CRL_ENDIANNESS is required!"
#endif
#endif

#if defined(INCLUDE_AccHw_GCM) && !defined(INCLUDE_AccHw_AES)
#error "GCM is currently supported only by AES, but AES has not be included, please include AES or remove GCM"
#endif

#if defined(INCLUDE_AccHw_CMAC) && !defined(INCLUDE_AccHw_AES)
#error "CMAC is currently supported only by AES, but AES has not be included, please include AES or remove GCM"
#endif

#if defined(INCLUDE_AccHw_KEY_WRAP) && !defined(INCLUDE_AccHw_AES)
#error "KWRAP is currently supported only by AES, but AES has not be included, please include AES or remove KWRAP"
#endif

#if defined(INCLUDE_AccHw_CCM) && !defined(INCLUDE_AccHw_AES)
#error "CCM is currently supported only by AES, but AES has not be included, please include AES or remove CCM"
#endif

#if defined(INCLUDE_AccHw_POLY1305) && !defined(INCLUDE_AccHw_AES128)
#error "POLY1305-AES requires INCLUDE_AccHw_AES_128"
#endif

#if defined(INCLUDE_AccHw_RSA) && !defined(AccHw_RSA_WINDOW_SIZE)
#define AccHw_RSA_WINDOW_SIZE 1
#endif

/*************************************************************************************************
***-*-*-*-*--**- STD PERIPHERAL DRIVERS INCLUSION -**--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-***
*************************************************************************************************/
#define CL_ON_STM32

/*************************************************************************************************
***-*-*-*-*--**- CRYPTO LIBRARY INCLUSIONS -**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-***
*************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include "Common/AccHw_types.h"
#include "Common/AccHw_macros.h"
#include "Common/AccHw_err_codes.h"
#include "Common/AccHw_sk.h"


#ifdef INCLUDE_AccHw_AES
#include "AES/AccHw_aes.h"
#endif


#ifdef INCLUDE_AccHw_MATH
#include "Math/AccHw_math.h"
#endif

#ifdef INCLUDE_AccHw_RSA
#include "RSA/AccHw_rsa.h"
#endif

#ifdef INCLUDE_AccHw_ECC
#include "ECC/AccHw_ecc.h"
#endif
#ifdef INCLUDE_AccHw_POLY1305
#include "POLY1305/AccHw_poly1305.h"
#endif



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
