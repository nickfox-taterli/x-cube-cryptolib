/**
  ******************************************************************************
  * @file    C25519/KeyGen_KeyExch/Src/main.c
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

const uint8_t Secret_Key_A[] =
  {
    0x70, 0x07, 0x6D, 0x0A, 0x73, 0x18, 0xA5, 0x7D, 0x3C, 0x16, 0xC1, 0x72, 0x51, 0xB2, 0x66, 0x45,
    0xDF, 0x4C, 0x2F, 0x87, 0xEB, 0xC0, 0x99, 0x2A, 0xB1, 0x77, 0xFB, 0xA5, 0x1D, 0xB9, 0x2C, 0x6A
  };

const uint8_t Public_Key_A[] =
  {
    0x85, 0x20, 0xF0, 0x09, 0x89, 0x30, 0xA7, 0x54, 0x74, 0x8B, 0x7D, 0xDC, 0xB4, 0x3E, 0xF7, 0x5A,
    0x0D, 0xBF, 0x3A, 0x0D, 0x26, 0x38, 0x1A, 0xF4, 0xEB, 0xA4, 0xA9, 0x8E, 0xAA, 0x9B, 0x4E, 0x6A
  };

const uint8_t Secret_Key_B[] =
  {
    0x58, 0xAB, 0x08, 0x7E, 0x62, 0x4A, 0x8A, 0x4B, 0x79, 0xE1, 0x7F, 0x8B, 0x83, 0x80, 0x0E, 0xE6,
    0x6F, 0x3B, 0xB1, 0x29, 0x26, 0x18, 0xB6, 0xFD, 0x1C, 0x2F, 0x8B, 0x27, 0xFF, 0x88, 0xE0, 0x6B
  };

const uint8_t Public_Key_B[] =
  {
    0xDE, 0x9E, 0xDB, 0x7D, 0x7B, 0x7D, 0xC1, 0xB4, 0xD3, 0x5B, 0x61, 0xC2, 0xEC, 0xE4, 0x35, 0x37,
    0x3F, 0x83, 0x43, 0xC8, 0x5B, 0x78, 0x67, 0x4D, 0xAD, 0xFC, 0x7E, 0x14, 0x6F, 0x88, 0x2B, 0x4F
  };

const uint8_t Shared_Secret[] =
  {
    0x4A, 0x5D, 0x9D, 0x5B, 0xA4, 0xCE, 0x2D, 0xE1, 0x72, 0x8E, 0x3B, 0xF4, 0x80, 0x35, 0x0F, 0x25,
    0xE0, 0x7E, 0x21, 0xC9, 0x47, 0xD1, 0x9E, 0x33, 0x76, 0xF0, 0x9B, 0x3C, 0x1E, 0x16, 0x17, 0x42
  };
const uint8_t G[32] =
  {
    0x09
  }
  ; /* Generator, used in key generation from a given private key using C25519keyExchange function */
uint8_t result_buffer[32]; /* We'll store result here */
uint8_t private_key[32]; /* Buffer for the private key*/
uint8_t public_key[32]; /* Buffer for the public key */

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_C25519_RandKeyGen(   uint8_t private_key[32],
                                   uint8_t public_key[32]);

TestStatus Buffercmp(const uint8_t* pBuffer,
                     const uint8_t* pBuffer1,
                     uint16_t BufferLength);

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
int main(void)
{
  int32_t status = C25519_SUCCESS ;

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


  /* Curve25519 Key Generation */
  status = STM32_C25519_RandKeyGen(private_key, public_key );
  if (status == C25519_SUCCESS)
  {
    /* add application traitment in case of generation key is success */
  }
  else
  {

    /* In case of generation key not success possible values of status:
     * C25519_ERR_BAD_PARAMETER, RNG_ERR_BAD_PARAMETER, RNG_ERR_BAD_ENTROPY_SIZE,
     *      RNG_ERR_BAD_PERS_STRING_SIZE, RNG_ERR_BAD_NONCE_SIZE, RNG_ERR_UNINIT_STATE 
     *      RNG_ERR_RESEED_NEEDED, RNG_ERR_BAD_ADD_INPUT_SIZE, RNG_ERR_BAD_REQUEST      
     */

    Error_Handler();

  }

  /* Curve25519 Keys Exchange */
  status = C25519keyExchange(result_buffer, Secret_Key_A, G);
  if (status == C25519_SUCCESS)
  {
    if (Buffercmp(result_buffer, Public_Key_A, 32) == PASSED)
    {
      status = C25519keyExchange(result_buffer, Secret_Key_B, G);
      if (status == C25519_SUCCESS)
      {
        if (Buffercmp(result_buffer, Public_Key_B, 32) == PASSED)
        {
          status = C25519keyExchange(result_buffer, Secret_Key_A,  Public_Key_B);
          if (status == C25519_SUCCESS)
          {
            if (Buffercmp(result_buffer, Shared_Secret, 32) == PASSED)
            {
              /* Add application traitment in case of generation of the shared secret is PASSED*/
            }
            else
            {
              Error_Handler();
            }
          }
          else
          {
            /* In case of generation of shared secret is not success the possible values of status:
            C25519_ERR_BAD_PARAMETER*/


            Error_Handler();
          }
        }
        else
        {
          Error_Handler();
        }
      }
      else
      {
        /* In case of generation of the secret_key_B is not success possible values of status: C25519_ERR_BAD_PARAMETER*/
        /* Turn off the green led in case of generation of secret_key_B is not success*/
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        Error_Handler();
      }
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


  /* Turn on the green led in case of Curve 25519 operations are successful*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}
}


/*
 * @brief  Curve25519 Key Generation Example
 * @param[out]  private_key: Buffer for the private key generated
 * @param[out]  public_key: Buffer for the public key generated
 * @retval error status: can be C25519_SUCCESS if success or one of
 * C25519_ERR_BAD_PARAMETER, RNG_ERR_BAD_PARAMETER, RNG_ERR_BAD_ENTROPY_SIZE,
 *      RNG_ERR_BAD_PERS_STRING_SIZE, RNG_ERR_BAD_NONCE_SIZE, RNG_ERR_UNINIT_STATE 
 *      RNG_ERR_RESEED_NEEDED, RNG_ERR_BAD_ADD_INPUT_SIZE, RNG_ERR_BAD_REQUEST 
 */
int32_t STM32_C25519_RandKeyGen( uint8_t private_key[32], uint8_t public_key[32])
{

  int32_t error_status;

  RNGinitInput_stt RNGinit_st; /* Structure used to initialize the Random Engine */
  RNGstate_stt RNGstate;      /* Structure that keep the Random Engine State */
  /* String of entropy. This is an example, in real use case it is required to contain entropy */
  uint8_t example_string[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };


  /* Initialize RNGinit_st structure */
  RNGinit_st.pmEntropyData = example_string;
  RNGinit_st.mEntropyDataSize = sizeof(example_string);
  RNGinit_st.mPersDataSize = 0;
  RNGinit_st.mNonceSize = 0;
  /* Call Random Inizialiazion */
  error_status = RNGinit(&RNGinit_st, &RNGstate);
  if (error_status == RNG_SUCCESS )
  {
    /* First generate random 32 bytes into private_key */
    error_status  = RNGgenBytes(&RNGstate, NULL, private_key, 32);
    if (error_status == RNG_SUCCESS)
    {
      error_status = C25519keyGen(private_key, public_key);
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
TestStatus Buffercmp(const uint8_t* pBuffer, const uint8_t* pBuffer1, uint16_t BufferLength)
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
