
/**
  ******************************************************************************
  * @file    RSA/Enc_Dec/Src/main.c
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

uint8_t preallocated_buffer[4096]; /* buffer required for internal allocation of memory */

/******************************************************************************/
/************************** RSA 2048 Test Vector  ****************************/
/******************************************************************************/
const uint8_t Message[] =
  {
    0xEB, 0x39, 0x49, 0x2F, 0x73, 0xED, 0x5E, 0x1C, 0x5E,
    0x45, 0xAF, 0xB5, 0x7F, 0xC1, 0xD6, 0xFE,
  };

const uint8_t Modulus[] =
  {
    0xB5, 0x05, 0xFC, 0xA2, 0xCA, 0x33, 0x48, 0xD5, 0x9B, 0xF3, 0x00, 0x5F, 0x7C, 0xFD, 0xC4, 0x56, 0x4C, 0x25, 0x07,
    0x67, 0xE9, 0xC9, 0x40, 0x24, 0x69, 0x79, 0x61, 0x41, 0x98, 0x1D, 0x6A, 0xF5, 0x6A, 0x1A, 0x84, 0xB5, 0xA9, 0xA4,
    0xB3, 0x33, 0x5F, 0xA0, 0x25, 0xA8, 0x7F, 0x4B, 0x4D, 0x0B, 0xA0, 0x60, 0xB8, 0xBE, 0xF9, 0x34, 0x0B, 0xE4, 0x5F,
    0xDB, 0x05, 0x76, 0x20, 0x38, 0x90, 0xA0, 0x71, 0xCE, 0xE9, 0xB0, 0x59, 0x4B, 0x95, 0x12, 0x7B, 0xB4, 0x80, 0xED,
    0xC7, 0x43, 0xBD, 0xCE, 0x27, 0xFD, 0x2B, 0xEC, 0xD0, 0x33, 0x00, 0x24, 0x32, 0x9E, 0xED, 0xAF, 0x3C, 0x1A, 0x12,
    0x13, 0xB2, 0x8D, 0x32, 0xD1, 0x83, 0xEA, 0xF4, 0x1A, 0x9A, 0x46, 0x3A, 0x08, 0x8C, 0xD4, 0xBA, 0x67, 0xDA, 0x91,
    0x26, 0x79, 0x49, 0xBA, 0xAA, 0x54, 0x26, 0x56, 0x03, 0x76, 0xA7, 0x70, 0x58, 0x9E, 0xA8, 0x37, 0x60, 0xB8, 0xC5,
    0xC1, 0xF9, 0xDD, 0x54, 0x18, 0x4D, 0x7F, 0x91, 0xCC, 0x0A, 0xBB, 0x08, 0xC3, 0x05, 0x3C, 0x04, 0x8B, 0xDC, 0xD0,
    0xE9, 0x7A, 0x16, 0x28, 0x53, 0x0D, 0x20, 0x74, 0x0B, 0xD1, 0xD5, 0x0F, 0x16, 0x48, 0x06, 0xB2, 0x5F, 0x1E, 0x0A,
    0xC9, 0xDD, 0x9E, 0x17, 0xE5, 0x00, 0xD6, 0xB9, 0x2D, 0x40, 0xE6, 0xA8, 0xDC, 0x7F, 0xAE, 0x5B, 0x6B, 0x7F, 0x76,
    0x27, 0xF7, 0xED, 0x0C, 0xF5, 0x1D, 0xC1, 0x6F, 0xA4, 0x00, 0x45, 0x8A, 0x22, 0x09, 0x84, 0xD1, 0xB4, 0xB1, 0x18,
    0x44, 0x76, 0xC9, 0xD6, 0xA7, 0xC6, 0x72, 0x5B, 0x43, 0x48, 0x91, 0x85, 0xBB, 0x7F, 0xB1, 0x44, 0x73, 0x45, 0xF5,
    0x5A, 0x7E, 0x72, 0x3D, 0xA1, 0x8C, 0x43, 0xAE, 0x83, 0xD9, 0xB4, 0xCB, 0x1D, 0xDC, 0x26, 0x3F, 0x7F, 0x1E, 0xFE,
    0x83, 0x6C, 0x9A, 0x0D, 0xEA, 0xE1, 0x94, 0x55, 0xF1
  };

const uint8_t PublicExponent[] =
  {
    0x01, 0x00, 0x01
  };

