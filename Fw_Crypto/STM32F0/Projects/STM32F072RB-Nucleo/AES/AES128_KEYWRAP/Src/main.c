/**
  ******************************************************************************
  * @file    AES/AES128_KEYWRAP/Src/main.c
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
uint8_t OutputMessage[128];
uint8_t deciphertext[128];
int32_t OutputMessageLength, len;
const uint8_t Plaintext[PLAINTEXT_LENGTH]={
                       0x00,0x11,0x22,0x33,0x44,
                       0x55,0x66,0x77,0x88,0x99,
                       0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
                       
uint8_t key[]={
   0x00,0x01,0x02,0x03,0x04,
   0x05,0x06,0x07,0x08,0x09,
   0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};

uint8_t IV[CRL_AES_KWRAP_BLOCK]={0xA6,0xA6,0xA6,0xA6,0xA6,0xA6,0xA6,
                                             0xA6};

uint8_t Expected_Ciphertext[3*CRL_AES_KWRAP_BLOCK]={0x1F,0xA6,
0x8B,0x0A,0x81,0x12,0xB4,0x47,0xAE,0xF3,0x4B,0xD8,0xFB,0x5A,0x7B,0x82,0x9D,0x3E,
0x86,0x23,0x71,0xD2,0xCF,0xE5};

static GPIO_InitTypeDef  GPIO_InitStruct;

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_AES_kwrap_Encrypt(uint8_t*  InputMessage,
                        uint8_t  InputMessageLength,
                        uint8_t  *Key,
                        uint8_t  *IV,
                        uint8_t  IvLength,
                        uint8_t  *OutputMessage,
                        int32_t *OutputMessageLength);

int32_t STM32_AES_kwrap_Decrypt(uint8_t*  InputMessage,
                        uint8_t  InputMessageLength,
                        uint8_t  *Key,
                        uint8_t  *IV,
                        uint8_t  IvLength,
                        uint8_t  *OutputMessage,
                        int32_t *OutputMessageLength);

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
  
  /* Configure the system clock to 64 MHz */
  SystemClock_Config(); 
  
  /* Configure the green led */
  Led_Config();
  
  /* Toggle the green led before starting the algorithm */
  Led_Toggle(500);
  
  /* Enable CRC clock */
  __CRC_CLK_ENABLE();
 
  /* Encrypt DATA with AES in KEYWRAP mode */
  status = STM32_AES_kwrap_Encrypt( (uint8_t *) Plaintext, PLAINTEXT_LENGTH, key, IV, sizeof(IV), OutputMessage,
                            &OutputMessageLength);

  if (status == AES_SUCCESS)
  {
    if (Buffercmp(Expected_Ciphertext, OutputMessage, 3*CRL_AES_KWRAP_BLOCK) == PASSED)
    {
         /* add application traitment in case of AES keywrap encryption is passed */

    }
    else
    {

       Error_Handler();

    }
  }
  else
  {
     /* In case of encryption/decryption not success, the possible values of status:
       * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION
   */

       Error_Handler();
      
  
              
  }
  /* Decrypt DATA with AES in KEYWRAP mode */
  status = STM32_AES_kwrap_Decrypt( (uint8_t *) Expected_Ciphertext, 3*CRL_AES_KWRAP_BLOCK , key, IV, sizeof(IV), OutputMessage,
                            &OutputMessageLength);
    if (status ==AUTHENTICATION_SUCCESSFUL)
  {
     /* add application traitment in case of AES keywrap authentication is successful*/
  }
  else
  {

       /* add application traitment in case of AES keywrap encryption is failed */
       /* add application traitment in case of AES keywrap authentication is failed, possible values
       *  of status:
       * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, 
       * AUTHENTICATION_FAILED
       */
              Error_Handler();
  }

  /* Turn on the green led in case of AES kwarp operations are succssfuls*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {
  }
}



/**
  * @brief  AES kwrap Encryption example.
  * @param  InputMessage: pointer to input message to be encrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.  
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_AES_kwrap_Encrypt(uint8_t*  InputMessage,
                        uint8_t  InputMessageLength,
                        uint8_t  *Key,
                        uint8_t  *IV,
                        uint8_t  IvLength,
                        uint8_t  *OutputMessage,
                        int32_t *OutputMessageLength)
{ 
 int32_t outputLength = 0;
int32_t status = AES_SUCCESS;
AESKWctx_stt KWctx_st;
KWctx_st.mKeySize = CRL_AES128_KEY;
KWctx_st.mFlags = E_SK_DEFAULT;
  
  status = AES_KeyWrap_Encrypt_Init(&KWctx_st, Key, IV);
  if(status == AES_SUCCESS)
  {
     status = AES_KeyWrap_Encrypt_Append(&KWctx_st, InputMessage, CRL_AES128_KEY, OutputMessage, &outputLength);
     if(status == AES_SUCCESS)
     {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      status = AES_KeyWrap_Encrypt_Finish(&KWctx_st, OutputMessage, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
     }
  }
  return status;
}


/**
  * @brief  AES kwrap Decryption example.
  * @param  InputMessage: pointer to input message to be decrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.  
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @param  OutputMessageLength: pointer to decrypted message length.
  * @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of 
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER, AES_ERR_BAD_INPUT_SIZE, AUTHENTICATION_FAILED if error occured.  
  */
int32_t STM32_AES_kwrap_Decrypt(uint8_t*  InputMessage,
                        uint8_t  InputMessageLength,
                        uint8_t  *Key,
                        uint8_t  *IV,
                        uint8_t  IvLength,
                        uint8_t  *OutputMessage,
                        int32_t *OutputMessageLength)
{
         int32_t outputLength = 0;
         int32_t status = AES_SUCCESS;
         AESKWctx_stt KWctx_st;
         KWctx_st.mKeySize = CRL_AES128_KEY;
         KWctx_st.mFlags = E_SK_DEFAULT;

  /* Initialize the operation, by passing the key.*/
         status = AES_KeyWrap_Decrypt_Init(&KWctx_st, Key, IV);

  /* check for initialization errors */
  if (status == AES_SUCCESS)
  {
    /* Decrypt Data */
    status = AES_KeyWrap_Decrypt_Append(&KWctx_st,
                                        InputMessage, 
                                        InputMessageLength,
                                        OutputMessage, 
                                        &outputLength );

    if (status == AES_SUCCESS)
    {
      /* Write the number of data written*/
     *OutputMessageLength = outputLength;
      /* Do the Finalization */
      status = AES_KeyWrap_Decrypt_Finish(&KWctx_st, OutputMessage, &outputLength);  
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return status;
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
  *            System Clock source            = PLL (HSI48)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 48000000
  *            PREDIV                         = 2
  *            PLLMUL                         = 2
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Select HSI48 Oscillator as PLL source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI48;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK and PCLK1 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
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
static void Led_Toggle(uint32_t toggle_delay)
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
  {
  }
}
#endif


/**
  * @}
  */


/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/
