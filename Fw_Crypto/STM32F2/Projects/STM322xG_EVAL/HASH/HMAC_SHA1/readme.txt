/**
  @page HASH HMAC_SHA1 Hash Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    HASH/HMAC_SHA1/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "HMAC_SHA1 Hash Example" example.
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
This example describes how to use the STM32 Cryptographic Library SHA1 Hash  
algorithm to generate message digest.

The SHA1 Hash algorithm is used to generate 20 bytes (CRL_SHA1_SIZE) HMAC digest 
of input message.

SHA1 hash routines can return HASH_SUCCESS in case of successful hash operation
or one of the following error codes in case of fail: 
  - HASH_ERR_BAD_PARAMETER,
  - HASH_ERR_BAD_CONTEXT, 
  - HASH_ERR_BAD_OPERATION.

A comparison between the generated digest data and expected digest data is done 
to check that the input data have been correctly hashed.

The green LED will be toggled three times each 500 milliseconds before starting 
the SHA1 algorithms operations.    
In case of successful hash operations the green led will be turned on and 
in case of fail it will be toggled each 250 milliseconds in an infinity loop.

@note FIPS 198 vectors examples for HASH/SHA1 are taken from FIPS Publication:
"The Keyed-Hash Message Authentication Code (HMAC), Issued March 6, 2002"
Available at:
  http://csrc.nist.gov/publications/fips/fips198/fips-198a.pdf

@par Directory contents 

  - HASH/HMAC_SHA1/Inc/STM32f2xx_hal_conf.h    HAL configuration file
  - HASH/HMAC_SHA1/Inc/STM32f2xx_it.h          Interrupt handlers header file
  - HASH/HMAC_SHA1/Inc/main.h                  Header for main.c module  
  - HASH/HMAC_SHA1/Src/STM32f2xx_it.c          Interrupt handlers
  - HASH/HMAC_SHA1/Src/main.c                  Main program
  - HASH/HMAC_SHA1/Src/system_stm32f2xx.c      STM32F2xx system source file


@par Hardware and Software environment

  - This example runs on ST STM32F207VG devices.
    
  - This example has been tested with STM322xG-EVAL RevB board and can be
    easily tailored to any other supported device and development board


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */