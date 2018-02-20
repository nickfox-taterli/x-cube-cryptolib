/**
  ******************************************************************************
  * @file    AES/AES128_CCM/Src/main.c
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
#define TAG_LENGTH 4
#define PLAINTEXT_LENGTH 4
#define CIPHER_TEXT_LENGTH PLAINTEXT_LENGTH + TAG_LENGTH

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Header message, will be authenticated but not encrypted */
const uint8_t HeaderMessage[] =
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
  };

uint32_t HeaderLength = sizeof (HeaderMessage) ;

/* string length only, without '\0' end of string marker */


/* Payload message, will be authenticated and encrypted */
const uint8_t Plaintext[] =
  {
    0x20, 0x21, 0x22, 0x23
  };

/* string length only, without '\0' end of string marker */
uint32_t InputLength = sizeof (Plaintext) ;

/* Key to be used for AES encryption/decryption */
uint8_t Key[CRL_AES128_KEY] =
  {
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f
  };

/* Initialization Vector, used only in non-ECB modes */
uint8_t IV[] =
  {
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16
  };

/* NIST example 1 ciphertext vector: in encryption we expect this vector as result */
const uint8_t Expected_Ciphertext[CIPHER_TEXT_LENGTH] =
  {
    0x71, 0x62, 0x01, 0x5b, 0x4d, 0xac, 0x25, 0x5d
  };

/* Buffer to store the output data and the authentication TAG */
uint8_t encrypt_OutputMessage[64];
uint8_t decrypt_OutputMessage[64];
int32_t encrypt_OutputMessageLength = 0;
int32_t decrypt_OutputMessageLength = 0;
int32_t AuthenticationTAGLength = 0;

uint8_t tag[64];

static GPIO_InitTypeDef  GPIO_InitStruct;

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_AES_CCM_Encrypt(uint8_t*  HeaderMessage,
                              uint32_t  HeaderMessageLength,
                              uint8_t*  InputMessage,
                              uint32_t  InputMessageLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              int32_t *OutputMessageLength,
                              int32_t *AuthenticationTAGLength
                             );


int32_t STM32_AES_CCM_Decrypt(uint8_t*  HeaderMessage,
                              uint32_t  HeaderMessageLength,
                              uint8_t*  InputMessage,
                              uint32_t  InputMessageLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              int32_t *OutputMessageLength,
                              int32_t  AuthenticationTAGLength);

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

  /* STM32F0xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 84 MHz */
  SystemClock_Config();

  /* Configure the green led */
  Led_Config();

  /* Toggle the green led toggle three times before starting the algorithm */
  Led_Toggle(500);

  /* Enable CRC clock */
  __CRC_CLK_ENABLE();

  /* Encrypt DATA with AES in CCM mode and generate authentication TAG */

  status = STM32_AES_CCM_Encrypt( (uint8_t *) HeaderMessage, HeaderLength , (uint8_t *) Plaintext,
                                  InputLength, Key, IV, sizeof(IV), encrypt_OutputMessage,
                                  &encrypt_OutputMessageLength, &AuthenticationTAGLength);
  if (status == AES_SUCCESS)
  {

    if (Buffercmp(Expected_Ciphertext, encrypt_OutputMessage, CIPHER_TEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of AES CCM encryption is passed */

    }
    else
    {

      Error_Handler();

    }
  }
  else
  {

    /* In case of encryption/decryption not success possible values of status:
    * AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER
    */

    Error_Handler();


  }

  /* Decrypt DATA with AES in CCM mode and check the authentication TAG */
  status = STM32_AES_CCM_Decrypt( (uint8_t *) HeaderMessage, sizeof(HeaderMessage), (uint8_t *) encrypt_OutputMessage,
                                  encrypt_OutputMessageLength, Key, IV, sizeof(IV), decrypt_OutputMessage,
                                  &decrypt_OutputMessageLength, AuthenticationTAGLength);
  if (status == AUTHENTICATION_SUCCESSFUL)
  {

    if (Buffercmp(Plaintext, decrypt_OutputMessage, PLAINTEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of AES CCM encryption is passed */

    }
    else
    {

      Error_Handler();


    }
    /* Add application traitment in case of AES CCM authentication is successful */
  }
  else
  {
    /*  In case of AES CCM authentication is failed possible values
      *  of status:
      * AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, 
      * AUTHENTICATION_FAILED
      */

    Error_Handler();


  }



  /* Turn on the green led in an infinite loop in case of AES CCM operations are succssfuls*/
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  while (1)
  {}
}


/**
  * @brief  AES CCM Authenticated Encryption example.
  * @param  HeaderMessage: pointer to the header message. It will be authenticated but not encrypted.
  * @param  HeaderMessageLength: header message length in byte.
  * @param  Plaintext: pointer to input message to be encrypted.
  * @param  PlaintextLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message and TAG
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @param  AuthenticationTAGLength: authentication TAG length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_AES_CCM_Encrypt(uint8_t*  HeaderMessage,
                              uint32_t  HeaderMessageLength,
                              uint8_t*  Plaintext,
                              uint32_t  PlaintextLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              int32_t *OutputMessageLength,
                              int32_t *AuthenticationTAGLength
                             )
{
  AESCCMctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = 16;

  /* Set nonce size field to IvLength, note that valid values are 7,8,9,10,11,12,13*/
  AESctx.mNonceSize = IvLength;

  /* Size of returned authentication TAG */
  AESctx.mTagSize = 4;

  /* Set the size of the header */
  AESctx.mAssDataSize = HeaderMessageLength;

  /* Set the size of thepayload */
  AESctx.mPayloadSize = PlaintextLength;

  /* Initialize the operation, by passing the key and IV */
  error_status = AES_CCM_Encrypt_Init(&AESctx, AES128_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Process Header */
    error_status = AES_CCM_Header_Append(&AESctx,
                                         HeaderMessage,
                                         HeaderMessageLength);
    if (error_status == AES_SUCCESS)
    {
      /* Encrypt Data */
      error_status = AES_CCM_Encrypt_Append(&AESctx,
                                            Plaintext,
                                            PlaintextLength,
                                            OutputMessage,
                                            OutputMessageLength);

      if (error_status == AES_SUCCESS)
      {
        /* Do the Finalization, write the TAG at the end of the encrypted message */
        error_status = AES_CCM_Encrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, AuthenticationTAGLength);
      }
    }
  }

  return error_status;
}


