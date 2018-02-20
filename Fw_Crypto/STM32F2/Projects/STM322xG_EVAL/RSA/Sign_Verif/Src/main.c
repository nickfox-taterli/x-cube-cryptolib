/**
  ******************************************************************************
  * @file    RSA/Sign_Verif/Src/main.c
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

uint8_t preallocated_buffer[4096]; /* buffer required for internal allocation of memory */

/* RSA 1024 Test Vector 1 */
const uint8_t T1_Modulus[] =
  {
    0xa5, 0x6e, 0x4a, 0x0e, 0x70, 0x10, 0x17, 0x58, 0x9a, 0x51, 0x87, 0xdc, 0x7e, 0xa8, 0x41, 0xd1,
    0x56, 0xf2, 0xec, 0x0e, 0x36, 0xad, 0x52, 0xa4, 0x4d, 0xfe, 0xb1, 0xe6, 0x1f, 0x7a, 0xd9, 0x91,
    0xd8, 0xc5, 0x10, 0x56, 0xff, 0xed, 0xb1, 0x62, 0xb4, 0xc0, 0xf2, 0x83, 0xa1, 0x2a, 0x88, 0xa3,
    0x94, 0xdf, 0xf5, 0x26, 0xab, 0x72, 0x91, 0xcb, 0xb3, 0x07, 0xce, 0xab, 0xfc, 0xe0, 0xb1, 0xdf,
    0xd5, 0xcd, 0x95, 0x08, 0x09, 0x6d, 0x5b, 0x2b, 0x8b, 0x6d, 0xf5, 0xd6, 0x71, 0xef, 0x63, 0x77,
    0xc0, 0x92, 0x1c, 0xb2, 0x3c, 0x27, 0x0a, 0x70, 0xe2, 0x59, 0x8e, 0x6f, 0xf8, 0x9d, 0x19, 0xf1,
    0x05, 0xac, 0xc2, 0xd3, 0xf0, 0xcb, 0x35, 0xf2, 0x92, 0x80, 0xe1, 0x38, 0x6b, 0x6f, 0x64, 0xc4,
    0xef, 0x22, 0xe1, 0xe1, 0xf2, 0x0d, 0x0c, 0xe8, 0xcf, 0xfb, 0x22, 0x49, 0xbd, 0x9a, 0x21, 0x37,
  };
const uint8_t T1_pubExp[] =
  {
    0x01, 0x00, 0x01
  };

const uint8_t T1_privExp[] =
  {
    0x33, 0xa5, 0x04, 0x2a, 0x90, 0xb2, 0x7d, 0x4f, 0x54, 0x51, 0xca, 0x9b, 0xbb, 0xd0, 0xb4, 0x47,
    0x71, 0xa1, 0x01, 0xaf, 0x88, 0x43, 0x40, 0xae, 0xf9, 0x88, 0x5f, 0x2a, 0x4b, 0xbe, 0x92, 0xe8,
    0x94, 0xa7, 0x24, 0xac, 0x3c, 0x56, 0x8c, 0x8f, 0x97, 0x85, 0x3a, 0xd0, 0x7c, 0x02, 0x66, 0xc8,
    0xc6, 0xa3, 0xca, 0x09, 0x29, 0xf1, 0xe8, 0xf1, 0x12, 0x31, 0x88, 0x44, 0x29, 0xfc, 0x4d, 0x9a,
    0xe5, 0x5f, 0xee, 0x89, 0x6a, 0x10, 0xce, 0x70, 0x7c, 0x3e, 0xd7, 0xe7, 0x34, 0xe4, 0x47, 0x27,
    0xa3, 0x95, 0x74, 0x50, 0x1a, 0x53, 0x26, 0x83, 0x10, 0x9c, 0x2a, 0xba, 0xca, 0xba, 0x28, 0x3c,
    0x31, 0xb4, 0xbd, 0x2f, 0x53, 0xc3, 0xee, 0x37, 0xe3, 0x52, 0xce, 0xe3, 0x4f, 0x9e, 0x50, 0x3b,
    0xd8, 0x0c, 0x06, 0x22, 0xad, 0x79, 0xc6, 0xdc, 0xee, 0x88, 0x35, 0x47, 0xc6, 0xa3, 0xb3, 0x25,
  };

