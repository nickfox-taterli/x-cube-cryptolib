/**
  @page HASH MD5 Hash Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    HASH/MD5/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the MD5 Hash example.
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
This example describes how to use the STM32 Cryptographic Library MD5 Hash  
algorithm to generate message digest.

The MD5 Hash algorithm is configured to generate 16 bytes hash digest 
(CRL_MD5_SIZE) and in default mode (E_HASH_DEFAULT).

MD5 hash routines can return HASH_SUCCESS in case of successful hash operation
or one of the following error codes in case of fail: 
  - HASH_ERR_BAD_PARAMETER,
  - HASH_ERR_BAD_CONTEXT, 
  - HASH_ERR_BAD_OPERATION.

A comparison between the generated digest data and expected digest data is done 
to check that the input data have been correctly hashed. 

The green LED will be toggled three times each 500 milliseconds before starting 
the MD5 algorithms operations.    
In case of successful hash operations the green led will be turned on and 
in case of fail it will be toggled each 250 milliseconds in an infinity loop.

@note vectors examples for HASH/MD5 are taken from RFC Publication:
"The MD5 Message-Digest Algorithm April 1992"
Available at:
  http://www.rfc-editor.org/rfc/pdfrfc/rfc1321.txt.pdf

@par Directory contents 

  - HASH/MD5/Inc/STM32f1xx_hal_conf.h    HAL configuration file
  - HASH/MD5/Inc/STM32f1xx_it.h          Interrupt handlers header file
  - HASH/MD5/Inc/main.h                  Header for main.c module  
  - HASH/MD5/Src/STM32f1xx_it.c          Interrupt handlers
  - HASH/MD5/Src/main.c                  Main program
  - HASH/MD5/Src/system_stm32f1xx.c      STM32F1xx system source file


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