const uint8_t PrivateExponent[] =
  {
    0x06, 0xBE, 0x0F, 0x57, 0xDC, 0xE2, 0x26, 0x1F, 0x56, 0xAC, 0xA9, 0x61, 0xE5, 0x1C, 0xEA, 0x98, 0x30, 0x43,
    0xDC, 0xCF, 0xC1, 0x04, 0x6E, 0xF0, 0x2C, 0x41, 0x8A, 0x1E, 0xD0, 0x54, 0xA0, 0x2C, 0x3D, 0xE4, 0x78, 0xF6,
    0xEF, 0x37, 0xA4, 0x39, 0x10, 0xA1, 0xBD, 0x65, 0x56, 0x40, 0x6E, 0xC1, 0x35, 0x1B, 0x05, 0x26, 0x8F, 0xCF,
    0xA1, 0x75, 0xC3, 0x20, 0x3C, 0x46, 0xD7, 0x12, 0x64, 0x48, 0xA5, 0x94, 0x88, 0x5D, 0xBA, 0x25, 0xB7, 0x8A,
    0xB5, 0xB2, 0xD6, 0x6E, 0x84, 0xD2, 0x80, 0x1A, 0x52, 0xA0, 0xFA, 0x66, 0xDA, 0xA6, 0x5B, 0xA5, 0xFD, 0x80,
    0xAF, 0xE7, 0xAB, 0xFC, 0x68, 0x99, 0xF5, 0x37, 0x8F, 0x22, 0x00, 0xA0, 0xDA, 0xB0, 0xB6, 0xF8, 0x50, 0xA7,
    0x0A, 0xDF, 0xCD, 0x85, 0x9A, 0xBD, 0x77, 0x4A, 0x63, 0x35, 0xA1, 0xAC, 0x7A, 0xB5, 0x0F, 0x71, 0xF6, 0xF0,
    0x97, 0x4C, 0x59, 0x7B, 0x53, 0xD1, 0x71, 0x98, 0x3D, 0xFD, 0x1E, 0xE3, 0x81, 0x39, 0x0A, 0xD7, 0x8D, 0x2B,
    0x82, 0x12, 0xCC, 0x9D, 0xF9, 0xC7, 0xEE, 0xAC, 0x90, 0x65, 0xC7, 0x01, 0xBC, 0x58, 0x52, 0xEF, 0x02, 0x74,
    0x04, 0x70, 0x87, 0xA0, 0x55, 0x42, 0xAF, 0x89, 0xF2, 0x9B, 0x22, 0xFB, 0x14, 0x5D, 0xF3, 0x26, 0x55, 0xD3,
    0x2F, 0x04, 0xF0, 0x92, 0xC3, 0x1F, 0x45, 0x7B, 0x82, 0xE9, 0x0F, 0xF1, 0x8C, 0xA2, 0x32, 0xA9, 0x56, 0x65,
    0xC8, 0x2E, 0xA1, 0xA5, 0x95, 0x16, 0xBF, 0xC5, 0xDB, 0x78, 0xF8, 0x83, 0xDB, 0xFD, 0x04, 0xD8, 0x29, 0x92,
    0x58, 0xD4, 0xE3, 0x8D, 0xD2, 0x66, 0xB6, 0xDB, 0x4A, 0xC0, 0x4B, 0xE0, 0xF4, 0xF8, 0x02, 0x9B, 0xE8, 0xD3,
    0x41, 0xD9, 0x4A, 0x32, 0x3C, 0x75, 0x43, 0x19, 0xA8, 0x1F, 0x41, 0x90, 0x92, 0x1E, 0xF7, 0x18, 0xE8, 0x0C,
    0x55, 0xC2, 0x98, 0x01
  };