const uint8_t T1_message_1[] =
  {
    0xcd, 0xc8, 0x7d, 0xa2, 0x23, 0xd7, 0x86, 0xdf, 0x3b, 0x45, 0xe0, 0xbb, 0xbc, 0x72, 0x13, 0x26,
    0xd1, 0xee, 0x2a, 0xf8, 0x06, 0xcc, 0x31, 0x54, 0x75, 0xcc, 0x6f, 0x0d, 0x9c, 0x66, 0xe1, 0xb6,
    0x23, 0x71, 0xd4, 0x5c, 0xe2, 0x39, 0x2e, 0x1a, 0xc9, 0x28, 0x44, 0xc3, 0x10, 0x10, 0x2f, 0x15,
    0x6a, 0x0d, 0x8d, 0x52, 0xc1, 0xf4, 0xc4, 0x0b, 0xa3, 0xaa, 0x65, 0x09, 0x57, 0x86, 0xcb, 0x76,
    0x97, 0x57, 0xa6, 0x56, 0x3b, 0xa9, 0x58, 0xfe, 0xd0, 0xbc, 0xc9, 0x84, 0xe8, 0xb5, 0x17, 0xa3,
    0xd5, 0xf5, 0x15, 0xb2, 0x3b, 0x8a, 0x41, 0xe7, 0x4a, 0xa8, 0x67, 0x69, 0x3f, 0x90, 0xdf, 0xb0,
    0x61, 0xa6, 0xe8, 0x6d, 0xfa, 0xae, 0xe6, 0x44, 0x72, 0xc0, 0x0e, 0x5f, 0x20, 0x94, 0x57, 0x29,
    0xcb, 0xeb, 0xe7, 0x7f, 0x06, 0xce, 0x78, 0xe0, 0x8f, 0x40, 0x98, 0xfb, 0xa4, 0x1f, 0x9d, 0x61,
    0x93, 0xc0, 0x31, 0x7e, 0x8b, 0x60, 0xd4, 0xb6, 0x08, 0x4a, 0xcb, 0x42, 0xd2, 0x9e, 0x38, 0x08,
    0xa3, 0xbc, 0x37, 0x2d, 0x85, 0xe3, 0x31, 0x17, 0x0f, 0xcb, 0xf7, 0xcc, 0x72, 0xd0, 0xb7, 0x1c,
    0x29, 0x66, 0x48, 0xb3, 0xa4, 0xd1, 0x0f, 0x41, 0x62, 0x95, 0xd0, 0x80, 0x7a, 0xa6, 0x25, 0xca,
    0xb2, 0x74, 0x4f, 0xd9, 0xea, 0x8f, 0xd2, 0x23, 0xc4, 0x25, 0x37, 0x02, 0x98, 0x28, 0xbd, 0x16,
    0xbe, 0x02, 0x54, 0x6f, 0x13, 0x0f, 0xd2, 0xe3, 0x3b, 0x93, 0x6d, 0x26, 0x76, 0xe0, 0x8a, 0xed,
    0x1b, 0x73, 0x31, 0x8b, 0x75, 0x0a, 0x01, 0x67, 0xd0,
  };

const uint8_t T1_signature_1[] =
  {
    0x6b, 0xc3, 0xa0, 0x66, 0x56, 0x84, 0x29, 0x30, 0xa2, 0x47, 0xe3, 0x0d, 0x58, 0x64, 0xb4, 0xd8,
    0x19, 0x23, 0x6b, 0xa7, 0xc6, 0x89, 0x65, 0x86, 0x2a, 0xd7, 0xdb, 0xc4, 0xe2, 0x4a, 0xf2, 0x8e,
    0x86, 0xbb, 0x53, 0x1f, 0x03, 0x35, 0x8b, 0xe5, 0xfb, 0x74, 0x77, 0x7c, 0x60, 0x86, 0xf8, 0x50,
    0xca, 0xef, 0x89, 0x3f, 0x0d, 0x6f, 0xcc, 0x2d, 0x0c, 0x91, 0xec, 0x01, 0x36, 0x93, 0xb4, 0xea,
    0x00, 0xb8, 0x0c, 0xd4, 0x9a, 0xac, 0x4e, 0xcb, 0x5f, 0x89, 0x11, 0xaf, 0xe5, 0x39, 0xad, 0xa4,
    0xa8, 0xf3, 0x82, 0x3d, 0x1d, 0x13, 0xe4, 0x72, 0xd1, 0x49, 0x05, 0x47, 0xc6, 0x59, 0xc7, 0x61,
    0x7f, 0x3d, 0x24, 0x08, 0x7d, 0xdb, 0x6f, 0x2b, 0x72, 0x09, 0x61, 0x67, 0xfc, 0x09, 0x7c, 0xab,
    0x18, 0xe9, 0xa4, 0x58, 0xfc, 0xb6, 0x34, 0xcd, 0xce, 0x8e, 0xe3, 0x58, 0x94, 0xc4, 0x84, 0xd7,
  };

