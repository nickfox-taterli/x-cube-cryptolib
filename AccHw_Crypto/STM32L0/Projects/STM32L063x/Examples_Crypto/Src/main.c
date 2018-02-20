/**
  ******************************************************************************
  * @file    Examples_Crypto/Src/main.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup Examples_Crypto
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Example_Status = 0;

/* Private function prototypes -----------------------------------------------*/
TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{

  /* STM32L0xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
       - Low Level Initialization
     */

  HAL_Init();

  /* Configure the system clock to 64 MHz */
  SystemClock_Config();

  /* Enable CRC clock */
  __CRC_CLK_ENABLE();



#ifdef Example_AES128bitsCFB
  Example_Status = ExampleAES128bitsCFB();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of AES CFB encryption and decryption is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_AES128bitsCCM
  Example_Status = ExampleAES128bitsCCM();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of AES CCM encryption and decryption is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_AES128bitsOFB
  Example_Status = ExampleAES128bitsOFB();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of AES OFB encryption and decryption is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_AES128bitsCMAC
  Example_Status = ExampleAES128bitsCMAC();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of AES CMAC encryption and decryption is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_AES128bitsGCM
  Example_Status = ExampleAES128bitsGCM();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of AES GCM encryption and decryption is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_AES128bitsKEYWRAP
  Example_Status = ExampleAES128bitsKEYWRAP();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of AES KEYWRAP encryption and decryption is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_AES256bitsXTS
  Example_Status = ExampleAES256bitsXTS();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of AES XTS encryption and decryption is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_POLY1305GetMACVerifMAC
  Example_Status = ExamplePOLY1305GetMACVerifMAC();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of POLY1305 get and verify MAC is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_ECCKeyGenSignVerif
  Example_Status = ExampleECCKeyGenSignVerif();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of ECC key generation, signature and verification is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_ECCSignVerif
  Example_Status = ExampleECCSignVerif();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of ECC signature and verification encryption is passed */
  }
  else
  {
    Error_Handler();
  }
#endif

#ifdef Example_RSAEncDec
  Example_Status = ExampleRSAEncDec();
  if (Example_Status == PASSED)
  {
    /* User may add application traitment in case of RSA encryption and decryption encryption is passed */
  }
  else
  {
    Error_Handler();
  }
#endif


  /* Infinite loop */
  while (1)
  {}
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer, pBuffer1: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer identical to pBuffer1
  *         FAILED: pBuffer differs from pBuffer1
  */
TestStatus Buffercmp(const uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer != *pBuffer1)
    {
      return FAILED;
    }

    pBuffer++;
    pBuffer1++;
  }

  return PASSED;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = MSI
  *            SYSCLK(Hz)                     = 2000000
  *            HCLK(Hz)                       = 2000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            Flash Latency(WS)              = 0
  *            Main regulator output voltage  = Scale3 mode
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

  /* Enable Power Control clock */
  __PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /* Enable HSI48 Oscillator for RNG analog part */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while (1)
  {}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