const uint8_t EncryptedMessage[] =
  {
    0x45, 0x4E, 0x4F, 0xE2, 0x40, 0xBA, 0xF4, 0xD9, 0xED, 0xEA, 0x65, 0x79, 0xB4, 0xCF, 0x8D, 0xE4, 0x41, 0x3E,
    0x56, 0x78, 0xAC, 0x5C, 0x47, 0x3F, 0x22, 0x1F, 0x16, 0xCB, 0xBC, 0xFC, 0x9E, 0xB7, 0x31, 0x96, 0x37, 0x83,
    0x3A, 0xFE, 0x46, 0x51, 0x75, 0x27, 0xE6, 0x6F, 0x66, 0x3E, 0xC9, 0xB9, 0xB4, 0x7C, 0x1E, 0xB8, 0xF3, 0xB1,
    0xBA, 0x87, 0xF6, 0x12, 0x0F, 0xCA, 0xD7, 0x63, 0xC0, 0x8A, 0x86, 0xE3, 0xF6, 0x1C, 0x61, 0x5A, 0x01, 0xDD,
    0x3F, 0x97, 0xC9, 0x2A, 0x55, 0x0B, 0x46, 0x25, 0xE6, 0xAE, 0x87, 0x72, 0x08, 0xA8, 0x49, 0x10, 0xED, 0xE0,
    0xAB, 0xD5, 0x73, 0xE4, 0xF2, 0x74, 0x01, 0xCE, 0x7B, 0xAA, 0xD2, 0xC2, 0x86, 0xC1, 0x64, 0x8D, 0xD7, 0x63,
    0xA4, 0x7C, 0xDC, 0xA8, 0x21, 0x93, 0x12, 0x0D, 0xC3, 0x8D, 0xD9, 0x59, 0x97, 0x80, 0xC1, 0xC7, 0x8F, 0x0D,
    0x3B, 0x16, 0x3C, 0xE2, 0x2F, 0xB4, 0x52, 0x8C, 0x0C, 0x15, 0xE5, 0x98, 0x81, 0xEF, 0xB4, 0xD3, 0x5E, 0x72,
    0xC8, 0x89, 0x64, 0xBE, 0x54, 0xEC, 0xFB, 0x38, 0x85, 0xB4, 0x62, 0x39, 0xA6, 0xCC, 0xC4, 0x68, 0x0C, 0xDF,
    0xA4, 0x5A, 0x9D, 0x34, 0x31, 0x2A, 0x0C, 0x3B, 0x52, 0xCF, 0x13, 0xF3, 0xE8, 0x5A, 0x0C, 0xEA, 0x41, 0x94,
    0xD5, 0x25, 0xAA, 0xC0, 0x2B, 0xC8, 0xB2, 0x04, 0xA6, 0xCD, 0x26, 0xF6, 0x02, 0x98, 0x89, 0x79, 0x62, 0x76,
    0x76, 0xEF, 0xF4, 0x3C, 0x09, 0x16, 0x4B, 0x1A, 0x9C, 0xCA, 0x4F, 0x42, 0x9A, 0xA2, 0x4B, 0x98, 0xF8, 0xFF,
    0xBE, 0xBF, 0xE4, 0xA0, 0x0F, 0xEB, 0xC1, 0xDB, 0x69, 0x4D, 0x93, 0x16, 0x5F, 0x3D, 0xBF, 0xA1, 0xD8, 0x4D,
    0x05, 0x21, 0xD1, 0xB4, 0xDA, 0x13, 0x4C, 0x27, 0x8E, 0xB2, 0x4F, 0x57, 0x07, 0xCC, 0xA6, 0xA1, 0x0F, 0x52,
    0xD5, 0x72, 0x16, 0x9D
  };

/* String of entropy */
uint8_t entropy_data[32] =
  {
    0x91, 0x20, 0x1a, 0x18, 0x9b, 0x6d, 0x1a, 0xa7,
    0x0e, 0x69, 0x57, 0x6f, 0x36, 0xb6, 0xaa, 0x88,
    0x55, 0xfd, 0x4a, 0x7f, 0x97, 0xe9, 0x72, 0x69,
    0xb6, 0x60, 0x88, 0x78, 0xe1, 0x9c, 0x8c, 0xa5
  };

uint8_t output[2048/8];
int32_t outputSize = 0;


/* Private function prototypes -----------------------------------------------*/

int32_t RSA_Encrypt(RSApubKey_stt *P_pPubKey,
                    const uint8_t *P_pInputMessage,
                    int32_t P_InputSize,
                    uint8_t *P_pOutput);

int32_t RSA_Decrypt(RSAprivKey_stt * P_pPrivKey,
                    const uint8_t * P_pInputMessage,
                    uint8_t *P_pOutput,
                    int32_t *P_OutputSize);
