/**
  ******************************************************************************
  * @file    TDES_DES/TDES_ECB/main.c
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

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#define PLAINTEXT_LENGTH 24
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t Plaintext[PLAINTEXT_LENGTH] =
  {
    0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x66, 0x63, 0x6B, 0x20, 0x62, 0x72, 0x6F,
    0x77, 0x6E, 0x20, 0x66, 0x6F, 0x78, 0x20, 0x6A, 0x75, 0x6D, 0x70
  };

/* Key to be used for AES encryption/decryption */
uint8_t Key[CRL_TDES_KEY] =
  {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x23, 0x45, 0x67, 0x89, 0xAB,
    0xCD, 0xEF, 0x01, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23
  };

/* Buffer to store the output data */
uint8_t OutputMessage[PLAINTEXT_LENGTH];

/* Size of the output data */
uint32_t OutputMessageLength = 0;

const uint8_t Expected_Ciphertext[PLAINTEXT_LENGTH] =
  {
    0xA8, 0x26, 0xFD, 0x8C, 0xE5, 0x3B, 0x85, 0x5F, 0xCC, 0xE2, 0x1C, 0x81, 0x12,
    0x25, 0x6F, 0xE6, 0x68, 0xD5, 0xC0, 0x5D, 0xD9, 0xB6, 0xB9, 0x00
  };

static GPIO_InitTypeDef  GPIO_InitStruct;

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_TDES_ECB_Encrypt(uint8_t* InputMessage,
                         uint32_t InputMessageLength,
                         uint8_t  *TDES_Key,
                         uint8_t  *OutputMessage,
                         uint32_t *OutputMessageLength);

int32_t STM32_TDES_ECB_Decrypt(uint8_t* InputMessage,
                         uint32_t InputMessageLength,
                         uint8_t *TDES_Key,
                         uint8_t  *OutputMessage,
                         uint32_t *OutputMessageLength);

TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);
                     
static void SystemClock_Config(void);
static void Led_Config(void);
static void Led_Toggle(uint32_t toggle_delay);
static void Error_Handler(void);                     
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  int32_t status = TDES_SUCCESS;


  /* STM32F2xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
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

  /* Encrypt DATA with TDES in ECB mode */
  status = STM32_TDES_ECB_Encrypt( (uint8_t *) Plaintext, PLAINTEXT_LENGTH, Key, OutputMessage,
                             &OutputMessageLength);
  if (status == TDES_SUCCESS)
  {
    if (Buffercmp(Expected_Ciphertext, OutputMessage, PLAINTEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of TDES ECB encryption is passed */
    
    }
    else
    {
     

      Error_Handler();

    }
  }
  else
  {
    /* In case of encryption/decryption not success possible values of status:
       * TDES_ERR_BAD_INPUT_SIZE, TDES_ERR_BAD_OPERATION, TDES_ERR_BAD_CONTEXT, TDES_ERR_BAD_PARAMETER
       */
       

      Error_Handler();
  }

  /* Decrypt DATA with TDES in ECB mode */
  status = STM32_TDES_ECB_Decrypt( (uint8_t *) OutputMessage, OutputMessageLength, Key, OutputMessage,
                             &OutputMessageLength);
  if (status == TDES_SUCCESS)
  {
    if (Buffercmp(Plaintext, OutputMessage, PLAINTEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of TDES ECB decrption is passed */
     
    }
    else
    {
     

      Error_Handler();

    }
  }
  else
  {
    /* In case of encryption/decryption not success possible values of status:
       * TDES_ERR_BAD_INPUT_SIZE, TDES_ERR_BAD_OPERATION, TDES_ERR_BAD_CONTEXT, TDES_ERR_BAD_PARAMETER
       */
       
      Error_Handler();
  }

  /* Turn on the green led in case of TDES ECB operations are successful*/
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
	while (1)
	{
	}
}

/**
  * @brief  TDES ECB Encryption example.
  * @param  InputMessage: pointer to input message to be encrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  TDES_Key: pointer to the TDES key to be used in the operation
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @retval error status: can be TDES_SUCCESS if success or one of
  *         TDES_ERR_BAD_INPUT_SIZE, TDES_ERR_BAD_OPERATION, TDES_ERR_BAD_PARAMETER
  *         if error occured.
  */
int32_t STM32_TDES_ECB_Encrypt(uint8_t* InputMessage,
                         uint32_t InputMessageLength,
                         uint8_t  *TDES_Key,
                         uint8_t  *OutputMessage,
                         uint32_t *OutputMessageLength)
{
  TDESECBctx_stt TDESctx;

  uint32_t error_status = TDES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  TDESctx.mFlags = E_SK_DEFAULT;

  /* Initialize the operation, by passing the key.
   * Third parameter is NULL because ECB doesn't use any IV */
  error_status = TDES_ECB_Encrypt_Init(&TDESctx, TDES_Key, NULL );

  /* check for initialization errors */
  if (error_status == TDES_SUCCESS)
  {
    /* Encrypt Data */
    error_status = TDES_ECB_Encrypt_Append(&TDESctx,
                                           InputMessage,
                                           InputMessageLength,
                                           OutputMessage,
                                           &outputLength);

    if (error_status == TDES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = TDES_ECB_Encrypt_Finish(&TDESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}


/**
  * @brief  TDES ECB Decryption example.
  * @param  InputMessage: pointer to input message to be decrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  TDES_Key: pointer to the TDES key to be used in the operation
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @param  OutputMessageLength: pointer to decrypted message length.
  * @retval error status: can be TDES_SUCCESS if success or one of
  *         TDES_ERR_BAD_INPUT_SIZE, TDES_ERR_BAD_OPERATION, TDES_ERR_BAD_PARAMETER
  *         if error occured.
  */
int32_t STM32_TDES_ECB_Decrypt(uint8_t* InputMessage,
                         uint32_t InputMessageLength,
                         uint8_t  *TDES_Key,
                         uint8_t  *OutputMessage,
                         uint32_t *OutputMessageLength)
{
  TDESECBctx_stt TDESctx;

  uint32_t error_status = TDES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  TDESctx.mFlags = E_SK_DEFAULT;

  /* Initialize the operation, by passing the key.
   * Third parameter is NULL because ECB doesn't use any IV */
  error_status = TDES_ECB_Decrypt_Init(&TDESctx, TDES_Key, NULL );

  /* check for initialization errors */
  if (error_status == TDES_SUCCESS)
  {
    /* Decrypt Data */
    error_status = TDES_ECB_Decrypt_Append(&TDESctx,
                                           InputMessage,
                                           InputMessageLength,
                                           OutputMessage,
                                           &outputLength);

    if (error_status == TDES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = TDES_ECB_Decrypt_Finish(&TDESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
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
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 120000000
  *            HCLK(Hz)                       = 120000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 240
  *            PLL_P                          = 2
  *            PLL_Q                          = 5
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3);
}

/**
  * @brief  Configures the green led.
  * @param  None
  * @retval None
  */
static void Led_Config(void)
{
    /* -1- Enable each GPIO Clock (to be able to program the configuration registers) */
  __GPIOG_CLK_ENABLE();

  /* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct); 
  
}

/**
  * @brief  Toggles the green led three times.
  * @param[in]  toggle_delay : toggle frequency
  * @retval None
  */
static void Led_Toggle(uint32_t toggle_delay)
{
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);      
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  Led_Toggle(250);
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
  {
  }
}
#endif


/**
  * @}
  */


/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/

