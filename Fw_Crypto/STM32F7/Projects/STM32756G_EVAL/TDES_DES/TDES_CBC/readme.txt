/**
  @page TDES_CBC  TDES algorithm in CBC mode

  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    TDES_DES/TDES_CBC/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "TDES CBC modes" example.
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
This example describes how to use the STM32 Cryptographic Library TDES algorithm
and the different steps (Initialization/Append data/Finalization) to perform TDES
Encryption/Decryption processes for CBC mode.

This example is split into two parts:
The first part is to:
1 - Encrypt DATA in CBC mode 
2 - Compare between the encrypted data and expected encrypted data 

TDES algorithm routines can return TDES_SUCCESS in case of successful encryption 
operations or one of the following error codes in case of fail:

  - TDES_ERR_BAD_OPERATION,
  - TDES_ERR_BAD_CONTEXT,
  - TDES_ERR_BAD_PARAMETER.
  - TDES_ERR_BAD_INPUT_SIZE.  

The second part is to:
1 - Decrypt DATA in CBC mode
2 - Compare between the decrypted data and expected decrypted data 

TDES algorithm routines can return TDES_SUCCESS in case of successful decryption 
operations or one of the following error codes in case of fail:

  - TDES_ERR_BAD_OPERATION,
  - TDES_ERR_BAD_CONTEXT,
  - TDES_ERR_BAD_PARAMETER.
  - TDES_ERR_BAD_INPUT_SIZE.  
  
The green LED will be toggled three times each 500 milliseconds before starting 
the TDES algorithms operations.    
In case of successful Encryption and Decryption operations the green led will 
be turned on and in case of fail it will be toggled each 250 milliseconds in an 
infinity loop. 
  
@note NIST vectors examples for TDES CBC are taken from:
"fips 81 - DES MODES OF OPERATION"
Available at:
http://www.itl.nist.gov/fipspubs/fip81.htm

@par Directory contents 

  - TDES_DES/TDES_CBC/Inc/STM32F7xx_hal_conf.h    HAL configuration file
  - TDES_DES/TDES_CBC/Inc/STM32F7xx_it.h          Interrupt handlers header file
  - TDES_DES/TDES_CBC/Inc/main.h                  Header for main.c module  
  - TDES_DES/TDES_CBC/Src/STM32F7xx_it.c          Interrupt handlers
  - TDES_DES/TDES_CBC/Src/main.c                  Main program
  - TDES_DES/TDES_CBC/Src/system_stm32f7xx.c      STM32F7xx system source file


@par Hardware and Software environment

  - This example runs on STM32F756IG devices.
    
  - This example has been tested with STM327x6G-EVAL board revB and can be
    easily tailored to any other supported device and development board.

  - To use LED1, ensure that JP24 is in position 2-3


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */