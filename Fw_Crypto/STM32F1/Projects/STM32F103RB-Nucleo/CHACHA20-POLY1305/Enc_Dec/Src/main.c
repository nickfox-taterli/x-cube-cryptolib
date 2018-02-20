/**
******************************************************************************
* @file    CHACHA20-POLY1305/Enc_Dec/Src/main.c
* @author  MCD Application Team
* @version V3.1.0
* @date    30-October-2015
* @brief   Main program body
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
* You may not use this file except in compliance with the License.
* You may obtain a copy of the License at:
*
* http://www.st.com/software_license_agreement_liberty_v2
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


/** @addtogroup STM32_Crypto_Examples
* @{
*/

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

const uint8_t key[] =
  {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
  };

const uint8_t nonce[] =
  {
    0x07, 0x00, 0x00, 0x00, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
  };

const uint8_t input[] =
  {
    0x4c, 0x61, 0x64, 0x69, 0x65, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x47, 0x65, 0x6e, 0x74, 0x6c,
    0x65, 0x6d, 0x65, 0x6e, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x63, 0x6c, 0x61, 0x73,
    0x73, 0x20, 0x6f, 0x66, 0x20, 0x27, 0x39, 0x39, 0x3a, 0x20, 0x49, 0x66, 0x20, 0x49, 0x20, 0x63,
    0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6f, 0x66, 0x66, 0x65, 0x72, 0x20, 0x79, 0x6f, 0x75, 0x20, 0x6f,
    0x6e, 0x6c, 0x79, 0x20, 0x6f, 0x6e, 0x65, 0x20, 0x74, 0x69, 0x70, 0x20, 0x66, 0x6f, 0x72, 0x20,
    0x74, 0x68, 0x65, 0x20, 0x66, 0x75, 0x74, 0x75, 0x72, 0x65, 0x2c, 0x20, 0x73, 0x75, 0x6e, 0x73,
    0x63, 0x72, 0x65, 0x65, 0x6e, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x62, 0x65, 0x20, 0x69,
    0x74, 0x2e,
  };

const uint8_t aad[] =
  {
    0x50, 0x51, 0x52, 0x53, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
  };

uint8_t rfc_result[] =
  {
    0xd3, 0x1a, 0x8d, 0x34, 0x64, 0x8e, 0x60, 0xdb, 0x7b, 0x86, 0xaf, 0xbc, 0x53, 0xef, 0x7e, 0xc2,
    0xa4, 0xad, 0xed, 0x51, 0x29, 0x6e, 0x08, 0xfe, 0xa9, 0xe2, 0xb5, 0xa7, 0x36, 0xee, 0x62, 0xd6,
    0x3d, 0xbe, 0xa4, 0x5e, 0x8c, 0xa9, 0x67, 0x12, 0x82, 0xfa, 0xfb, 0x69, 0xda, 0x92, 0x72, 0x8b,
    0x1a, 0x71, 0xde, 0x0a, 0x9e, 0x06, 0x0b, 0x29, 0x05, 0xd6, 0xa5, 0xb6, 0x7e, 0xcd, 0x3b, 0x36,
    0x92, 0xdd, 0xbd, 0x7f, 0x2d, 0x77, 0x8b, 0x8c, 0x98, 0x03, 0xae, 0xe3, 0x28, 0x09, 0x1b, 0x58,
    0xfa, 0xb3, 0x24, 0xe4, 0xfa, 0xd6, 0x75, 0x94, 0x55, 0x85, 0x80, 0x8b, 0x48, 0x31, 0xd7, 0xbc,
    0x3f, 0xf4, 0xde, 0xf0, 0x8e, 0x4b, 0x7a, 0x9d, 0xe5, 0x76, 0xd2, 0x65, 0x86, 0xce, 0xc6, 0x4b,
    0x61, 0x16,
  };

const uint8_t rfc_tag[] =
  {
    0x1a, 0xe1, 0x0b, 0x59, 0x4f, 0x09, 0xe2, 0x6a, 0x7e, 0x90, 0x2e, 0xcb, 0xd0, 0x60, 0x06, 0x91,
  };
uint8_t outputBuffer[265];


/* Private function prototypes -----------------------------------------------*/
int32_t STM32_ChaChaPoly_Encrypt(const uint8_t *AAD,
                                 int32_t      AADSize,
                                 const uint8_t *InputMessage,
                                 int32_t      InputMessageSize,
                                 const uint8_t  *Key,
                                 const uint8_t  *Nonce,
                                 uint8_t     *Output);

