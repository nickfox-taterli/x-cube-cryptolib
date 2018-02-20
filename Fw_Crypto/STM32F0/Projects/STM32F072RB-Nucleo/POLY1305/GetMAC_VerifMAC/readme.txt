/**
  @page POLY1305 GetMAC_VerifMAC Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    POLY1305/GetMAC_VerifMAC/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "GetMAC_VerifMAC in POLY1305 " example.
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
This example describes how to use the STM32 Cryptographic Library POLY1305
algorithm and the different steps (Initialization/Append data/Finalization) 
to authentication a message with POLY1305.

This example is split into two parts:
The first part is to 
1 - Generate authentication TAG to the input data 
2 - Compare between the generated TAG and expected TAG

POLY1305 algorithm routines can return POLY1305_SUCCESS in case of successful 
generation of TAG or one of the following error codes in case of fail:
 
  - POLY1305_ERR_BAD_OPERATION,
  - POLY1305_ERR_BAD_CONTEXT,
  - POLY1305_ERR_BAD_PARAMETER.

The second part is to:
1 - Check authentication TAG

POLY1305 algorithm routines can return AUTHENTICATION_SUCCESSFUL in case of successful 
verification of TAG or one of the following error codes in case of fail:
 
  - POLY1305_ERR_BAD_OPERATION,
  - POLY1305_ERR_BAD_CONTEXT,
  - POLY1305_ERR_BAD_PARAMETER,
  - AUTHENTICATION_FAILED. 
  
@note vectors examples for POLY1305 are taken from:
 "The Poly1305-AES message-authentication code"
  Available at:
 http://cr.yp.to/mac/poly1305-20050329.pdf

@par Directory contents 

  - POLY1305/GetMAC_VerifMAC/Inc/STM32f0xx_hal_conf.h    HAL configuration file
  - POLY1305/GetMAC_VerifMAC/Inc/STM32f0xx_it.h          Interrupt handlers header file
  - POLY1305/GetMAC_VerifMAC/Inc/main.h                  Header for main.c module  
  - POLY1305/GetMAC_VerifMAC/Src/STM32f0xx_it.c          Interrupt handlers
  - POLY1305/GetMAC_VerifMAC/Src/main.c                  Main program
  - POLY1305/GetMAC_VerifMAC/Src/system_stm32f0xx.c      STM32F0xx system source file


@par Hardware and Software environment

  - This example runs on STM32F072RB devices.
    
  - This example has been tested with STM32F072RB-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */