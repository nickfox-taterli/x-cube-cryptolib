/**
  @page ARC4_ENCRYPTION  ARC4 Encryption/Decryption 
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    ARC4/Encryption_Decryption/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "ARC4 Encryption/Decryption" example.
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

This example describes how to use the STM32 Cryptographic Library ARC4 algorithm
and the different steps (Initialization/Append data/Finalization) to perform ARC4
Encryption/Decryption processes for both ARC4 modes with Key length is 40 bits.

This example is split into two parts:
The first part is to: 
1 - Encrypt DATA with ARC4  
2 - Compare between the encrypted data and expected encrypted data 

ARC4 algorithm routines can return ARC4_SUCCESS in case of successful encryption 
operations or one of the following error codes in case of fail:
 
  - ARC4_ERR_BAD_OPERATION, 
  - ARC4_ERR_BAD_CONTEXT,
  - ARC4_ERR_BAD_PARAMETER.

The second part is to:
1 - Decrypt DATA with ARC4  
2 - Compare between the decrypted data and expected decrypted data

ARC4 algorithm routines can return ARC4_SUCCESS in case of successful decryption
operations or one of the following error codes in case of fail:
 
  - ARC4_ERR_BAD_OPERATION, 
  - ARC4_ERR_BAD_CONTEXT,
  - ARC4_ERR_BAD_PARAMETER.
  
The green LED will be toggled three times each 500 milliseconds before starting 
the ARC4 algorithm operations.    
In case of successful Encryption and Decryption operations the green led will 
be turned on and in case of fail it will be toggled each 250 milliseconds in an 
infinity loop. 

@note vectors examples for ARC4 are taken from RFC Publication:
Test Vectors for the Stream Cipher RC4", May 2011"
Available at:
  http://www.rfc-editor.org/rfc/pdfrfc/rfc6229.txt.pdf

@par Directory contents 

  - ARC4/Encryption_Decryption/Inc/STM32f4xx_hal_conf.h    HAL configuration file
  - ARC4/Encryption_Decryption/Inc/STM32f4xx_it.h          Interrupt handlers header file
  - ARC4/Encryption_Decryption/Inc/main.h                  Header for main.c module  
  - ARC4/Encryption_Decryption/Src/STM32f4xx_it.c          Interrupt handlers
  - ARC4/Encryption_Decryption/Src/main.c                  Main program
  - ARC4/Encryption_Decryption/Src/system_stm32f4xx.c      STM32F4xx system source file


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