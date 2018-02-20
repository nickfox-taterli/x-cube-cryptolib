/**
  @page Curve25519 Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    C25519/KeyGen_KeyExch/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "C25519_KeyGeneration_KeyExchange" example.
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
This example describes how to use the STM32 Cryptographic Library Curve25519 algorithm 
in example of an ECC key generation and signature verification with Parameters 
for Elliptic Curve: P-192, P-256 and P-384.


This example is split into two parts:
The first part is to: 
1- Generate a secret key using RNG algorithm
2- Genreate a public key using the secret key

Curve25519 routines can return C25519_SUCCESS in case of successful operations or 
one of the following error codes in case of fail: 
 - C25519_ERR_BAD_PARAMETER,
 - RNG_ERR_BAD_PARAMETER,
 - RNG_ERR_BAD_ENTROPY_SIZE,
 - RNG_ERR_BAD_PERS_STRING_SIZE, 
 - RNG_ERR_BAD_NONCE_SIZE 

The second part is to:
1 - Generate a public key for the first user using his secret key
2 - Generate a public key for the second user using his secret key
3 - Generate a secret wich can be shared by the two users and used to authenticate
    and encrypt messages between them. 
    
Curve25519 routines can return C25519_SUCCES in case of successful operation or 
C25519_ERR_BAD_PARAMETER in case of fail.
  
The green LED will be toggled three times each 500 milliseconds before starting 
the Curve25519 algorithms operations.    
In case of successful operations the green led will be turned on and in case of 
fail it will be toggled each 250 milliseconds in an infinity loop.   
  
User application needs to check on returned value to determine which action will
be run in both fail and success cases.

@note The vectors examples for Curve25519 are taken from:
 "Curve25519 for ephemeral key exchange in Transport Layer Security (TLS) 
 draft-josefsson-tls-curve25519-06" September 11, 2014.
Available at:
 http://ietfreport.isoc.org/all-ids/draft-josefsson-tls-curve25519-06.txt 

@par Directory contents 

  - C25519/ECC_KeyGen_SignVerif/Inc/STM32l0xx_hal_conf.h    HAL configuration file
  - C25519/ECC_KeyGen_SignVerif/Inc/STM32l0xx_it.h          Interrupt handlers header file
  - C25519/ECC_KeyGen_SignVerif/Inc/main.h                  Header for main.c module  
  - C25519/ECC_KeyGen_SignVerif/Src/STM32l0xx_it.c          Interrupt handlers
  - C25519/ECC_KeyGen_SignVerif/Src/main.c                  Main program
  - C25519/ECC_KeyGen_SignVerif/Src/system_stm32l0xx.c      STM32L0xx system source file


@par Hardware and Software environment

  - This example runs on STM32L053R8 devices.
    
  - This example has been tested with STM32L053R8-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */