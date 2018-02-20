/**
  @page RSA_Signature  RSA Signature example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    RSA/RSA_Signature/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "RSA signature" example
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
This example describes how to use the STM32 Cryptographic Library RSA algorithm 
to:
 1/ Generate RSA signature of a message digest using private key. 
 2/ Verify RSA signature validity of message digest using public key.

RSA routines can return RSA_SUCCESS in case of successful operation, SIGNATURE_VALID 
in case of vaidate signature or one of the following error codes in case of fail: 

  - RSA_ERR_BAD_PARAMETER, 
  - RSA_ERR_UNSUPPORTED_HASH, 
  - RSA_ERR_BAD_KEY, 
  - ERR_MEMORY_FAIL,
  - RSA_ERR_MODULUS_TOO_SHORT,
  - SIGNATURE_INVALID.

A comparison between the generated RSA signature of message and expected 
signature data is done to check that the generated signature has been correctly 
done.

The green LED will be toggled three times each 500 milliseconds before starting 
the RSA algorithms operations.    
In case of successful operations the green led will be turned on and in case of 
fail it will be toggled each 250 milliseconds in an infinity loop. 

@note RSA vectors examples for PKCS#1v1.5 are taken from:
Available at:
ftp://ftp.rsa.com/pub/rsalabs/tmp/pkcs1v15sign-vectors.txt

@par Directory contents 

  - RSA/RSA_Signature/Inc/STM32l0xx_hal_conf.h    HAL configuration file
  - RSA/RSA_Signature/Inc/STM32l0xx_it.h          Interrupt handlers header file
  - RSA/RSA_Signature/Inc/main.h                  Header for main.c module  
  - RSA/RSA_Signature/Src/STM32l0xx_it.c          Interrupt handlers
  - RSA/RSA_Signature/Src/main.c                  Main program
  - RSA/RSA_Signature/Src/system_stm32l0xx.c      STM32L0xx system source file


@par Hardware and Software environment

  - This example runs on STM32L053R8 devices.
    
  - This example has been tested with STM32L053R8-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */