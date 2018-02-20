/**
  ******************************************************************************
  * @file    TDES_DES/DES_CBC/Src/main.c
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
    0x4e, 0x6f, 0x77, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68, 0x65, 0x20, 0x74, 0x69,
    0x6d, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x61, 0x6c, 0x6c, 0x20
  };

/* Key to be used for DES encryption/decryption */
uint8_t Key[CRL_TDES_KEY] =
  {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,  /* key 1 */
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,  /* key 2 */
    0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67
  }
  ; /* key 3 */
/* Initialization Vector */
uint8_t IV[CRL_TDES_BLOCK] =
  {
    0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef
  };

/* Buffer to store the output data */
uint8_t OutputMessage[PLAINTEXT_LENGTH];

/* Size of the output data */
uint32_t OutputMessageLength = 0;

const uint8_t Expected_Ciphertext[PLAINTEXT_LENGTH] =
  {
    0xe5, 0xc7, 0xcd, 0xde, 0x87, 0x2b, 0xf2, 0x7c, 0x43, 0xe9, 0x34, 0x00, 0x8c,
    0x38, 0x9c, 0x0f, 0x68, 0x37, 0x88, 0x49, 0x9a, 0x7c, 0x05, 0xf6
  };

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_DES_CBC_Encrypt(uint8_t*  InputMessage,
                              uint32_t  InputMessageLength,
                              uint8_t  *DES_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              uint32_t *OutputMessageLength);

int32_t STM32_DES_CBC_Decrypt(uint8_t*  InputMessage,
                              uint32_t  InputMessageLength,
                              uint8_t  *DES_Key,
                              uint8_t  *InitializationVector,
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

  int32_t status = TDES_SUCCESS;


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


  /* Encrypt DATA with DES in CBC mode */
  status = STM32_DES_CBC_Encrypt( (uint8_t *) Plaintext, PLAINTEXT_LENGTH, Key, IV, sizeof(IV), OutputMessage,
                                  &OutputMessageLength);
  if (status == DES_SUCCESS)
  {
    if (Buffercmp(Expected_Ciphertext, OutputMessage, PLAINTEXT_LENGTH) == PASSED)
    {

      /* add application traitment in case of DES CBC encryption is passed */


    }
    else
    {

      Error_Handler();

    }
  }
  else
  {
    /* In case of encryption/decryption not success possible values of status:
      * DES_ERR_BAD_INPUT_SIZE, DES_ERR_BAD_OPERATION, DES_ERR_BAD_CONTEXT, DES_ERR_BAD_PARAMETER
      */

    /* Turn off the green led in case of encryption/decryption not success*/
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    Error_Handler();
  }
  /* Decrypt DATA with DES in CBC mode */
  status = STM32_DES_CBC_Decrypt( (uint8_t *) Expected_Ciphertext, PLAINTEXT_LENGTH, Key, IV, sizeof(IV), OutputMessage,
                                  &OutputMessageLength);
  if (status == DES_SUCCESS)
  {
    if (Buffercmp(Plaintext, OutputMessage, PLAINTEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of DES CBC encryption is passed */

    }
    else
    {
      Error_Handler();
    }
  }
  else
  {
    /* In case of encryption/decryption not success possible values of status:
      * DES_ERR_BAD_INPUT_SIZE, DES_ERR_BAD_OPERATION, DES_ERR_BAD_CONTEXT, DES_ERR_BAD_PARAMETER
      */

    Error_Handler();
  }
  /* Turn on the green led in case of DES CBC operations are successful*/
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  while (1)
  {}
}

/**
  * @brief  DES CBC Encryption example.
  * @param  InputMessage: pointer to input message to be encrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  DES_Key: pointer to the DES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @retval error status: can be DES_SUCCESS if success or one of
  *         DES_ERR_BAD_INPUT_SIZE, DES_ERR_BAD_OPERATION, DES_ERR_BAD_CONTEXT
  *         DES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_DES_CBC_Encrypt(uint8_t* InputMessage,
                              uint32_t InputMessageLength,
                              uint8_t  *DES_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              uint32_t *OutputMessageLength)
{
  DESCBCctx_stt DESctx;

  uint32_t error_status = DES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  DESctx.mFlags = E_SK_DEFAULT;

  /* Set iv size field to IvLength*/
  DESctx.mIvSize = IvLength;

  /* Initialize the operation, by passing the key.
   * Third parameter is NULL because CBC doesn't use any IV */
  error_status = DES_CBC_Encrypt_Init(&DESctx, DES_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == DES_SUCCESS)
  {
    /* Encrypt Data */
    error_status = DES_CBC_Encrypt_Append(&DESctx,
                                          InputMessage,
                                          InputMessageLength,
                                          OutputMessage,
                                          &outputLength);

    if (error_status == DES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = DES_CBC_Encrypt_Finish(&DESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}


/**
  * @brief  DES CBC Decryption example.
  * @param  InputMessage: pointer to input message to be decrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  DES192_Key: pointer to the DES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @param  OutputMessageLength: pointer to decrypted message length.
  * @retval error status: can be DES_SUCCESS if success or one of
  *         DES_ERR_BAD_INPUT_SIZE, DES_ERR_BAD_OPERATION, DES_ERR_BAD_CONTEXT
  *         DES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_DES_CBC_Decrypt(uint8_t* InputMessage,
                              uint32_t InputMessageLength,
                              uint8_t  *DES_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              uint32_t *OutputMessageLength)
{
  DESCBCctx_stt DESctx;

  uint32_t error_status = DES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  DESctx.mFlags = E_SK_DEFAULT;

  /* Set iv size field to IvLength*/
  DESctx.mIvSize = IvLength;

  /* Initialize the operation, by passing the key.
   * Third parameter is NULL because CBC doesn't use any IV */
  error_status = DES_CBC_Decrypt_Init(&DESctx, DES_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == DES_SUCCESS)
  {
    /* Decrypt Data */
    error_status = DES_CBC_Decrypt_Append(&DESctx,
                                          InputMessage,
                                          InputMessageLength,
                                          OutputMessage,
                                          &outputLength);

    if (error_status == DES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = DES_CBC_Decrypt_Finish(&DESctx, OutputMessage + *OutputMessageLength, &outputLength);
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/