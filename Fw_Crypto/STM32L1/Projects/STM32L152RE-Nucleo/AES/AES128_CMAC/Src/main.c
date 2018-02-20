/**
  ******************************************************************************
  * @file    AES/AES128_CMAC/Src/main.c
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
#define PLAINTEXT_LENGTH 16
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t Plaintext [PLAINTEXT_LENGTH] =
  {
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
  };

/* Key to be used for AES encryption/decryption */
const uint8_t key[CRL_AES128_KEY] =
  {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
  };

/* In encryption we expect this vector as result */
const uint8_t expectedTags[CRL_AES_BLOCK] =
  {
    0x07, 0x0a, 0x16, 0xb4, 0x6b, 0x4d, 0x41, 0x44,
    0xf7, 0x9b, 0xdd, 0x9d, 0xd0, 0x4a, 0x28, 0x7c
  };

uint8_t OutputMessage[CRL_AES_BLOCK];


/* Private function prototypes -----------------------------------------------*/


int32_t STM32_AES_CMAC_Encrypt(const uint8_t *InputMessage,
                               uint32_t   InputMessageLength,
                               const uint8_t *AES_Key,
                               uint32_t   KeyLength,
                               uint32_t   TagSize,
                               uint8_t   *OutputTag);

int32_t STM32_AES_CMAC_Decrypt(const uint8_t *InputMessage,
                               uint32_t   InputMessageLength,
                               const uint8_t *AES_Key,
                               uint32_t   KeyLength,
                               const uint8_t *tag,
                               uint32_t   TagSize);

TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);

static void SystemClock_Config(void);
static void Led_Config(void);
static void Led_Toggle( __IO uint32_t toggle_delay);
static void Error_Handler(void);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{

  int32_t status = AES_SUCCESS;


  /* STM32L1xx HAL library initialization:
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

  /* Encrypt DATA with AES in CMAC mode */
  status = STM32_AES_CMAC_Encrypt(Plaintext, PLAINTEXT_LENGTH, key, CRL_AES128_KEY, CRL_AES_BLOCK, OutputMessage);

  if (status == AES_SUCCESS)
  {
    if (Buffercmp(expectedTags, OutputMessage, CRL_AES_BLOCK) == PASSED)
    {
      /* add application traitment in case of AES CMAC encryption is passed */
    }
    else
    {

      Error_Handler();

    }

  }

  else
  {
    /* In case of encryption/decryption not success the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION, AES_ERR_BAD_INPUT_SIZE
     */

    Error_Handler();

  }

  /* Decrypt DATA with AES in CMAC mode */
  status = STM32_AES_CMAC_Decrypt(Plaintext, PLAINTEXT_LENGTH, key, CRL_AES128_KEY, OutputMessage, CRL_AES_BLOCK);
  if (status == AUTHENTICATION_SUCCESSFUL)
  {
    /* Add application traitment in case of AES CMAC authentication is successful */
  }
  else
  {
    /* In case of AES CMAC authentication is failed possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION, AES_ERR_BAD_INPUT_SIZE,
     * AUTHENTICATION_FAILED
     */

    Error_Handler();

  }



  /* Turn on the green led in case of AES CMAC operations are successful*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}


}

/**
  * @brief  AES CMAC Encryption
  * @param  InputMessage: pointer to input message to be encrypted
  * @param  InputMessageLength: input data message length in byte
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  TagSize: length of generated tag
  * @param  OutputTag: generated tag
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_AES_CMAC_Encrypt(const uint8_t *InputMessage,
                               uint32_t   InputMessageLength,
                               const uint8_t *AES_Key,
                               uint32_t   KeyLength,
                               uint32_t   TagSize,
                               uint8_t   *OutputTag)
{
  /* AES context, error status and output length */
  AESCMACctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;
  AESctx.mFlags |= E_SK_FINAL_APPEND;

  /* Set the key */
  AESctx.pmKey = AES_Key;
  /* Set the key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the size of generated tag */
  AESctx.mTagSize = TagSize;
  /* Initialize the operation, by passing the context */
  error_status = AES_CMAC_Encrypt_Init(&AESctx);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Encrypt Data in CMAC mode */
    error_status = AES_CMAC_Encrypt_Append(&AESctx, InputMessage,
                                           InputMessageLength);

    /* check for encryption errors in CMAC mode */
    if (error_status == AES_SUCCESS)
    {
      /* Finalize data */
      error_status = AES_CMAC_Encrypt_Finish(&AESctx, OutputTag,
                                             &outputLength);
    }
  }

  return error_status;
}


/**
  * @brief  AES CMAC Decryption
  * @param  InputMessage: pointer to input message to be decrypted
  * @param  InputMessageLength: input data message length in byte
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  tag: associated input message tag
  * @param  TagSize: length of tag
  * @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER, AES_ERR_BAD_INPUT_SIZE, AUTHENTICATION_FAILED if error occured.
  */
int32_t STM32_AES_CMAC_Decrypt(const uint8_t *InputMessage,
                               uint32_t   InputMessageLength,
                               const uint8_t *AES_Key,
                               uint32_t   KeyLength,
                               const uint8_t *tag,
                               uint32_t   TagSize)
{
  /* AES context, error status and output length */
  AESCMACctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;
  AESctx.mFlags |= E_SK_FINAL_APPEND;
  /* Set the key */
  AESctx.pmKey = AES_Key;
  /* Set key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the verification tag */
  AESctx.pmTag = tag;
  /* Set the size of generated tag */
  AESctx.mTagSize = TagSize;
  /* Initialize the operation */
  error_status = AES_CMAC_Decrypt_Init(&AESctx);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Decrypt Data in CMAC mode */
    error_status = AES_CMAC_Decrypt_Append(&AESctx, InputMessage,
                                           InputMessageLength);

    /* check for decryption errors in CMAC mode */
    if (error_status == AES_SUCCESS)
    {
      /* Finalize data */
      error_status = AES_CMAC_Decrypt_Finish(&AESctx, NULL,
                                             &outputLength);
    }
  }

  return error_status;
}

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
  *            SYSCLK(Hz)                     = 32000000
  *            HCLK(Hz)                       = 32000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLLMUL                         = 6
  *            PLLDIV                         = 3
  *            Flash Latency(WS)              = 1
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable HSE Oscillator and Activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV          = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Set Voltage scale1 as MCU will run at 32MHz */
  __PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
  while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOS) != RESET) {};

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
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
