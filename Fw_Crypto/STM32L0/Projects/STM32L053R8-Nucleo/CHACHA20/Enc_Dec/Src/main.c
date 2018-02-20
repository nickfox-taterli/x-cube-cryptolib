/**
  ******************************************************************************
  * @file    CHACHA20/Enc_Dec/Src/main.c
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
#define PLAINTEXT_LENGTH 128
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Key to be used for encryption/decryption */
const uint8_t Key[CRL_CHACHA256_KEY] =
  {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
    0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00
  };


/* Initialization Vector */
const uint8_t IV[CRL_CHACHA_NONCE] =
  {
    0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78
  };

/* Test Vectors have zero input, we need to replicate */
uint8_t Plaintext[PLAINTEXT_LENGTH] =
  {
    0,
  };

/* Buffer to store the output data */
uint8_t OutputMessage[PLAINTEXT_LENGTH];

/* Size of the output data */
uint32_t OutputMessageLength = 0;

const uint8_t Expected_Encryption_Result[PLAINTEXT_LENGTH] =
  {
    0xd1, 0xab, 0xf6, 0x30, 0x46, 0x7e, 0xb4, 0xf6,
    0x7f, 0x1c, 0xfb, 0x47, 0xcd, 0x62, 0x6a, 0xae,
    0x8a, 0xfe, 0xdb, 0xbe, 0x4f, 0xf8, 0xfc, 0x5f,
    0xe9, 0xcf, 0xae, 0x30, 0x7e, 0x74, 0xed, 0x45,
    0x1f, 0x14, 0x04, 0x42, 0x5a, 0xd2, 0xb5, 0x45,
    0x69, 0xd5, 0xf1, 0x81, 0x48, 0x93, 0x99, 0x71,
    0xab, 0xb8, 0xfa, 0xfc, 0x88, 0xce, 0x4a, 0xc7,
    0xfe, 0x1c, 0x3d, 0x1f, 0x7a, 0x1e, 0xb7, 0xca,
    0xe7, 0x6c, 0xa8, 0x7b, 0x61, 0xa9, 0x71, 0x35,
    0x41, 0x49, 0x77, 0x60, 0xdd, 0x9a, 0xe0, 0x59,
    0x35, 0x0c, 0xad, 0x0d, 0xce, 0xdf, 0xaa, 0x80,
    0xa8, 0x83, 0x11, 0x9a, 0x1a, 0x6f, 0x98, 0x7f,
    0xd1, 0xce, 0x91, 0xfd, 0x8e, 0xe0, 0x82, 0x80,
    0x34, 0xb4, 0x11, 0x20, 0x0a, 0x97, 0x45, 0xa2,
    0x85, 0x55, 0x44, 0x75, 0xd1, 0x2a, 0xfc, 0x04,
    0x88, 0x7f, 0xef, 0x35, 0x16, 0xd1, 0x2a, 0x2c
  };
const uint8_t Expected_Decryption_Result[PLAINTEXT_LENGTH] =
  {
    0x9f, 0xad, 0xf4, 0x09, 0xc0, 0x08, 0x11, 0xd0,
    0x04, 0x31, 0xd6, 0x7e, 0xfb, 0xd8, 0x8f, 0xba,
    0x59, 0x21, 0x8d, 0x5d, 0x67, 0x08, 0xb1, 0xd6,
    0x85, 0x86, 0x3f, 0xab, 0xbb, 0x0e, 0x96, 0x1e,
    0xea, 0x48, 0x0f, 0xd6, 0xfb, 0x53, 0x2b, 0xfd,
    0x49, 0x4b, 0x21, 0x51, 0x01, 0x50, 0x57, 0x42,
    0x3a, 0xb6, 0x0a, 0x63, 0xfe, 0x4f, 0x55, 0xf7,
    0xa2, 0x12, 0xe2, 0x16, 0x7c, 0xca, 0xb9, 0x31,
    0xfb, 0xfd, 0x29, 0xcf, 0x7b, 0xc1, 0xd2, 0x79,
    0xed, 0xdf, 0x25, 0xdd, 0x31, 0x6b, 0xb8, 0x84,
    0x3d, 0x6e, 0xde, 0xe0, 0xbd, 0x1e, 0xf1, 0x21,
    0xd1, 0x2f, 0xa1, 0x7c, 0xbc, 0x2c, 0x57, 0x4c,
    0xcc, 0xab, 0x5e, 0x27, 0x51, 0x67, 0xb0, 0x8b,
    0xd6, 0x86, 0xf8, 0xa0, 0x9d, 0xf8, 0x7e, 0xc3,
    0xff, 0xb3, 0x53, 0x61, 0xb9, 0x4e, 0xbf, 0xa1,
    0x3f, 0xec, 0x0e, 0x48, 0x89, 0xd1, 0x8d, 0xa5,
  };

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_CHACHA_20_Encrypt(uint8_t*  InputMessage,
                                uint32_t  InputMessageLength,
                                const uint8_t  *Key,
                                const uint8_t  *InitializationVector,
                                uint32_t  IvLength,
                                uint8_t  *OutputMessage,
                                uint32_t *OutputMessageLength);