/**
  * @brief  AES CCM Authenticated Decryption example.
  * @param  HeaderMessage: pointer to the header message. It will be authenticated but not Decrypted.
  * @param  HeaderMessageLength: header message length in byte.
  * @param  Plaintext: pointer to input message to be Decrypted.
  * @param  PlaintextLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the Decrypted message and TAG
  * @param  OutputMessageLength: pointer to Decrypted message length.
  * @param  AuthenticationTAGLength: authentication TAG length.
  * @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER, AUTHENTICATION_FAILED if error occured.
  */
int32_t STM32_AES_CCM_Decrypt(uint8_t*  HeaderMessage,
                              uint32_t  HeaderMessageLength,
                              uint8_t*  Plaintext,
                              uint32_t  PlaintextLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              int32_t *OutputMessageLength,
                              int32_t  AuthenticationTAGLength
                             )
{
  AESCCMctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = 16;

  /* Set nonce size field to IvLength, note that valid values are 7,8,9,10,11,12,13*/
  AESctx.mNonceSize = IvLength;

  /* Size of returned authentication TAG */
  AESctx.mTagSize = 4;

  /* Set the size of the header */
  AESctx.mAssDataSize = HeaderMessageLength;

  /* Set the size of thepayload */
  AESctx.mPayloadSize = PlaintextLength;

  /* Set the pointer to the TAG to be checked */
  AESctx.pmTag = Plaintext + PlaintextLength;

  /* Size of returned authentication TAG */
  AESctx.mTagSize = AuthenticationTAGLength;


  /* Initialize the operation, by passing the key and IV */
  error_status = AES_CCM_Decrypt_Init(&AESctx, AES128_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Process Header */
    error_status = AES_CCM_Header_Append(&AESctx,
                                         HeaderMessage,
                                         HeaderMessageLength);
    if (error_status == AES_SUCCESS)
    {
      /* Decrypt Data */
      error_status = AES_CCM_Decrypt_Append(&AESctx,
                                            Plaintext,
                                            PlaintextLength,
                                            OutputMessage,
                                            OutputMessageLength);

      if (error_status == AES_SUCCESS)
      {
        /* Do the Finalization, check the authentication TAG*/
        error_status = AES_CCM_Decrypt_Finish(&AESctx, NULL, &AuthenticationTAGLength);
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


/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/
