/**
  ******************************************************************************
  * @file    Examples_Crypto/Src/example_aes128bits_cmac.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   AES-128 CMAC Example
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
#include "example_aes128bits_cmac.h"

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PLAINTEXT_LENGTH_AES128bitsCMAC 16
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t Plaintext_AES128bitsCMAC [PLAINTEXT_LENGTH_AES128bitsCMAC] =
  {
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
  };

/* Key to be used for AES encryption/decryption */
const uint8_t key_AES128bitsCMAC[CRL_AES128_KEY] =
  {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
  };

/* In encryption we expect this vector as result */
const uint8_t expectedTags_AES128bitsCMAC[CRL_AES_BLOCK] =
  {
    0x07, 0x0a, 0x16, 0xb4, 0x6b, 0x4d, 0x41, 0x44,
    0xf7, 0x9b, 0xdd, 0x9d, 0xd0, 0x4a, 0x28, 0x7c
  };

uint8_t OutputMessage_AES128bitsCMAC[CRL_AES_BLOCK];



/* Private function prototypes -----------------------------------------------*/


static int32_t STM32_AES_CMAC_Encrypt(const uint8_t *InputMessage,
                                      uint32_t   InputMessageLength,
                                      const uint8_t *AES_Key,
                                      uint32_t   KeyLength,
                                      uint32_t   TagSize,
                                      uint8_t   *OutputTag);

static int32_t STM32_AES_CMAC_Decrypt(const uint8_t *InputMessage,
                                      uint32_t   InputMessageLength,
                                      const uint8_t *AES_Key,
                                      uint32_t   KeyLength,
                                      const uint8_t *tag,
                                      uint32_t   TagSize);

TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int ExampleAES128bitsCMAC(void)
{

  int32_t status = AES_SUCCESS;
  int32_t example_status = 0;
  /* Encrypt DATA with AES in CMAC mode */
  status = STM32_AES_CMAC_Encrypt(Plaintext_AES128bitsCMAC, PLAINTEXT_LENGTH_AES128bitsCMAC, key_AES128bitsCMAC, CRL_AES128_KEY, CRL_AES_BLOCK, OutputMessage_AES128bitsCMAC);

  if (status == AES_SUCCESS)
  {
    if (Buffercmp(expectedTags_AES128bitsCMAC, OutputMessage_AES128bitsCMAC, CRL_AES_BLOCK) == PASSED)
    {
      /* add application traitment in case of AES CMAC encryption is passed */
    }
    else
    {

      example_status = 0x0003;

    }

  }

  else
  {
    /* In case of encryption/decryption not success the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION, AES_ERR_BAD_INPUT_SIZE
     */

    example_status = 0x0003;

  }

  /* Decrypt DATA with AES in CMAC mode */
  status = STM32_AES_CMAC_Decrypt(Plaintext_AES128bitsCMAC, PLAINTEXT_LENGTH_AES128bitsCMAC, key_AES128bitsCMAC, CRL_AES128_KEY, OutputMessage_AES128bitsCMAC, CRL_AES_BLOCK);
  if (status == AUTHENTICATION_SUCCESSFUL)
  {
    /* Add application traitment in case of AES CMAC authentication is successful */
  }
  else
  {
    /* In case of AES CMAC authentication is failed possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION, AES_ERR_BAD_INPUT_SIZE,
     * AUTHENTICATION_FAILED
     */

    example_status = 0x0003;

  }
  return(example_status);
}

/**
  * @brief  AES CMAC Encryption
  * @param  InputMessage: pointer to input message to be encrypted
  * @param  InputMessageLength: input data message length in byte
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  TagSize: length of generated tag
  * @param  OutputTag: generated tag
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
static int32_t STM32_AES_CMAC_Encrypt(const uint8_t *InputMessage,
                                      uint32_t   InputMessageLength,
                                      const uint8_t *AES_Key,
                                      uint32_t   KeyLength,
                                      uint32_t   TagSize,
                                      uint8_t   *OutputTag)
{
  /* AES context, error status and output length */
  AccHw_AESCMACctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT;
  AESctx.mFlags |= AccHw_E_SK_FINAL_APPEND;

  /* Set the key */
  AESctx.pmKey = AES_Key;
  /* Set the key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the size of generated tag */
  AESctx.mTagSize = TagSize;
  /* Initialize the operation, by passing the context */
  error_status = AccHw_AES_CMAC_Encrypt_Init(&AESctx);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Encrypt Data in CMAC mode */
    error_status = AccHw_AES_CMAC_Encrypt_Append(&AESctx, InputMessage,
                   InputMessageLength);

    /* check for encryption errors in CMAC mode */
    if (error_status == AES_SUCCESS)
    {
      /* Finalize data */
      error_status = AccHw_AES_CMAC_Encrypt_Finish(&AESctx, OutputTag,
                     &outputLength);
    }
  }

  return error_status;
}


/**
  * @brief  AES CMAC Decryption
  * @param  InputMessage: pointer to input message to be decrypted
  * @param  InputMessageLength: input data message length in byte
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  tag: associated input message tag
  * @param  TagSize: length of tag
  * @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER, AES_ERR_BAD_INPUT_SIZE, AUTHENTICATION_FAILED if error occured.
  */
static int32_t STM32_AES_CMAC_Decrypt(const uint8_t *InputMessage,
                                      uint32_t   InputMessageLength,
                                      const uint8_t *AES_Key,
                                      uint32_t   KeyLength,
                                      const uint8_t *tag,
                                      uint32_t   TagSize)
{
  /* AES context, error status and output length */
  AccHw_AESCMACctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT;
  AESctx.mFlags |= AccHw_E_SK_FINAL_APPEND;
  /* Set the key */
  AESctx.pmKey = AES_Key;
  /* Set key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the verification tag */
  AESctx.pmTag = tag;
  /* Set the size of generated tag */
  AESctx.mTagSize = TagSize;
  /* Initialize the operation */
  error_status = AccHw_AES_CMAC_Decrypt_Init(&AESctx);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Decrypt Data in CMAC mode */
    error_status = AccHw_AES_CMAC_Decrypt_Append(&AESctx, InputMessage,
                   InputMessageLength);

    /* check for decryption errors in CMAC mode */
    if (error_status == AES_SUCCESS)
    {
      /* Finalize data */
      error_status = AccHw_AES_CMAC_Decrypt_Finish(&AESctx, NULL,
                     &outputLength);
    }
  }

  return error_status;
}

/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/