static GPIO_InitTypeDef  GPIO_InitStruct;

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_RSA_Sign_SHA1(RSAprivKey_stt * P_pPrivKey,
                      const uint8_t * P_pInputMessage,
                      int32_t P_MessageSize,
                      uint8_t *P_pOutput);

int32_t STM32_RSA_Verify_SHA1(RSApubKey_stt *P_pPubKey,
                        const uint8_t *P_pInputMessage,
                        int32_t P_MessageSize,
                        const uint8_t *P_pSignature);

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

  int32_t status = RSA_SUCCESS;

  RSApubKey_stt PubKey_st; /* Structure that will contain the public key */
  RSAprivKey_stt PrivKey_st; /* Structure that will contain the private key*/
  uint8_t Signature[2048/8]; /* Buffer that will contain the signature */


  /* STM32F2xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
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

  /* TEST VECTOR FOR RSA-1024  */
  PubKey_st.mExponentSize = sizeof(T1_pubExp);
  PubKey_st.mModulusSize = sizeof(T1_Modulus);
  PubKey_st.pmExponent = (uint8_t *) T1_pubExp;
  PubKey_st.pmModulus = (uint8_t *)T1_Modulus;

  PrivKey_st.mExponentSize = sizeof(T1_privExp);
  PrivKey_st.mModulusSize = sizeof(T1_Modulus);
  PrivKey_st.pmExponent = (uint8_t *)T1_privExp;
  PrivKey_st.pmModulus = (uint8_t *)T1_Modulus;

  status = STM32_RSA_Sign_SHA1(&PrivKey_st, T1_message_1, sizeof(T1_message_1), Signature);
  if (status == RSA_SUCCESS)
{
    /* Compare the Signature */
    if (Buffercmp(T1_signature_1, Signature, sizeof(T1_signature_1)) == PASSED)
    {
     /* add application traitment in case of RSA sign is passed */
  
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
    
    status = STM32_RSA_Verify_SHA1(&PubKey_st, T1_message_1, sizeof(T1_message_1), T1_signature_1);
    if (status == SIGNATURE_VALID)
    {
      /* Signature has been validated */
  
    }
    else
    {
      /* In case signature invalide possible values of status:
      * RSA_ERR_BAD_PARAMETER, RSA_ERR_UNSUPPORTED_HASH, RSA_ERR_BAD_KEY, ERR_DYNAMIC_ALLOCATION_FAILED,
      * RSA_ERR_MODULUS_TOO_SHORT, SIGNATURE_INVALID, ERR_MEMORY_FAIL
      */
      
      Error_Handler();
    }
  
  /* Turn on the green led in case of RSA_Signaure operations are successful*/
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
	while (1)
	{
	}

}

/**
  * @brief  RSA Signature Generation with PKCS#1v1.5
  * @param  P_pPrivKey The RSA private key structure, already initialized
  * @param  P_pInputMessage Input Message to be signed
  * @param  P_MessageSize Size of input message
  * @param  P_pOutput Pointer to output buffer
  * @retval error status: can be RSA_SUCCESS if success or one of
  * RSA_ERR_BAD_PARAMETER, RSA_ERR_UNSUPPORTED_HASH, RSA_ERR_BAD_KEY, ERR_MEMORY_FAIL
  * RSA_ERR_MODULUS_TOO_SHORT
*/
int32_t STM32_RSA_Sign_SHA1(RSAprivKey_stt * P_pPrivKey, const uint8_t * P_pInputMessage, int32_t P_MessageSize, uint8_t *P_pOutput)
{
  /* The SHA1 context */
  SHA1ctx_stt SHA1ctx_st;
  /* structure that will contain the preallocated buffer */
  membuf_stt mb_st;
  /* Buffer that will contain the SHA-1 digest of the message */
  uint8_t Digest[CRL_SHA1_SIZE];
  int32_t status = HASH_SUCCESS ;
  int32_t outputSize;

  /* Initialize the membuf_st that must be passed to the ECC functions */
  mb_st.mSize = sizeof(preallocated_buffer);
  mb_st.mUsed = 0;
  mb_st.pmBuf = preallocated_buffer;

  /* Initialize it the SHA-1 Context */
  /* Default Flags */
  SHA1ctx_st.mFlags = E_HASH_DEFAULT;
  /* 20 byte of output */
  SHA1ctx_st.mTagSize = CRL_SHA1_SIZE;
  /* Init SHA-1 */
  status = SHA1_Init(&SHA1ctx_st);
  if (status == HASH_SUCCESS)
  {
    /* Process the message with SHA-1 */
    status = SHA1_Append(&SHA1ctx_st, P_pInputMessage, P_MessageSize);
    if (status == HASH_SUCCESS)
    {
      /* Output the Digest  */
      status = SHA1_Finish(&SHA1ctx_st, Digest, &outputSize);
      if (status == HASH_SUCCESS)
      {
        /* Sign with RSA */
        status = RSA_PKCS1v15_Sign(P_pPrivKey, Digest, E_SHA1, P_pOutput, &mb_st);
      }
    }
  }
  return (status);
}

/**
  * @brief  RSA Signature Verification with PKCS#1v1.5
  * @param  P_pPubKey The RSA public key structure, already initialized
  * @param  P_pInputMessage Input Message
  * @param  P_MessageSize Size of input message
  * @param  P_pSignature Signature that will be checked
  * @retval error status: can be RSA_SUCCESS if success or one of
  * RSA_ERR_BAD_PARAMETER, RSA_ERR_UNSUPPORTED_HASH, RSA_ERR_BAD_KEY, ERR_MEMORY_FAIL
  * RSA_ERR_MODULUS_TOO_SHORT
*/
int32_t STM32_RSA_Verify_SHA1(RSApubKey_stt *P_pPubKey,
                        const uint8_t *P_pInputMessage,
                        int32_t P_MessageSize,
                        const uint8_t *P_pSignature)
{
  /* The SHA1 context */
  SHA1ctx_stt SHA1ctx_st;
  /* structure that will contain the preallocated buffer */
  membuf_stt mb_st;
  /* Buffer that will contain the SHA-1 digest of the message */
  uint8_t Digest[CRL_SHA1_SIZE];
  int32_t status = HASH_SUCCESS;
  int32_t outputSize;

  /* Initialize the membuf_st that must be passed to the ECC functions */
  mb_st.mSize = sizeof(preallocated_buffer);
  mb_st.mUsed = 0;
  mb_st.pmBuf = preallocated_buffer;

  /* Initialize it the SHA-1 Context */
  /* Default Flags */
  SHA1ctx_st.mFlags = E_HASH_DEFAULT;
  /* 20 byte of output */
  SHA1ctx_st.mTagSize = CRL_SHA1_SIZE;
  /* Init SHA-1 */
  status = SHA1_Init(&SHA1ctx_st);
  if (status == HASH_SUCCESS)
  {
    /* Process the message with SHA-1 */
    status = SHA1_Append(&SHA1ctx_st, P_pInputMessage, P_MessageSize);
    if (status == HASH_SUCCESS)
    {
      /* Output the Digest  */
      status = SHA1_Finish(&SHA1ctx_st, Digest, &outputSize);
      if (status == HASH_SUCCESS)
      {
        /* Sign with RSA */
        status = RSA_PKCS1v15_Verify(P_pPubKey, Digest, E_SHA1, P_pSignature, &mb_st);
      }
    }
  }
  return (status);
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
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 120000000
  *            HCLK(Hz)                       = 120000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 240
  *            PLL_P                          = 2
  *            PLL_Q                          = 5
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3);
}

/**
  * @brief  Configures the green led.
  * @param  None
  * @retval None
  */
static void Led_Config(void)
{
    /* -1- Enable each GPIO Clock (to be able to program the configuration registers) */
  __GPIOG_CLK_ENABLE();

  /* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct); 
  
}

/**
  * @brief  Toggles the green led three times.
  * @param[in]  toggle_delay : toggle frequency
  * @retval None
  */
static void Led_Toggle(uint32_t toggle_delay)
{
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);      
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
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
  Led_Toggle(250);
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
