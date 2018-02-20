/**
  ******************************************************************************
  * @file    Examples_Crypto/Src/example_aes256bits_xts.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   AES-256 XTS example
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "example_aes256bits_xts.h"

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t PlainText_AES256bitsXTS[] =
  {
    0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
    0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
  };
const uint8_t Key_AES256bitsXTS[] =
  {
    0xff, 0xfe, 0xfd, 0xfc, 0xfb, 0xfa, 0xf9, 0xf8, 0xf7, 0xf6, 0xf5, 0xf4, 0xf3, 0xf2, 0xf1, 0xf0,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
  };
const uint8_t SequenceNumber_AES256bitsXTS[] =
  {
    0x33, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };
const uint8_t CipherText_AES256bitsXTS[] =
  {
    0xaf, 0x85, 0x33, 0x6b, 0x59, 0x7a, 0xfc, 0x1a, 0x90, 0x0b, 0x2e, 0xb2, 0x1e, 0xc9, 0x49, 0xd2,
    0x92, 0xdf, 0x4c, 0x04, 0x7e, 0x0b, 0x21, 0x53, 0x21, 0x86, 0xa5, 0x97, 0x1a, 0x22, 0x7a, 0x89,
  };

int32_t check_AES256bitsXTS; /* check whether obtained ciphertext during encryption
  * and obtained plaintext during decryption are equal
  * to expected vectors */

uint8_t temp_AES256bitsXTS[512]; /* temporary buffer to store result */

/* Private function prototypes -----------------------------------------------*/

static int32_t STM32_AES_XTS_Encrypt(const uint8_t *InputMessage,
                                     uint32_t   InputMessageLength,
                                     const uint8_t *AES_Key,
                                     uint32_t   KeyLength,
                                     const uint8_t *Tweak,
                                     uint8_t   *OutputMessage);

static int32_t STM32_AES_XTS_Decrypt(const uint8_t *InputMessage,
                                     uint32_t   InputMessageLength,
                                     const uint8_t *AES_Key,
                                     uint32_t   KeyLength,
                                     const uint8_t *Tweak,
                                     uint8_t   *OutputMessage);

TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int ExampleAES256bitsXTS(void)
{

  int32_t status = AES_SUCCESS;
  int32_t example_status = 0;

  /* Encrypt DATA with AES in XTS mode */
  status = STM32_AES_XTS_Encrypt(PlainText_AES256bitsXTS, sizeof(PlainText_AES256bitsXTS), Key_AES256bitsXTS, CRL_AES128_KEY, SequenceNumber_AES256bitsXTS, temp_AES256bitsXTS);

  if (status ==  AES_SUCCESS)
  {
    /* do a memory compare for check accordance between calculated ciphertext
    * and expected ciphertext */
    if (Buffercmp(CipherText_AES256bitsXTS, temp_AES256bitsXTS, CRL_AES_BLOCK) == PASSED)
    {
    }
    else
    {
      example_status = 0x000A;
    }
  }
  else
  {
    example_status = 0x000A;
  }

  /* Decrypt DATA with AES in XTS mode */
  status = STM32_AES_XTS_Decrypt(CipherText_AES256bitsXTS, sizeof(CipherText_AES256bitsXTS), Key_AES256bitsXTS,
                                 CRL_AES128_KEY, SequenceNumber_AES256bitsXTS, temp_AES256bitsXTS);

  if (status == AES_SUCCESS)
  {
    /* do a memory compare for check accordance between calculated plaintext
    * and expected plaintext */
    if (Buffercmp(PlainText_AES256bitsXTS, temp_AES256bitsXTS, CRL_AES_BLOCK) == PASSED)
    {
    }
    else
    {
      example_status = 0x000A;
    }

  }
  else
  {
    example_status = 0x000A;
  }
  return(example_status);
}

/**
  * @brief  AES-128-XTS Encryption
  * @param  InputMessage: pointer to input message to be encrypted
  * @param  InputMessageLength: input data message length in byte
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  Tweak: Initialization vector
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_AES_XTS_Encrypt(const uint8_t *InputMessage,
                              uint32_t   InputMessageLength,
                              const uint8_t *AES_Key,
                              uint32_t   KeyLength,
                              const uint8_t *Tweak,
                              uint8_t   *OutputMessage)
{
  /* AES context, error status and output length */
  AccHw_AESXTSctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT ;
  /* Set the key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the Tweak size in AES status */
  AESctx.mTweakSize = CRL_AES_BLOCK;
  /* Initialize the operation, by passing key and Tweak */
  error_status = AccHw_AES_XTS_Encrypt_Init(&AESctx, AES_Key, Tweak);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Encrypt Data in XTS mode */
    error_status = AccHw_AES_XTS_Encrypt_Append(&AESctx, InputMessage,
                   InputMessageLength, OutputMessage, &outputLength);

    /* check for encryption errors in XTS mode */
    if (error_status == AES_SUCCESS)
    {
      /* Finalize data */
      error_status = AccHw_AES_XTS_Encrypt_Finish(&AESctx, OutputMessage,
                     &outputLength);
    }
  }

  return error_status;
}


/**
  * @brief  AES-128-XTS Decryption
  * @param  InputMessage: pointer to input message to be decrypted
  * @param  InputMessageLength: input data message length in byte
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  Tweak: Initialization vector
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_AES_XTS_Decrypt(const uint8_t *InputMessage,
                              uint32_t   InputMessageLength,
                              const uint8_t *AES_Key,
                              uint32_t   KeyLength,
                              const uint8_t *Tweak,
                              uint8_t   *OutputMessage)
{
  /* AES context, error status and output length */
  AccHw_AESXTSctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT;
  /* Set key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the Tweak size in AES status */
  AESctx.mTweakSize = CRL_AES_BLOCK;
  /* Initialize the operation, by passing the key and Tweak */
  error_status = AccHw_AES_XTS_Decrypt_Init(&AESctx, AES_Key, Tweak);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Decrypt Data in XTS mode */
    error_status = AccHw_AES_XTS_Decrypt_Append(&AESctx, InputMessage,
                   InputMessageLength, OutputMessage, &outputLength);

    /* check for decryption errors in XTS mode */
    if (error_status == AES_SUCCESS)
    {
      /* Finalize data */
      error_status = AccHw_AES_XTS_Decrypt_Finish(&AESctx, OutputMessage,
                     &outputLength);
    }
  }

  return error_status;
}

/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/


