/**
  ******************************************************************************
  * @file    POlY1305/GetMAC_VerifMAC/Src/main.c
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
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

const uint8_t Key[] =
  {
    0xec, 0x07, 0x4c, 0x83, 0x55, 0x80, 0x74, 0x17,
    0x01, 0x42, 0x5b, 0x62, 0x32, 0x35, 0xad, 0xd6,
    0x85, 0x1f, 0xc4, 0x0c, 0x34, 0x67, 0xac, 0x0b,
    0xe0, 0x5c, 0xc2, 0x04, 0x04, 0xf3, 0xf7, 0x00
  };
const uint8_t Nonce[] =
  {
    0xfb, 0x44, 0x73, 0x50, 0xc4, 0xe8, 0x68, 0xc5,
    0x2a, 0xc3, 0x27, 0x5c, 0xf9, 0xd4, 0x32, 0x7e
  };
const uint8_t Input[] =
  {
    0xf3, 0xf6
  };


/* Buffer to store the output data */
uint8_t OutputMessage[16];

/* Size of the output data */
uint32_t OutputMessageLength = 0;

const uint8_t Expected_Result[] =
  {
    0xf4, 0xc6, 0x33, 0xc3, 0x04, 0x4f, 0xc1, 0x45,
    0xf8, 0x4f, 0x33, 0x5c, 0xb8, 0x19, 0x53, 0xde
  };

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_POLY1305_GET_MAC(const uint8_t *input,
                               const uint8_t *key,
                               const uint8_t *nonce,
                               int32_t inputSize,
                               uint8_t  *OutputMessage,
                               uint32_t *OutputMessageLength);
int32_t STM32_POLY1305_VERIFY_MAC
(const uint8_t *input,
 const uint8_t *key,
 const uint8_t *nonce,
 int32_t inputSize,
 const uint8_t *expectedResult);


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

  int32_t status = POLY1305_SUCCESS;

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


  /* Encrypt DATA with AES in CTR mode */
  status = STM32_POLY1305_GET_MAC(Input,
                                  Key,
                                  Nonce,
                                  sizeof(Input),
                                  OutputMessage,
                                  &OutputMessageLength);


  if (status == POLY1305_SUCCESS)
  {
    if ((Buffercmp(Expected_Result, OutputMessage, 16) == PASSED) || OutputMessageLength == 16)
    {
      /* add application traitment in case of POLY1305 encryption is passed */

    }
    else
    {


      Error_Handler();

    }
  }
  else
  {
    /* In case of POLY1305 encryption not success possible values of status:
       * POLY1305_ERR_BAD_CONTEXT, POLY1305_ERR_BAD_PARAMETER, POLY1305_ERR_BAD_OPERATION
       */

    Error_Handler();
  }
  status = STM32_POLY1305_VERIFY_MAC(Input,
                                     Key,
                                     Nonce,
                                     sizeof(Input),
                                     OutputMessage);

  if (status == AUTHENTICATION_SUCCESSFUL)
  {
    /* add application traitment in case of POLY1305 authentication is successful */

  }
  else
  {
    /* In case of POLY1305 authentication is failed possible values of status:
       * POLY1305_ERR_BAD_CONTEXT, POLY1305_ERR_BAD_PARAMETER, POLY1305_ERR_BAD_OPERATION, 
       * AUTHENTICATION_FAILED*/

    Error_Handler();
  }

  /* Turn on the green led in case of POLY1305 operations are successful*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}
}

/**
* @brief  Function to test the TAG Generation Functionalities of Poly1305-AES
* @param[in]  *input          Input message to be authenticated
* @param[in]  *key            Key
* @param[in]  *nonce          Nonce
* @param[in]   inputSize      Size of input
* @retval error status: can be POLY1305_SUCCESS if success or one of
*         POLY1305_ERR_BAD_CONTEXT, POLY1305_ERR_BAD_PARAMETER, POLY1305_ERR_BAD_OPERATION
*         if error occured.
*/
int32_t STM32_POLY1305_GET_MAC(const uint8_t *input, const uint8_t *key, const uint8_t *nonce, int32_t inputSize, uint8_t  *OutputMessage,
                               uint32_t *OutputMessageLength)
{

  int32_t outputLength = 16;
  Poly1305ctx_stt polyctx;
  uint32_t error_status = POLY1305_SUCCESS;


  /* Initialize Context by setting the size of the required TAG */
  polyctx.mTagSize = 16;

  /* Initialize operation */
  error_status = Poly1305_Auth_Init(&polyctx, key, nonce);

  if (error_status == POLY1305_SUCCESS)
  {
    error_status = Poly1305_Auth_Append(&polyctx,
                                        input,
                                        inputSize);


    if (error_status == POLY1305_SUCCESS)
    {

      error_status = Poly1305_Auth_Finish(&polyctx, OutputMessage , &outputLength);

    }
  }

  return error_status;
}


/**
* @brief  Function to test the TAG Verification Functionalities of Poly1305-AES
* @param[in]  *input          Input message to be authenticated
* @param[in]  *key            Key
* @param[in]  *nonce          Nonce
* @param[in]   inputSize      Size of input
* @param[in]  *expectedResult Expected Result, used in verification
* @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of
*         POLY1305_ERR_BAD_CONTEXT, POLY1305_ERR_BAD_PARAMETER, POLY1305_ERR_BAD_OPERATION, AUTHENTICATION_FAILED
*         if error occured.
*/
int32_t STM32_POLY1305_VERIFY_MAC(const uint8_t *input, const uint8_t *key, const uint8_t *nonce, int32_t inputSize, const uint8_t *expectedResult)
{
  uint32_t error_status ;
  Poly1305ctx_stt polyctx;

  /* Initialize Context by setting the size of the required TAG and pointer to TAG to be verified */
  polyctx.mTagSize = 16;
  polyctx.pmTag = expectedResult;

  /* Initialize operation */
  error_status = Poly1305_Verify_Init(&polyctx, key, nonce);
  if (error_status == POLY1305_SUCCESS)
  {
    error_status = Poly1305_Verify_Append(&polyctx, input, inputSize);

    if (error_status == POLY1305_SUCCESS)
    {
      /* Generate TAG */
      error_status = Poly1305_Verify_Finish(&polyctx, NULL, NULL);
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
