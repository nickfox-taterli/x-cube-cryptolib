/**
  @page CHACHA20 Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    CHACHA20/Enc_Dec/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "CHACHA20" example.
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
This example describes how to use the STM32 Cryptographic Library CHACHA20 algorithm
and the different steps (Initialization/Append data/Finalization) to perform CHACHA20
Encryption/Decryption processes.

This example is split into two parts:
The first part is to: 
1 - Encrypt DATA with CHACHA20  
2 - Compare between the encrypted data and expected encrypted data 

CHACHA20 algorithm routines can return CHACHA_SUCCESS in case of successful encryption 
operations or one of the following error codes in case of fail:
 
  - CHACHA_ERR_BAD_PARAMETER,
  - CHACHA_ERR_BAD_OPERATION,
  - CHACHA_ERR_BAD_CONTEXT.

The second part is to:
1 - Decrypt DATA in with CHACHA20
2 - Compare between the decrypted data and expected decrypted data

CHACHA20 algorithm routines can return CHACHA_SUCCESS in case of successful decryption
operations or one of the following error codes in case of fail:
 
  - CHACHA_ERR_BAD_PARAMETER,
  - CHACHA_ERR_BAD_OPERATION,
  - CHACHA_ERR_BAD_CONTEXT.
  
The green LED will be toggled three times each 500 milliseconds before starting 
the CHACHA20 algorithm operations.    
In case of successful Encryption and Decryption operations the green led will 
be turned on and in case of fail it will be toggled each 250 milliseconds in an 
infinity loop. 

@note The vectors examples for CHACHA20 are taken from:
"Test Vectors for the Stream Cipher ChaCha draft-strombergson-chacha-test-vectors-01"
December 31, 2013.
Available at:
 https://tools.ietf.org/html/draft-strombergson-chacha-test-vectors-01

@par Directory contents 

  - CHACHA20/Encryption_Decryption/Inc/STM32f1xx_hal_conf.h    HAL configuration file
  - CHACHA20/Encryption_Decryption/Inc/STM32f1xx_it.h          Interrupt handlers header file
  - CHACHA20/Encryption_Decryption/Inc/main.h                  Header for main.c module  
  - CHACHA20/Encryption_Decryption/Src/STM32f1xx_it.c          Interrupt handlers
  - CHACHA20/Encryption_Decryption/Src/main.c                  Main program
  - CHACHA20/Encryption_Decryption/Src/system_stm32f1xx.c      STM32F1xx system source file


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