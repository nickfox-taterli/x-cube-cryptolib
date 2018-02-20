/**
  ******************************************************************************
  * @file    ARC4/Enc_Dec/Src/main.c
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
	
#include "main.h"

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#define ARC4_LENGTH 32
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t InputMessage[32] =
  {
    0x00
  };

uint32_t InputLength = sizeof(InputMessage);

/* Key to be used for ARC4 encryption/decryption */
uint8_t Key[5] =
  {
    0x01, 0x02, 0x03, 0x04, 0x05
  };

/* Buffer to store the output data */
uint8_t OutputMessage[ARC4_LENGTH];

/* Size of the output data */
uint32_t OutputMessageLength = 0;

const uint8_t Expected_OutputMessage[ARC4_LENGTH] =
  {
    0xb2, 0x39, 0x63, 0x05,
    0xf0, 0x3d, 0xc0, 0x27,
    0xcc, 0xc3, 0x52, 0x4a,
    0x0a, 0x11, 0x18, 0xa8,
    0x69, 0x82, 0x94, 0x4f,
    0x18, 0xfc, 0x82, 0xd5,
    0x89, 0xc4, 0x03, 0xa4,
    0x7a, 0x0d, 0x09, 0x19
  };

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_ARC4_Encrypt(uint8_t* InputMessage,
                           uint32_t InputMessageLength,
                           uint8_t  *ARC4_Key,
                           uint32_t KeyLength,
                           uint8_t  *OutputMessage,
                           uint32_t *OutputMessageLength);

int32_t STM32_ARC4_Decrypt(uint8_t* InputMessage,
                           uint32_t InputMessageLength,
                           uint8_t  *ARC4_Key,
                           uint32_t KeyLength,
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

  int32_t status = ARC4_SUCCESS;

  /* STM32F103xB HAL library initialization:
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

  /* Encrypt DATA with ARC4 */
  status = STM32_ARC4_Encrypt( (uint8_t *) InputMessage, InputLength, Key, (uint32_t) sizeof(Key), OutputMessage,
                               &OutputMessageLength);
  if (status == ARC4_SUCCESS)
  {

    if (Buffercmp(Expected_OutputMessage, OutputMessage, OutputMessageLength) == PASSED)
    {
      /* add application traitment in case of ARC4 success */

    }
    else
    {

      Error_Handler();

    }
  }
  else
  {
    /* In case of encryption/decryption not success the possible values of status:
     * ARC4_ERR_BAD_OPERATION, ARC4_ERR_BAD_CONTEXT, ARC4_ERR_BAD_PARAMETER
     */

    Error_Handler();

  }

  /* Data has been encrypted, now decrypt it.
   * Decrypt DATA with ARC4 */
  status = STM32_ARC4_Decrypt( (uint8_t *) Expected_OutputMessage, ARC4_LENGTH, Key, (uint32_t) sizeof(Key),
                               OutputMessage, &OutputMessageLength);
  if (status == ARC4_SUCCESS)
  {

    if (Buffercmp(InputMessage, OutputMessage, InputLength) == PASSED)
    {
      /* add application traitment in case of ARC4 success */

    }
    else
    {

      Error_Handler();

    }
  }
  else
  {
    /* In case of encryption/decryption not success the possible values of status:
     * ARC4_ERR_BAD_OPERATION, ARC4_ERR_BAD_CONTEXT, ARC4_ERR_BAD_PARAMETER
     */

    Error_Handler();

  }

  /* Turn on the green led in case of ARC4 operations are successful*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}
}



/**
  * @brief  ARC4 Encryption example.
  * @param  InputMessage: pointer to input message to be encrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  ARC4_Key: pointer to the ARC4 key to be used in the operation
  * @param  KeyLength: ARC4 key length in byte
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @retval error status: can be ARC4_SUCCESS if success or one of
  *         ARC4_ERR_BAD_OPERATION, ARC4_ERR_BAD_CONTEXT, ARC4_ERR_BAD_PARAMETER
  *         if error occured.
  */
int32_t STM32_ARC4_Encrypt(uint8_t* InputMessage,
                           uint32_t InputMessageLength,
                           uint8_t  *ARC4_Key,
                           uint32_t KeyLength,
                           uint8_t  *OutputMessage,
                           uint32_t *OutputMessageLength)
{
  ARC4ctx_stt ARC4ctx;

  uint32_t error_status = ARC4_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  ARC4ctx.mFlags = E_SK_DEFAULT;

  /* Set key length in the context */
  ARC4ctx.mKeySize = KeyLength;

  /* Initialize the operation, by passing the key.
   * Third parameter is NULL because ARC4 doesn't use any IV */
  error_status = ARC4_Encrypt_Init(&ARC4ctx, ARC4_Key, NULL );

  /* check for initialization errors */
  if (error_status == ARC4_SUCCESS)
  {
    /* Encrypt Data */
    error_status = ARC4_Encrypt_Append(&ARC4ctx,
                                       InputMessage,
                                       InputMessageLength,
                                       OutputMessage,
                                       &outputLength);

    if (error_status == ARC4_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = ARC4_Encrypt_Finish(&ARC4ctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}


/**
  * @brief  ARC4 Decryption example.
  * @param  InputMessage: pointer to input message to be decrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  ARC4_Key: pointer to the ARC4 key to be used in the operation
  * @param  KeyLength: ARC4 key length in byte
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @param  OutputMessageLength: pointer to decrypted message length.
  * @retval error status: can be ARC4_SUCCESS if success or one of
  *         ARC4_ERR_BAD_OPERATION, ARC4_ERR_BAD_CONTEXT, ARC4_ERR_BAD_PARAMETER
  *         if error occured.
  */
int32_t STM32_ARC4_Decrypt(uint8_t* InputMessage,
                           uint32_t InputMessageLength,
                           uint8_t  *ARC4_Key,
                           uint32_t KeyLength,
                           uint8_t  *OutputMessage,
                           uint32_t *OutputMessageLength)
{
  ARC4ctx_stt ARC4ctx;

  uint32_t error_status = ARC4_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  ARC4ctx.mFlags = E_SK_DEFAULT;

  /* Set key length in the context */
  ARC4ctx.mKeySize = KeyLength;

  /* Initialize the operation, by passing the key.
   * Third parameter is NULL because ECB doesn't use any IV */
  error_status = ARC4_Decrypt_Init(&ARC4ctx, ARC4_Key, NULL );

  /* check for initialization errors */
  if (error_status == ARC4_SUCCESS)
  {
    /* Decrypt Data */
    error_status = ARC4_Decrypt_Append(&ARC4ctx,
                                       InputMessage,
                                       InputMessageLength,
                                       OutputMessage,
                                       &outputLength);

    if (error_status == ARC4_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = ARC4_Decrypt_Finish(&ARC4ctx, OutputMessage + *OutputMessageLength, &outputLength);
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
