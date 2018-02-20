/**
  @page CHACHA20-POLY1305 Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    CHACHA20-POLY1305/Enc_Dec/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "CHACHA20-POLY1305" example.
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
This example describes how to use the STM32 Cryptographic Library CHACHA20-POLY1305
algorithm and the different steps to perform CHACHA20-POLY1305 Encryption/Decryption processes.

This example is split into two parts:
The first part is to: 
1 - Encrypt DATA with CHACHA20-POLY1305
2 - Generate authentication TAG
3 - Compare between the generated TAG data and expected generated TAG
4 - Compare between the encrypted data and expected encrypted data 

In case of successful Encryption operations CHACHA20-POLY1305 algorithm routines 
can return CHACHA20POLY1305_SUCCESS or one of the following error codes in case of fail:

  - CHACHA20POLY1305_ERR_BAD_PARAMETER
  - CHACHA20POLY1305_ERR_BAD_OPERATION

The second part is to:
1 - Decrypt DATA in CHACHA20-POLY1305
2 - Check the authentication TAG     
3 - Compare between the decrypted data and expected decrypted data

CHACHA20-POLY1305 algorithm routines can return AUTHENTICATION_SUCCESSFUL in case 
of successful Decryption operations or one of the following error codes in case of fail:
 
  - CHACHA20POLY1305_ERR_BAD_PARAMETER
  - CHACHA20POLY1305_ERR_BAD_OPERATION 
  - CHACHA20POLY1305_ERR_BAD_CONTEXT 
  - AUTHENTICATION_FAILED
  
The green LED will be toggled three times each 500 milliseconds before starting 
the CHACHA20-POLY1305 algorithms operations.    
In case of successful Encryption and Decryption operations the green led will 
be turned on and in case of fail it will be toggled each 250 milliseconds in an 
infinity loop. 
  
@note NIST vectors examples for CHACHA20-POLY1305 available at:
" ChaCha20 and Poly1305 for IETF protocols draft-irtf-cfrg-chacha20-poly1305-10"
February 20, 2015.
Available at:
 https://tools.ietf.org/html/draft-irtf-cfrg-chacha20-poly1305-10#section-2.8.1

@par Directory contents 

  - CHACHA20-POLY1305/Enc_Dec/Inc/stm32f0xx_hal_conf.h    HAL configuration file        
  - CHACHA20-POLY1305/Enc_Dec/Inc/stm32f0xx_it.h          Interrupt handlers header file
  - CHACHA20-POLY1305/Enc_Dec/Inc/main.h                  Header for main.c module      
  - CHACHA20-POLY1305/Enc_Dec/Src/stm32f0xx_it.c          Interrupt handlers            
  - CHACHA20-POLY1305/Enc_Dec/Src/main.c                  Main program                  
  - CHACHA20-POLY1305/Enc_Dec/Src/system_stm32f0xx.c      STM32F1xx system source file  


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