/**
  @page ECC  ECC_KeyGeneration_SignatureVerification Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    ECC_KeyGen_SignVerif/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "ECC_KeyGeneration_SignatureVerification" example.
  ******************************************************************************
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
  * limitations under the License
  * 
  ******************************************************************************
   @endverbatim

@par Example Description
This example describes how to use the STM32 Cryptographic Library ECC algorithm 
in example of an ECC key generation and signature verification with Parameters 
for Elliptic Curve: P-192, P-256 and P-384.

ECC starts by initilizing the Elliptic Curve parameters and generating the ECC 
key pair using RNG algorithm. When Public Key is validated, signature object 
will be initialized and prepare the structure for the ECDSA signature 
verification based on SHA-256.

ECC functions can return ECC_SUCCESS in case of successful ECC operation or one
of the following error codes in case of fail:
  - HASH_ERR_BAD_OPERATION,
  - HASH_ERR_BAD_CONTEXT,
  - HASH_ERR_BAD_PARAMETER,
  - ERR_MEMORY_FAIL, 
  - ECC_ERR_BAD_PARAMETER,
  - ECC_ERR_BAD_CONTEXT,
  - ECC_ERR_MISSING_EC_PARAMETE,
  - MATH_ERR_BIGNUM_OVERFLOW,
  - MATH_ERR_INTERNAL,
  - RNG_ERR_INTERNAL,
  - RNG_ERR_UNINIT_STATE 
  - SIGNATURE_INVALID.
  
The green LED will be toggled three times each 500 milliseconds before starting 
the ECC algorithms operations.    
In case of successful operations the green led will be turned on and in case of 
fail it will be toggled each 250 milliseconds in an infinity loop.   
  
User application needs to check on returned value to determine which action will
be run in both fail and success cases.

@par Directory contents 

  - ECC/ECC_KeyGen_SignVerif/Inc/STM32f4xx_hal_conf.h    HAL configuration file
  - ECC/ECC_KeyGen_SignVerif/Inc/STM32f4xx_it.h          Interrupt handlers header file
  - ECC/ECC_KeyGen_SignVerif/Inc/main.h                  Header for main.c module  
  - ECC/ECC_KeyGen_SignVerif/Src/STM32f4xx_it.c          Interrupt handlers
  - ECC/ECC_KeyGen_SignVerif/Src/main.c                  Main program
  - ECC/ECC_KeyGen_SignVerif/Src/system_stm32f4xx.c      STM32F4xx system source file


@par Hardware and Software environment

  - This example runs on STM32F401RE devices.
    
  - This example has been tested with NUCLEO-F401RE Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */