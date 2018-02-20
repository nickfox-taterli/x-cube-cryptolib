/**
  @page ED25519 KeyGen_Sign_Verif Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    KeyGen_Sign_Verif/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "ED25519 in KeyGen_Sign_Verif" example.
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
   @endverbatim

@par Example Description
This example describes how to use the STM32 Cryptographic Library ED25519 algorithm
in example of an ED25519 key generation,  signing message and signature verification.

This example is split into two parts:
The first part is to:
1 - Generate a secret key using RNG algorithm
2 - Generate a public key using the generated secret key 

ED25519 algorithm routines can return ED25519_SUCCESS in case of successful 
operations or one of the following error codes in case of fail:

  - ED5519_ERR_BAD_PARAMETER, 
  - HASH_ERR_INTERNAL, 
  - RNG_ERR_BAD_PARAMETER
  - RNG_ERR_BAD_PERS_STRING_SIZE, 
  - RNG_ERR_BAD_NONCE_SIZE 

The second part is to :
1 - generate a public key using the secret key
2 - signed the message using the secret key
3 - verify the signature using the generated public key

ED25519 algorithm routines can return ED25519_SUCCESS in case of successful 
operations, AUTHENTICATION_AUTHENTICATION_SUCCESSFUL in case of successful 
athentication or one of the following error codes in case of fail:
 
  - ED25519_ERR_BAD_PARAMETER,
  - HASH_ERR_INTERNAL 
  - AUTHENTICATION_FAILED

The green LED will be toggled three times each 500 milliseconds before starting 
the ED25519 algorithms operations.    
In case of successful Encryption and Decryption operations the green led will 
be turned on and in case of fail it will be toggled each 250 milliseconds in an 
infinity loop. 

@note The vectors examples for ED25519 are taken from:
"Ed25519: high-speed high-security signatures" version 2011.09.27 of the index.html web page
Available at:
 http://ed25519.cr.yp.to/python/sign.input

@par Directory contents 

  - ED25519/KeyGen_Sign_Verif/Inc/STM32f1xx_hal_conf.h    HAL configuration file
  - ED25519/KeyGen_Sign_Verif/Inc/STM32f1xx_it.h          Interrupt handlers header file
  - ED25519/KeyGen_Sign_Verif/Inc/main.h                  Header for main.c module  
  - ED25519/KeyGen_Sign_Verif/Src/STM32f1xx_it.c          Interrupt handlers
  - ED25519/KeyGen_Sign_Verif/Src/main.c                  Main program
  - ED25519/KeyGen_Sign_Verif/Src/system_stm32f1xx.c      STM32F1xx system source file


@par Hardware and Software environment

  - This example runs on STM32F103RB devices.
    
  - This example has been tested with STM32F103RB-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */