/**
  ******************************************************************************
  * @file    Examples_Crypto/Src/example_aes128bits_ofb.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   AES-128 OFB Example
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
#include "example_aes128bits_ofb.h"

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PLAINTEXT_LENGTH_AES128bitsOFB 16
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t Plaintext_AES128bitsOFB[PLAINTEXT_LENGTH_AES128bitsOFB] =
  {
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
  };

/* Key to be used for AES encryption/decryption */
uint8_t Key_AES128bitsOFB[CRL_AES128_KEY] =
  {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
  };

/* Initialization Vector, used only in non-ECB modes */
uint8_t IV_AES128bitsOFB[CRL_AES_BLOCK] =
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
  };


/* Buffer to store the output data */
uint8_t OutputMessage_AES128bitsOFB[PLAINTEXT_LENGTH_AES128bitsOFB];

/* Size of the output data */
uint32_t OutputMessageLength_AES128bitsOFB = 0;

const uint8_t Expected_Ciphertext_AES128bitsOFB[PLAINTEXT_LENGTH_AES128bitsOFB] =
  {
    0x3b, 0x3f, 0xd9, 0x2e, 0xb7, 0x2d, 0xad, 0x20,
    0x33, 0x34, 0x49, 0xf8, 0xe8, 0x3c, 0xfb, 0x4a
  };


/* Private function prototypes -----------------------------------------------*/
static int32_t STM32_AES_OFB_Encrypt(uint8_t*  InputMessage,
                                     uint32_t  InputMessageLength,
                                     uint8_t  *AES128_Key,
                                     uint8_t  *InitializationVector,
                                     uint32_t  IvLength,
                                     uint8_t  *OutputMessage,
                                     uint32_t *OutputMessageLength);

static int32_t STM32_AES_OFB_Decrypt(uint8_t*  InputMessage,
                                     uint32_t  InputMessageLength,
                                     uint8_t  *AES128_Key,
                                     uint8_t  *InitializationVector,
                                     uint32_t  IvLength,
                                     uint8_t  *OutputMessage,
                                     uint32_t *OutputMessageLength);

TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int ExampleAES128bitsOFB(void)
{
  int32_t status = AES_SUCCESS;
  int32_t example_status = 0;

  /* Encrypt DATA with AES in OFB mode */
  status = STM32_AES_OFB_Encrypt( (uint8_t *) Plaintext_AES128bitsOFB, PLAINTEXT_LENGTH_AES128bitsOFB, Key_AES128bitsOFB, IV_AES128bitsOFB, sizeof(IV_AES128bitsOFB), OutputMessage_AES128bitsOFB,
                                  &OutputMessageLength_AES128bitsOFB);
  if (status == AES_SUCCESS)
  {
    if (Buffercmp(Expected_Ciphertext_AES128bitsOFB, OutputMessage_AES128bitsOFB, PLAINTEXT_LENGTH_AES128bitsOFB) == PASSED)
    {
      /* add application traitment in case of AES OFB encryption is passed */

    }
    else
    {

      example_status = 0x0007;

    }
  }
  else
  {
    /* In case of encryption not success the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
     */

    example_status = 0x0007;

  }

  /* Decrypt DATA with AES in OFB mode */
  status = STM32_AES_OFB_Decrypt( (uint8_t *) Expected_Ciphertext_AES128bitsOFB, PLAINTEXT_LENGTH_AES128bitsOFB, Key_AES128bitsOFB, IV_AES128bitsOFB, sizeof(IV_AES128bitsOFB), OutputMessage_AES128bitsOFB,
                                  &OutputMessageLength_AES128bitsOFB);
  if (status == AES_SUCCESS)
  {
    if (Buffercmp(Plaintext_AES128bitsOFB, OutputMessage_AES128bitsOFB, PLAINTEXT_LENGTH_AES128bitsOFB) == PASSED)
    {
      /* add application traitment in case of AES OFB decryption is passed */

    }
    else
    {

      example_status = 0x0007;

    }
  }
  else
  {
    /* In case of decryption not success the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
     */

    example_status = 0x0007;

  }
  return(example_status);
}

/**
  * @brief  AES OFB Encryption example.
  * @param  InputMessage: pointer to input message to be encrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
  *         if error occured.
  */
static int32_t STM32_AES_OFB_Encrypt(uint8_t* InputMessage,
                                     uint32_t InputMessageLength,
                                     uint8_t  *AES128_Key,
                                     uint8_t  *InitializationVector,
                                     uint32_t  IvLength,
                                     uint8_t  *OutputMessage,
                                     uint32_t *OutputMessageLength)
{
  AccHw_AESECBctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = 16;

  /* Set iv size field to IvLength*/
  AESctx.mIvSize = IvLength;

  /* Initialize the operation, by passing the key.*/
  error_status = AccHw_AES_OFB_Encrypt_Init(&AESctx, AES128_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Encrypt Data */
    error_status = AccHw_AES_OFB_Encrypt_Append(&AESctx,
                   InputMessage,
                   InputMessageLength,
                   OutputMessage,
                   &outputLength);

    if (error_status == AES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = AccHw_AES_OFB_Encrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}


/**
  * @brief  AES OFB Decryption example.
  * @param  InputMessage: pointer to input message to be decrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @param  OutputMessageLength: pointer to decrypted message length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
  *         if error occured.
  */
static int32_t STM32_AES_OFB_Decrypt(uint8_t* InputMessage,
                                     uint32_t InputMessageLength,
                                     uint8_t  *AES128_Key,
                                     uint8_t  *InitializationVector,
                                     uint32_t  IvLength,
                                     uint8_t  *OutputMessage,
                                     uint32_t *OutputMessageLength)
{
  AccHw_AESECBctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = 16;

  /* Set iv size field to IvLength*/
  AESctx.mIvSize = IvLength;

  /* Initialize the operation, by passing the key. */
  error_status = AccHw_AES_OFB_Decrypt_Init(&AESctx, AES128_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Decrypt Data */
    error_status = AccHw_AES_OFB_Decrypt_Append(&AESctx,
                   InputMessage,
                   InputMessageLength,
                   OutputMessage,
                   &outputLength);
    if (error_status == AES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = AccHw_AES_OFB_Decrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}

/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/
