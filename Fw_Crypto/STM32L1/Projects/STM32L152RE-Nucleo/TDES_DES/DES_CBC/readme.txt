/**
  @page DES_CBC  TDES algorithm in CBC mode

  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    TDES_DES/DES_CBC/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "DES CBC modes" example.
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
This example describes how to use the STM32 Cryptographic Library DES algorithm
and the different steps (Initialization/Append data/Finalization) to perform DES
Encryption/Decryption processes for CBC mode.

This example is split into two parts:
The first part is to:
1 - Encrypt DATA in CBC mode 
2 - Compare between the encrypted data and expected encrypted data 

DES algorithm routines can return DES_SUCCESS in case of successful encryption 
operations or one of the following error codes in case of fail:

  - DES_ERR_BAD_OPERATION,
  - DES_ERR_BAD_CONTEXT,
  - DES_ERR_BAD_PARAMETER.
  - DES_ERR_BAD_INPUT_SIZE.  

The second part is to:
1 - Decrypt DATA in CBC mode
2 - Compare between the decrypted data and expected decrypted data 

DES algorithm routines can return DES_SUCCESS in case of successful decryption 
operations or one of the following error codes in case of fail:

  - DES_ERR_BAD_OPERATION,
  - DES_ERR_BAD_CONTEXT,
  - DES_ERR_BAD_PARAMETER.
  - DES_ERR_BAD_INPUT_SIZE.  
  
The green LED will be toggled three times each 500 milliseconds before starting 
the DES algorithms operations.    
In case of successful Encryption and Decryption operations the green led will 
be turned on and in case of fail it will be toggled each 250 milliseconds in an 
infinity loop.  

  
@note NIST vectors examples for DES CBC are taken from:
"fips 81 - DES MODES OF OPERATION"
Available at:
http://www.itl.nist.gov/fipspubs/fip81.htm

@par Directory contents 

  - TDES_DES/DES_CBC/Inc/STM32l1xx_hal_conf.h    HAL configuration file
  - TDES_DES/DES_CBC/Inc/STM32l1xx_it.h          Interrupt handlers header file
  - TDES_DES/DES_CBC/Inc/main.h                  Header for main.c module  
  - TDES_DES/DES_CBC/Src/STM32l1xx_it.c          Interrupt handlers
  - TDES_DES/DES_CBC/Src/main.c                  Main program
  - TDES_DES/DES_CBC/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment

  - This example runs on STM32L152RE devices.
    
  - This example has been tested with STM32L152RE-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */