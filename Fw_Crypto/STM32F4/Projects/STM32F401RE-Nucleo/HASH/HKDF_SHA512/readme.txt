/**
  @page HASH HKDF_SHA512 Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    HASH/HKDF_SHA512/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "HKDF_SHA512 Hash Example" example.
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
This example describes how to use the STM32 Cryptographic Library HKDF SHA512 Hash  
algorithm to generate message digest.

The HKDF SHA512 algorithm is used to derive a secret key from initial key.

HKDF SHA512 routines can return HASH_SUCCESS in case of successful operation
or one of the following error codes in case of fail: 
  - HASH_ERR_BAD_PARAMETER,
  - HASH_ERR_BAD_CONTEXT, 
  - HASH_ERR_INTERNAL.

A comparison between the generated key and expected generated key is done.

The green LED will be toggled three times each 500 milliseconds before starting 
the SHA1 algorithms operations.    
In case of successful hash operations the green led will be turned on and 
in case of fail it will be toggled each 250 milliseconds in an infinity loop.

@par Directory contents 

  - HASH/HKDF_SHA512/Inc/STM32f4xx_hal_conf.h    HAL configuration file
  - HASH/HKDF_SHA512/Inc/STM32f4xx_it.h          Interrupt handlers header file
  - HASH/HKDF_SHA512/Inc/main.h                  Header for main.c module  
  - HASH/HKDF_SHA512/Src/STM32f4xx_it.c          Interrupt handlers
  - HASH/HKDF_SHA512/Src/main.c                  Main program
  - HASH/HKDF_SHA512/Src/system_stm32f4xx.c      STM32F4xx system source file


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