int32_t STM32_CHACHA_20_Decrypt(uint8_t*  InputMessage,
                                uint32_t  InputMessageLength,
                                const uint8_t  *Key,
                                const uint8_t  *InitializationVector,
                                uint32_t  IvLength,
                                uint8_t  *OutputMessage,
                                uint32_t *OutputMessageLength);

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

  int32_t status = CHACHA_SUCCESS;

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

  /* Configure the green led */
  Led_Config();

  /* Toggle the green led before starting the algorithm */
  Led_Toggle(500);

  /* Enable CRC clock */
  __CRC_CLK_ENABLE();

  /* Encrypt DATA with CHACHA 20 */
  status = STM32_CHACHA_20_Encrypt( (uint8_t *) Plaintext, PLAINTEXT_LENGTH, Key, IV, sizeof(IV), 
                                   OutputMessage, &OutputMessageLength);
  if (status == CHACHA_SUCCESS)
  {
    if (Buffercmp(Expected_Encryption_Result, OutputMessage, PLAINTEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of CHACHA 20 encryption is passed */

    }
    else
    {
      Error_Handler();

    }
  }
  else
  {
    /* In case of encryption not success possible values of status:
     * CHACHA_ERR_BAD_CONTEXT, CHACHA_ERR_BAD_PARAMETER, CHACHA_ERR_BAD_OPERATION
     */

    Error_Handler();
  }

  /* Decrypt DATA with CHACHA 20*/
  status = STM32_CHACHA_20_Decrypt( (uint8_t *) Plaintext, PLAINTEXT_LENGTH, Key, IV, sizeof(IV), OutputMessage,
                                    &OutputMessageLength);
  if (status == CHACHA_SUCCESS)
  {
    if (Buffercmp(Expected_Decryption_Result, OutputMessage, PLAINTEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of CHACHA 20 decryption is passed */

    }
    else
    {

      Error_Handler();

    }
  }
  else
  {
    /* In case of decryption not success possible values of status:
     * CHACHA_ERR_BAD_CONTEXT, CHACHA_ERR_BAD_PARAMETER, CHACHA_ERR_BAD_OPERATION
     */

    Error_Handler();
  }

  /* Turn on the green led in case of CHACHA20 operations are successful*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}
}

/**
  * @brief  ChaCHa20 Encryption example.
  * @param  InputMessage: pointer to input message to be encrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  Key: pointer to the key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @retval error status: can be CHACHA_SUCCESS if success or one of
  *         CHACHA_ERR_BAD_CONTEXT, CHACHA_ERR_BAD_PARAMETER, CHACHA_ERR_BAD_OPERATION
  *         if error occured.
  */
int32_t STM32_CHACHA_20_Encrypt(uint8_t* InputMessage,
                                uint32_t InputMessageLength,
                                const uint8_t  *Key,
                                const uint8_t  *InitializationVector,
                                uint32_t  IvLength,
                                uint8_t  *OutputMessage,
                                uint32_t *OutputMessageLength)
{




  int32_t error_status;
  int32_t outputLength; /* Will store the size of written data */
  CHACHActx_stt chacha20ctx_st; /* Will keep the ChaCha20 Context */

  /* First Initialize the Context */
  chacha20ctx_st.mFlags = E_SK_DEFAULT; /* Default Flags */
  chacha20ctx_st.mIvSize = 8;  /* IV of 8 bytes */
  chacha20ctx_st.mKeySize = 16; /* Key of 16 bytes */


  /* Call Init */
  error_status = CHACHA_Encrypt_Init(&chacha20ctx_st, Key, InitializationVector);

  /* check for initialization errors */
  if (error_status == CHACHA_SUCCESS)
  {
    /* Call Append. It will process inout and generate output */
    error_status = CHACHA_Encrypt_Append(&chacha20ctx_st, InputMessage, InputMessageLength, OutputMessage, &outputLength);
    if (error_status == CHACHA_SUCCESS )
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Call Finish. For chacha20, this is useless, as all output has been already generated */
      /* It's kept here for API compliancy with the rest of the library */
      error_status = CHACHA_Encrypt_Finish(&chacha20ctx_st, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}


/**
  * @brief  ChaCHa20 Decryption example.
  * @param  InputMessage: pointer to input message to be decrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  Key: pointer to the key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @param  OutputMessageLength: pointer to decrypted message length.
  * @retval error status: can be CHACHA_SUCCESS if success or one of
  *         CHACHA_ERR_BAD_CONTEXT, CHACHA_ERR_BAD_PARAMETER, CHACHA_ERR_BAD_OPERATION
  *         if error occured.
  */
int32_t STM32_CHACHA_20_Decrypt(uint8_t* InputMessage,
                                uint32_t InputMessageLength,
                                const uint8_t  *Key,
                                const uint8_t  *InitializationVector,
                                uint32_t  IvLength,
                                uint8_t  *OutputMessage,
                                uint32_t *OutputMessageLength)
{




  int32_t error_status;
  int32_t outputLength; /* Will store the size of written data */
  CHACHActx_stt chacha20ctx_st; /* Will keep the ChaCha20 Context */

  /* First Initialize the Context */
  chacha20ctx_st.mFlags = E_SK_DEFAULT; /* Default Flags */
  chacha20ctx_st.mIvSize = 8;  /* IV of 8 bytes */
  chacha20ctx_st.mKeySize = 32; /* Key of 32 bytes */


  /* Call Init */
  error_status = CHACHA_Decrypt_Init(&chacha20ctx_st, Key, InitializationVector);

  /* check for initialization errors */
  if (error_status == CHACHA_SUCCESS)
  {
    /* Call Append. It will process inout and generate output */
    error_status = CHACHA_Decrypt_Append(&chacha20ctx_st, InputMessage, InputMessageLength, OutputMessage, &outputLength);
    if (error_status == CHACHA_SUCCESS )
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Call Finish. For chacha20, this is useless, as all output has been already generated */
      /* It's kept here for API compliancy with the rest of the library */
      error_status = CHACHA_Decrypt_Finish(&chacha20ctx_st, OutputMessage + *OutputMessageLength, &outputLength);
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
  
  /* Enable Power Control clock */
  __PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  
  /* Enable MSI Oscillator */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.MSICalibrationValue=0x00;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  
  /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
  
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
