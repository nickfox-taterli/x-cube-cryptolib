/**
  ******************************************************************************
  * @file    ED25519/KeyGen_Sign_Verif/Src/main.c
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

uint8_t private_key[64]; /* Buffer for the private key*/
uint8_t public_key2[64]; /* Buffer for the private key*/
uint8_t public_key[32];  /* Buffer for the public key */
uint8_t signature[64];

/* The following test vector is the second test of http://ed25519.cr.yp.to/python/sign.input */

uint8_t ed25519_correct_sk[64] =
  {
    0x4c, 0xcd, 0x08, 0x9b, 0x28, 0xff, 0x96, 0xda, 0x9d, 0xb6, 0xc3, 0x46, 0xec, 0x11, 0x4e, 0x0f,
    0x5b, 0x8a, 0x31, 0x9f, 0x35, 0xab, 0xa6, 0x24, 0xda, 0x8c, 0xf6, 0xed, 0x4f, 0xb8, 0xa6, 0xfb,
    0x3d, 0x40, 0x17, 0xc3, 0xe8, 0x43, 0x89, 0x5a, 0x92, 0xb7, 0x0a, 0xa7, 0x4d, 0x1b, 0x7e, 0xbc,
    0x9c, 0x98, 0x2c, 0xcf, 0x2e, 0xc4, 0x96, 0x8c, 0xc0, 0xcd, 0x55, 0xf1, 0x2a, 0xf4, 0x66, 0x0c,
  };
const uint8_t ed25519_correct_pk[32] =
  {
    0x3d, 0x40, 0x17, 0xc3, 0xe8, 0x43, 0x89, 0x5a, 0x92, 0xb7, 0x0a, 0xa7, 0x4d, 0x1b, 0x7e, 0xbc,
    0x9c, 0x98, 0x2c, 0xcf, 0x2e, 0xc4, 0x96, 0x8c, 0xc0, 0xcd, 0x55, 0xf1, 0x2a, 0xf4, 0x66, 0x0c,
  };
const uint8_t ed25519_correct_sign[64] =
  {
    0x92, 0xa0, 0x09, 0xa9, 0xf0, 0xd4, 0xca, 0xb8, 0x72, 0x0e, 0x82, 0x0b, 0x5f, 0x64, 0x25, 0x40,
    0xa2, 0xb2, 0x7b, 0x54, 0x16, 0x50, 0x3f, 0x8f, 0xb3, 0x76, 0x22, 0x23, 0xeb, 0xdb, 0x69, 0xda,
    0x08, 0x5a, 0xc1, 0xe4, 0x3e, 0x15, 0x99, 0x6e, 0x45, 0x8f, 0x36, 0x13, 0xd0, 0xf1, 0x1d, 0x8c,
    0x38, 0x7b, 0x2e, 0xae, 0xb4, 0x30, 0x2a, 0xee, 0xb0, 0x0d, 0x29, 0x16, 0x12, 0xbb, 0x0c, 0x00,
  };
const uint8_t ed25519_m[1] =
  {
    0x72
  };

/* Private function prototypes -----------------------------------------------*/

int32_t STM32_ED25519_RandKeyGen( uint8_t Pr_key[64],
                                  uint8_t Pu_key[32]);
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

  int32_t status = ED25519_SUCCESS;


    /* STM32F3xx HAL library initialization:
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

  /* ED25519 random key generation */
  status = STM32_ED25519_RandKeyGen(private_key, public_key);
  if (status == ED25519_SUCCESS)
  {
  }
  else
  {

    /* In case of generation key not success possible values of status:
     * ED5519_ERR_BAD_PARAMETER, HASH_ERR_INTERNAL, RNG_ERR_BAD_PARAMETER, RNG_ERR_BAD_ENTROPY_SIZE,
     * RNG_ERR_BAD_PERS_STRING_SIZE, RNG_ERR_BAD_NONCE_SIZE, RNG_ERR_UNINIT_STATE 
     * RNG_ERR_RESEED_NEEDED, RNG_ERR_BAD_ADD_INPUT_SIZE, RNG_ERR_BAD_REQUEST 
     */

    Error_Handler();
  }


  /* Generate public key from the secret key */
  status = ED25519keyGen(ed25519_correct_sk, public_key);
  if (status == ED25519_SUCCESS)
  {
    if (Buffercmp(ed25519_correct_pk, public_key, 32) == PASSED)
    {
      /* Call the signature */
      status = ED25519sign(signature, ed25519_m, 1, ed25519_correct_sk);
      if (status == ED25519_SUCCESS)
      {
        if (Buffercmp(signature, ed25519_correct_sign, 64) == PASSED)
        {
          /* Call the signature verification*/
          status = ED25519verify(ed25519_m, 1, ed25519_correct_sign, ed25519_correct_pk);
          if (status == AUTHENTICATION_SUCCESSFUL)
          {
            /* add application traitment in case of ED25519 authentication is successful */
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
      }
      else
      {
        /* In case of ED25519 sign is not success possible values of status :
           ED25519_ERR_BAD_PARAMETER, HASH_ERR_INTERNAL */
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
    /* In case of generation key not success possible values of status:
     * ED25519_ERR_BAD_PARAMETER, HASH_ERR_INTERNAL  */
    Error_Handler();
  }

  /* Turn on the green led in case of ED25519 operations are successful*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}
}

/**
* @brief  ed25519 Random Key Generation
  * @param   Pr_key : new random private key generated
  * @param   Pu_key : new random public key generated
  * @retval error status: can be ED25519_SUCCESS if success or one of
  *     ED5519_ERR_BAD_PARAMETER, HASH_ERR_INTERNAL, RNG_ERR_BAD_PARAMETERRNG_ERR_BAD_ENTROPY_SIZE,
  *     RNG_ERR_BAD_PERS_STRING_SIZE, RNG_ERR_BAD_NONCE_SIZEif error occured.
*/
int32_t STM32_ED25519_RandKeyGen( uint8_t Pr_key[64],
                                  uint8_t Pu_key[32])
{



  RNGinitInput_stt RNGinit_st; /* Structure used to initialize the Random Engine */
  RNGstate_stt RNGstate;      /* Structure that keep the Random Engine State */
  /* String of entropy. This is an example, in real use case it is required to contain entropy */
  uint8_t example_string[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
  int32_t retval;

  /* The first example generates a completly new random key pair */

  /* Initialize RNGinit_st structure */
  RNGinit_st.pmEntropyData = example_string;
  RNGinit_st.mEntropyDataSize = sizeof(example_string);
  RNGinit_st.mPersDataSize = 0;
  RNGinit_st.mNonceSize = 0;
  /* Call Random Inizialiazion */
  retval = RNGinit(&RNGinit_st, &RNGstate);
  if ( retval == RNG_SUCCESS)
  {
    retval = RNGgenBytes(&RNGstate, NULL, private_key, 32);


    if ( retval == RNG_SUCCESS)
    {
      /* The first example generates a completly new random key pair */
      retval = ED25519keyGen(private_key, public_key);

    }
  }

  return retval;

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
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLLMUL                         = RCC_PLL_MUL16 (16)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* HSI Oscillator already ON after system reset, activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
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
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
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