TestStatus Buffercmp(const uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength);

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
  int32_t status = RSA_ERR_GENERIC;
  RSApubKey_stt PubKey_st;
  RSAprivKey_stt PrivKey_st;

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

  /* Testing Encryption and Decryption */
  /* Preparing for Encryption */
  PubKey_st.mExponentSize = sizeof(PublicExponent);
  PubKey_st.mModulusSize = sizeof(Modulus);
  PubKey_st.pmExponent = (uint8_t *) PublicExponent;
  PubKey_st.pmModulus = (uint8_t *)Modulus;

  status = RSA_Encrypt(&PubKey_st, Message, sizeof(Message), output);

  if (status == RSA_SUCCESS)
  {
    /* Now we will test decryption */
    PrivKey_st.mExponentSize = sizeof(PrivateExponent);
    PrivKey_st.mModulusSize = sizeof(Modulus);
    PrivKey_st.pmExponent = (uint8_t *) PrivateExponent;
    PrivKey_st.pmModulus = (uint8_t *) Modulus;
    status = RSA_Decrypt(&PrivKey_st, output, output, &outputSize);

    if (status == RSA_SUCCESS)
    {
      /* Check expected output */
      if ( (Buffercmp(Message, output, sizeof(Message)) == PASSED ) && (outputSize == sizeof(Message)))
      {
        /* add application traitment in case of Encryption/Decryption is passed */
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
    Error_Handler();
  }



  /* Turn on the green led in case of RSA encryption/decryption operations are successful*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}
}

/**
  * @brief  RSA Encryption with PKCS#1v1.5
  * @param  P_pPubKey The RSA public key structure, already initialized
  * @param  P_pInputMessage Input Message to be signed
  * @param  P_MessageSize Size of input message
  * @param  P_pOutput Pointer to output buffer
  * @retval error status: can be RSA_SUCCESS if success or one of
  * RSA_ERR_BAD_PARAMETER, RSA_ERR_MESSAGE_TOO_LONG, RSA_ERR_BAD_OPERATION
*/
int32_t RSA_Encrypt(RSApubKey_stt *P_pPubKey,
                    const uint8_t *P_pInputMessage,
                    int32_t P_InputSize,
                    uint8_t *P_pOutput)
{
  int32_t status = RNG_SUCCESS ;
  RNGstate_stt RNGstate;
  RNGinitInput_stt RNGinit_st;
  RNGinit_st.pmEntropyData = entropy_data;
  RNGinit_st.mEntropyDataSize = sizeof(entropy_data);
  RNGinit_st.mPersDataSize = 0;
  RNGinit_st.mNonceSize = 0;

  status = RNGinit(&RNGinit_st, &RNGstate);
  if (status == RNG_SUCCESS)
  {
    RSAinOut_stt inOut_st;
    membuf_stt mb;

    mb.mSize = sizeof(preallocated_buffer);
    mb.mUsed = 0;
    mb.pmBuf = preallocated_buffer;

    /* Fill the RSAinOut_stt */
    inOut_st.pmInput = P_pInputMessage;
    inOut_st.mInputSize = P_InputSize;
    inOut_st.pmOutput = P_pOutput;

    /* Encrypt the message, this function will write sizeof(modulus) data */
    status = RSA_PKCS1v15_Encrypt(P_pPubKey, &inOut_st, &RNGstate, &mb);
  }
  return(status);
}

/**
  * @brief  RSA Decryption with PKCS#1v1.5
  * @param  P_pPrivKey The RSA private key structure, already initialized
  * @param  P_pInputMessage Input Message to be signed
  * @param  P_MessageSize Size of input message
  * @param  P_pOutput Pointer to output buffer
  * @retval error status: can be RSA_SUCCESS if success or RSA_ERR_GENERIC in case of fail
*/ 
int32_t RSA_Decrypt(RSAprivKey_stt * P_pPrivKey,
                    const uint8_t * P_pInputMessage,
                    uint8_t *P_pOutput,
                    int32_t *P_OutputSize)
{
  int32_t status = RSA_SUCCESS ;
  RSAinOut_stt inOut_st;
  membuf_stt mb;

  mb.mSize = sizeof(preallocated_buffer);
  mb.mUsed = 0;
  mb.pmBuf = preallocated_buffer;

  /* Fill the RSAinOut_stt */
  inOut_st.pmInput = P_pInputMessage;
  inOut_st.mInputSize = P_pPrivKey->mModulusSize;
  inOut_st.pmOutput = P_pOutput;

  /* Encrypt the message, this function will write sizeof(modulus) data */
  status = RSA_PKCS1v15_Decrypt(P_pPrivKey, &inOut_st, P_OutputSize, &mb);
  return(status);
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