int32_t STM32_ChaChaPoly_Decrypt(const uint8_t *AAD,
                                 int32_t      AADSize,
                                 const uint8_t *InputMessage,
                                 int32_t      InputMessageSize,
                                 const uint8_t  *Key,
                                 const uint8_t  *Nonce,
                                 uint8_t     *Output,
                                 const uint8_t  *Tag);

TestStatus Buffercmp(const uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength);

static void SystemClock_Config(void);
static void Led_Config(void);
static void Led_Toggle( __IO uint32_t toggle_delay);
static void Error_Handler(void);
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Main program
* @param  None
* @retval None
*/
int main()
{
  int32_t status = CHACHA20POLY1305_SUCCESS; /* Status */


  /* STM32F1xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
     
  HAL_Init();

  /* Configure the system clock to 64 MHz */
  SystemClock_Config();

  /* Configure the green led */
  Led_Config();

  /* Toggle the green led before starting the algorithm */
  Led_Toggle(500);

  /* Enable CRC clock */
  __CRC_CLK_ENABLE();

  status = STM32_ChaChaPoly_Encrypt(aad, sizeof(aad), input, sizeof(input), key, nonce, outputBuffer);

  if (status == CHACHA20POLY1305_SUCCESS)
  {
    /* Function returned SUCCESS */
    /* Checking Encrypted text with expected value */
    if (Buffercmp(rfc_result, outputBuffer, sizeof(rfc_result)) == PASSED)
    {
      /* add application traitment in case of CHACHA20-POLY1305 success */
    }
    else
    {
      Error_Handler();
    }
    /* Checking TAG with expected value */
    if (Buffercmp(rfc_tag, outputBuffer + sizeof(rfc_result), sizeof(rfc_tag)) == PASSED)
    {
      /* add application traitment in case of CHACHA20-POLY1305 success */
    }
    else
    {
      Error_Handler();
    }
  }
  else
  {
    Error_Handler();

  }


  status = STM32_ChaChaPoly_Decrypt(aad, sizeof(aad), rfc_result, sizeof(rfc_result), key, nonce, outputBuffer, rfc_tag);

  if (status == AUTHENTICATION_SUCCESSFUL)
  {

    /* Function returned AUTHENTICATION_SUCCESSFUL */
    /* Checking Decrypted text with expected value */
    if (Buffercmp(input, outputBuffer, sizeof(input)) == PASSED)

    {
      /* add application traitment in case of CHACHA20-POLY1305 success */
    }
    else
    {
      Error_Handler();

    }
  }
  else
  {
    Error_Handler();
  }

  /* Turn on the green led in case of ARC4 operations are successful*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}


}

/**
* @brief  ChaCha20-Poly1305 AEAD Encryption
* @param  AAD: Pointer to Additional Authenticated Data
* @param  AADSize: size of AAD
* @param  InputMessage: pointer to input message
* @param  InputMessageSize: size of input message
* @param  Key: pointer to the 256-bit key
* @param  Nonce: pointer to the 96-bit Nonce
* @param  Output: pointer to output buffer, the tag will be concatenated to the encrypted text
* @retval error status: can be CHACHA20POLY1305_SUCCESS if success or one of
*                     CHACHA20POLY1305_ERR_BAD_PARAMETER,CHACHA20POLY1305_ERR_BAD_OPERATION if error occured.
*/
int32_t STM32_ChaChaPoly_Encrypt(const uint8_t *AAD,
                                 int32_t      AADSize,
                                 const uint8_t *InputMessage,
                                 int32_t      InputMessageSize,
                                 const uint8_t  *Key,
                                 const uint8_t  *Nonce,
                                 uint8_t     *Output)
{
  /* ChaCha20Poly1305, error status and output length */
  ChaCha20Poly1305ctx_stt ctx;
  /* Default value for error status */
  uint32_t error_status = CHACHA20POLY1305_SUCCESS;
  /* Integer to store size of written data */
  int32_t outputLength = 0;

  /* Set flag field to default value */
  ctx.mFlags = E_SK_DEFAULT;

  /* Call the Init */
  error_status = ChaCha20Poly1305_Encrypt_Init(&ctx, Key, Nonce);
  if (error_status == CHACHA20POLY1305_SUCCESS)
  {
    /* Process the AAD */
    error_status = ChaCha20Poly1305_Header_Append(&ctx, AAD, AADSize);
    if (error_status == CHACHA20POLY1305_SUCCESS)
    {
      /* Encrypt Message */
      error_status = ChaCha20Poly1305_Encrypt_Append(&ctx, InputMessage, InputMessageSize, Output, &outputLength);
      if (error_status == CHACHA20POLY1305_SUCCESS)
      {
        /* Generate authentication tag */
        error_status = ChaCha20Poly1305_Encrypt_Finish(&ctx, Output + outputLength, &outputLength);
      }
    }
  }

  return error_status;
}

/**
* @brief  ChaCha20-Poly1305 AEAD Decryption and Authentication
* @param  AAD: Pointer to Additional Authenticated Data
* @param  AADSize: size of AAD
* @param  InputMessage: pointer to input message
* @param  InputMessageSize: size of input message
* @param  Key: pointer to the 256-bit key
* @param  Nonce: pointer to the 96-bit Nonce
* @param  Output: pointer to output buffer
* @param  Tag: pointer to input Tag to be verified
* @retval error status: AUTHENTICATION_SUCCESSFUL if success or one of
*                     CHACHA20POLY1305_ERR_BAD_PARAMETER,CHACHA20POLY1305_ERR_BAD_OPERATION
*                     CHACHA20POLY1305_ERR_BAD_CONTEXT, AUTHENTICATION_FAILED if error occured.
*/
int32_t STM32_ChaChaPoly_Decrypt(const uint8_t *AAD,
                                 int32_t      AADSize,
                                 const uint8_t *InputMessage,
                                 int32_t      InputMessageSize,
                                 const uint8_t  *Key,
                                 const uint8_t  *Nonce,
                                 uint8_t     *Output,
                                 const uint8_t  *Tag)
{
  /* ChaCha20Poly1305, error status and output length */
  ChaCha20Poly1305ctx_stt ctx;
  /* Default value for error status */
  uint32_t error_status = AUTHENTICATION_FAILED;
  /* Integer to store size of written data */
  int32_t outputLength = 0;

  /* Set flag field to default value */
  ctx.mFlags = E_SK_DEFAULT;
  /* Set the tag that will be verified */
  ctx.pmTag = Tag;

  /* Call the Init */
  error_status = ChaCha20Poly1305_Decrypt_Init(&ctx, Key, Nonce);
  if (error_status == CHACHA20POLY1305_SUCCESS)
  {
    /* Process the AAD */
    error_status = ChaCha20Poly1305_Header_Append(&ctx, AAD, AADSize);
    if (error_status == CHACHA20POLY1305_SUCCESS)
    {
      /* Decrypt Message */
      error_status = ChaCha20Poly1305_Decrypt_Append(&ctx, InputMessage, InputMessageSize, Output, &outputLength);
      if (error_status == CHACHA20POLY1305_SUCCESS)
      {
        /* Verify authentication tag */
        error_status = ChaCha20Poly1305_Decrypt_Finish(&ctx, NULL, 0);
      }
    }
  }

  return error_status;
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
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLLMUL                         = 16
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Configure PLL ------------------------------------------------------*/
  /* PLL configuration: PLLCLK = (HSI / 2) * PLLMUL = (8 / 2) * 16 = 64 MHz */
  /* PREDIV1 configuration: PREDIV1CLK = PLLCLK / HSEPredivValue = 64 / 1 = 64 MHz */
  /* Enable HSI and activate PLL with HSi_DIV2 as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
  oscinitstruct.HSEState        = RCC_HSE_OFF;
  oscinitstruct.LSEState        = RCC_LSE_OFF;
  oscinitstruct.HSIState        = RCC_HSI_ON;
  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  oscinitstruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSI_DIV2;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
}



/**
  * @brief  Configures the green led.
  * @param  None
  * @retval None
  */
static void Led_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
    /* -1- Enable each GPIO Clock (to be able to program the configuration registers) */
  LED2_GPIO_CLK_ENABLE();

  /* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pin = LED2_PIN;
  HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
  
}

/**
  * @brief  Toggles the green Led.
  * @param  None
  * @retval None
  */
static void Led_Toggle( __IO uint32_t toggle_delay)
{
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);      
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
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
  {
    HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
    HAL_Delay(250);
    HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
    HAL_Delay(250);
  }
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


/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/
