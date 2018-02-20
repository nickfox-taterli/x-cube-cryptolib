/**
  @page AES  AES128_CTR Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    AES128_CTR/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "AES128 in CTR mode" example.
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
This example describes how to use the STM32 Cryptographic Library AES algorithm
and the different steps (Initialization/Append data/Finalization) to perform AES
128 bits Encryption/Decryption processes for CTR mode .

This example is split into two parts:
The first part is to:
1 - Encrypt DATA in CTR mode 
2 - Compare between the encrypted data and expected encrypted data 

AES algorithm routines can return AES_SUCCESS in case of successful encryption 
operations or one of the following error codes in case of fail:

  - AES_ERR_BAD_OPERATION,
  - AES_ERR_BAD_CONTEXT,
  - AES_ERR_BAD_PARAMETER.

The second part is to:
1 - Decrypt DATA in CTR mode
2 - Compare between the decrypted data and expected decrypted data 

AES algorithm routines can return AES_SUCCESS in case of successful decryption 
operations or one of the following error codes in case of fail:

  - AES_ERR_BAD_OPERATION,
  - AES_ERR_BAD_CONTEXT,
  - AES_ERR_BAD_PARAMETER.

The green LED will be toggled three times each 500 milliseconds before starting 
the AES algorithms operations.    
In case of successful Encryption and Decryption operations the green led will 
be turned on and in case of fail it will be toggled each 250 milliseconds in an 
infinity loop. 

@note NIST vectors examples for AES CTR are taken from:
"Recommendation for Block Cipher Modes of Operation, 2001 Edition"
Available at:
 http://csrc.nist.gov/publications/nistpubs/800-38a/sp800-38a.pdf

@par Directory contents 

  - AES/AES128_CTR/Inc/STM32f3xx_hal_conf.h    HAL configuration file
  - AES/AES128_CTR/Inc/STM32f3xx_it.h          Interrupt handlers header file
  - AES/AES128_CTR/Inc/main.h                  Header for main.c module  
  - AES/AES128_CTR/Src/STM32f3xx_it.c          Interrupt handlers
  - AES/AES128_CTR/Src/main.c                  Main program
  - AES/AES128_CTR/Src/system_stm32f3xx.c      STM32F3xx system source file


@par Hardware and Software environment

  - This example runs on STM32F302R8 devices.
    
  - This example has been tested with STM32F302R8-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */