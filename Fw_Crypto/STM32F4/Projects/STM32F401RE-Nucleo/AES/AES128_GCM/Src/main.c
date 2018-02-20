/**
  ******************************************************************************
  * @file    AES/AES128_GCM/Src/main.c
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
/* Size of GCM Tag, fixed */
#define GCM_TAG_SIZE          16
/* length of plain and cipher text test vector of example  */
#define PLAIN_CIPHER_TEXT_LENGTH 60

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* key */
const uint8_t key [CRL_AES128_KEY] =
  {
    0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c, 0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08
  };
/*  IV */
const uint8_t IV [] =
  {
    0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad, 0xde, 0xca, 0xf8, 0x88
  };
/* header */
const uint8_t header[] =
  {
    0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
    0xab, 0xad, 0xda, 0xd2
  };
/* Expected tag */
const uint8_t expectedTag[GCM_TAG_SIZE] =
  {
    0x5b, 0xc9, 0x4f, 0xbc, 0x32, 0x21, 0xa5, 0xdb, 0x94, 0xfa, 0xe9, 0x5a, 0xe7, 0x12, 0x1a, 0x47
  };
/* Plaintext */
const uint8_t Plaintext[] =
  {
    0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5, 0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
    0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda, 0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
    0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53, 0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
    0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57, 0xba, 0x63, 0x7b, 0x39
  };
/* In encryption we expect this vector as result */
const uint8_t expectedCipherText[PLAIN_CIPHER_TEXT_LENGTH] =
  {
    0x42, 0x83, 0x1e, 0xc2, 0x21, 0x77, 0x74, 0x24, 0x4b, 0x72, 0x21, 0xb7, 0x84, 0xd0, 0xd4, 0x9c,
    0xe3, 0xaa, 0x21, 0x2f, 0x2c, 0x02, 0xa4, 0xe0, 0x35, 0xc1, 0x7e, 0x23, 0x29, 0xac, 0xa1, 0x2e,
    0x21, 0xd5, 0x14, 0xb2, 0x54, 0x66, 0x93, 0x1c, 0x7d, 0x8f, 0x6a, 0x5a, 0xac, 0x84, 0xaa, 0x05,
    0x1b, 0xa3, 0x0b, 0x39, 0x6a, 0x0a, 0xac, 0x97, 0x3d, 0x58, 0xe0, 0x91
  };

uint8_t Outputmessage [64];
uint8_t tag[GCM_TAG_SIZE];


/* Private function prototypes -----------------------------------------------*/

int32_t STM32_AES_GCM_Encrypt(const uint8_t *InputMessage,
                              uint32_t   InputMessageLength,
                              const uint8_t *AES_Key,
                              uint32_t   KeyLength,
                              const uint8_t *IV,
                              uint32_t   IVSize,
                              const uint8_t *Header,
                              uint32_t   HeaderSize,
                              uint8_t   *Tag,
                              uint32_t   TagSize,
                              uint8_t   *OutputMessage);

int32_t STM32_AES_GCM_Decrypt(const uint8_t *InputMessage,
                              uint32_t   InputMessageLength,
                              const uint8_t *AES_Key,
                              uint32_t   KeyLength,
                              const uint8_t *IV,
                              uint32_t   IVSize,
                              const uint8_t *Tag,
                              uint32_t   TagSize,
                              const uint8_t *Header,
                              uint32_t   HeaderSize,
                              uint8_t   *OutputMessage);

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

  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();

  /* Configure the system clock to 84 MHz */
  SystemClock_Config();

  /* Configure the green led */
  Led_Config();

  /* Toggle the green led before starting the algorithm */
  Led_Toggle(500);

  /* Enable CRC clock */
  __CRC_CLK_ENABLE();

  /* Encrypt data */
  status = STM32_AES_GCM_Encrypt(
             Plaintext, PLAIN_CIPHER_TEXT_LENGTH,
             key, CRL_AES128_KEY,
             IV, sizeof(IV),
             header, sizeof(header),
             tag, GCM_TAG_SIZE,
             Outputmessage);
  if (status ==  AES_SUCCESS)
  {
    if (Buffercmp(expectedCipherText, Outputmessage, PLAIN_CIPHER_TEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of AES GCM encryption is passed */

    }
    else
    {

      Error_Handler();

    }

    if (Buffercmp(expectedTag, tag, GCM_TAG_SIZE) == PASSED)
    {
      /* add application traitment in case of AES GCM encryption is passed */

    }
    else
    {

      Error_Handler();

    }
  }
  else
  {
    /* In case of encryption not success the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
     */

    Error_Handler();

  }





  /* Decrypt data */
  status = STM32_AES_GCM_Decrypt(
             expectedCipherText, PLAIN_CIPHER_TEXT_LENGTH,
             key, CRL_AES128_KEY,
             IV, sizeof(IV),
             tag, GCM_TAG_SIZE,
             header, sizeof(header),
             Outputmessage);


  if (status == AUTHENTICATION_SUCCESSFUL)
  {

    if (Buffercmp(Plaintext, Outputmessage, PLAIN_CIPHER_TEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of AES GCM encryption is passed */

    }
    else
    {


      Error_Handler();

    }
  }
  else
  {
    /* In case of AES GCM authentication is failed the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION, 
     * AUTHENTICATION_FAILED */

    Error_Handler();

  }

  /* Turn on the green led in case of AES GCM operations are succssfuls*/
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  while (1)
  {}


}

/**
  * @brief  AES GCM Encryption
  * @param  InputMessage: payload to encrypt
  * @param  InputMessageLength: length of payload
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  IV: Initialization Vector
  * @param  IVSize: length of IV
  * @param  Header: message header
  * @param  HeaderSize: length of message header
  * @param  Tag: generated tag
  * @param  TagSize: length of generated tag
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_AES_GCM_Encrypt(const uint8_t *InputMessage,
                              uint32_t   InputMessageLength,
                              const uint8_t *AES_Key,
                              uint32_t   KeyLength,
                              const uint8_t *IV,
                              uint32_t   IVSize,
                              const uint8_t *Header,
                              uint32_t   HeaderSize,
                              uint8_t   *Tag,
                              uint32_t   TagSize,
                              uint8_t   *OutputMessage)
{
  /* AES context, error status and output length */
  AESGCMctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;
  /* Set the key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the IV size in AES status */
  AESctx.mIvSize = IVSize;
  /* Set the tag size in AES status */
  AESctx.mTagSize = TagSize;
  /* Initialize the operation, by passing key and IV */
  error_status = AES_GCM_Encrypt_Init(&AESctx, AES_Key, IV);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Process Header (data to be authenticated but NOT encrypted) */
    error_status = AES_GCM_Header_Append(&AESctx, Header, HeaderSize);

    if (error_status == AES_SUCCESS)
    {
      /* Encrypt Data */
      error_status = AES_GCM_Encrypt_Append(&AESctx, InputMessage,
                                            InputMessageLength, OutputMessage, &outputLength);

      /* check for encryption errors */
      if (error_status == AES_SUCCESS)
      {
        /* Finalize data and write associated tag */
        error_status = AES_GCM_Encrypt_Finish(&AESctx,
                                              Tag, &outputLength);
      }
    }
  }

  return error_status;
}


/**
  * @brief  AES GCM Decryption
  * @param  InputMessage: pointer to input message to be decrypted
  * @param  InputMessageLength: input data message length in byte
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  IV: Initialization Vector
  * @param  Tag: tag for authenticate header and payload
  * @param  TagSize: size of tag
  * @param  Header: plain header
  * @param  HeaderSize: size of header
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER, AUTHENTICATION_FAILED if error occured.
  */
int32_t STM32_AES_GCM_Decrypt(const uint8_t *InputMessage,
                              uint32_t   InputMessageLength,
                              const uint8_t *AES_Key,
                              uint32_t   KeyLength,
                              const uint8_t *IV,
                              uint32_t   IVSize,
                              const uint8_t *Tag,
                              uint32_t   TagSize,
                              const uint8_t *Header,
                              uint32_t   HeaderSize,
                              uint8_t   *OutputMessage)
{
  /* AES context, error status and output length */
  AESGCMctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;
  /* Set the key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the IV size in AES status */
  AESctx.mIvSize = IVSize;
  /* Set the tag size in AES status */
  AESctx.mTagSize = TagSize;
  /* Set the tag in AES status */
  AESctx.pmTag = Tag;

  /* Initialize the operation, by passing the key and IV */
  error_status = AES_GCM_Decrypt_Init(&AESctx, AES_Key, IV);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Process header */
    error_status = AES_GCM_Header_Append(&AESctx, Header, HeaderSize);

    if (error_status == AES_SUCCESS)
    {
      /* Decrypt Data */
      error_status = AES_GCM_Decrypt_Append(&AESctx, InputMessage,
                                            InputMessageLength, OutputMessage, &outputLength);

      /* Authenticate */
      if (error_status == AES_SUCCESS)
      {
        /* Finalize data */
        error_status = AES_GCM_Decrypt_Finish(&AESctx, NULL, &outputLength);
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
  *            SYSCLK(Hz)                     = 84000000
  *            HCLK(Hz)                       = 84000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16
  *            PLL_N                          = 336
  *            PLL_P                          = 4
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale2 mode
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /* Enable HSI Oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/**
  * @brief  Toggles the green led three times.
  * @param[in]  toggle_delay : toggle frequency
  * @retval None
  */
static void Led_Toggle( __IO uint32_t toggle_delay)
{
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  HAL_Delay(toggle_delay);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  HAL_Delay(toggle_delay);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  HAL_Delay(toggle_delay);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  HAL_Delay(toggle_delay);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  HAL_Delay(toggle_delay);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
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
  while (1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(250);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
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
/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
