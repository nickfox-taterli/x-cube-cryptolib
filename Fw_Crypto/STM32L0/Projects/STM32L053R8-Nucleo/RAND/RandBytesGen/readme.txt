/**
  @page RandBytesGen  Ramdom Number Generator example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    RAND/RandBytesGen/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "Random Number Generator" example.
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
  */
   @endverbatim

@par Example Description
This example describes how to use the STM32 Cryptographic Library Random number 
generator algorithm to generate an array filled with random bytes.

Random number generator routines can return RNG_SUCCESS in case of successful 
operation or one of the following error codes in case of fail: 
  - RNG_ERR_UNINIT_STATE, 
  - RNG_ERR_BAD_PARAMETER,
  - RNG_ERR_BAD_ENTROPY_SIZE
  - RNG_ERR_BAD_PERS_STRING_SIZE
  
User application needs to check on returned value to determine which action will 
be run in both fail and success cases.

The green LED will be toggled three times each 500 milliseconds before starting 
the RNG algorithms operations.    
In case of successful operations the green led will  be turned on and in case of
fail it will be toggled each 250 milliseconds in an infinity loop. 

@par Directory contents 

  - RAND/RandBytesGen/Inc/STM32l0xx_hal_conf.h    HAL configuration file
  - RAND/RandBytesGen/Inc/STM32l0xx_it.h          Interrupt handlers header file
  - RAND/RandBytesGen/Inc/main.h                  Header for main.c module  
  - RAND/RandBytesGen/Src/STM32l0xx_it.c          Interrupt handlers
  - RAND/RandBytesGen/Src/main.c                  Main program
  - RAND/RandBytesGen/Src/system_stm32l0xx.c      STM32L0xx system source file


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