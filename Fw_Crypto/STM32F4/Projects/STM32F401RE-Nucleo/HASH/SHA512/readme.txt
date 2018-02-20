/**
  @page HASH  SHA-512 digest generation example

  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    HASH/SHA512/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "SHA-512 digest generation" example.
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
  * limitations under the License.
  *
  ******************************************************************************
   @endverbatim

@par Example Description
This example describes how to use the STM32 Cryptographic Library SHA-512 Hash  
algorithm to generate message digest.

The SHA-512 Hash algorithm is configured to generate 64 bytes hash digest 
(CRL_SHA512_SIZE) and in default mode (E_HASH_DEFAULT).

SHA-512 hash routines can return HASH_SUCCESS in case of successful hash 
operation or one of the following error codes in case of fail: 
  - HASH_ERR_BAD_PARAMETER,
  - HASH_ERR_BAD_CONTEXT, 
  - HASH_ERR_BAD_OPERATION.

A comparison between the generated digest data and expected digest data is done
to check that the input data have been correctly hashed.

The green LED will be toggled three times each 500 milliseconds before starting 
the SHA512 algorithms operations.    
In case of successful hash operations the green led will be turned on and 
in case of fail it will be toggled each 250 milliseconds in an infinity loop.
  
@note NIST vectors example for HASH 512 are taken from:
"Federal Information Processing Standards Publication 180-2 2002 August 1
Specifications for the SECURE HASH STANDARD"
	Available at:
	http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf

@par Directory contents 

  - HASH/SHA512/Inc/STM32f4xx_hal_conf.h    HAL configuration file
  - HASH/SHA512/Inc/STM32f4xx_it.h          Interrupt handlers header file
  - HASH/SHA512/Inc/main.h                  Header for main.c module  
  - HASH/SHA512/Src/STM32f4xx_it.c          Interrupt handlers
  - HASH/SHA512/Src/main.c                  Main program
  - HASH/SHA512/Src/system_stm32f4xx.c      STM32F4xx system source file


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