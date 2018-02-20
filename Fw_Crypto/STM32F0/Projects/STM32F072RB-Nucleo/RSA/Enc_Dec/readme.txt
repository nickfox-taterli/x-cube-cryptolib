/**
  @page RSA Enc_Dec encryption/decryption Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    RSA/Enc_Dec/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "RSA encryption/decryption" example.
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
This example describes how to use the STM32 Cryptographic Library RSA encryption/decryption 
algorithm and the different steps to perform RSA Encryption/Decryption processes.

This example is split into two parts:
The first part is to: 
1 - Encrypt DATA with RSA  

RSA encryption algorithm routines can return RSA_SUCCESS in case of successful encryption 
operations or one of the following error codes in case of fail:
 
  - RSA_ERR_BAD_PARAMETER,
  - RSA_ERR_MESSAGE_TOO_LONG,
  - RSA_ERR_BAD_OPERATION.

The second part is to:
1 - Decrypt DATA in with RSA
2 - Compare between the decrypted data and expected decrypted data

RSA decryption algorithm routines can return RSA_SUCCESS in case of successful encryption 
operations or RSA_ERR_GENERIC  in case of fail.

The green LED will be toggled three times each 500 milliseconds before starting 
the RSA encryption/decryption algorithm operations.    
In case of successful Encryption and Decryption operations the green led will 
be turned on and in case of fail it will be toggled each 250 milliseconds in an 
infinity loop. 

@par Directory contents 

  - RSA/Enc_Decn/Inc/stm32f0xx_hal_conf.h    HAL configuration file
  - RSA/Enc_Decn/Inc/stm32f0xx_it.h          Interrupt handlers header file
  - RSA/Enc_Decn/Inc/main.h                  Header for main.c module  
  - RSA/Enc_Decn/Src/stm32f0xx_it.c          Interrupt handlers
  - RSA/Enc_Decn/Src/main.c                  Main program
  - RSA/Enc_Decn/Src/system_stm32f0xx.c      STM32F0xx system source file


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