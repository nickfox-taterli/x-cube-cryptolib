/**
  ******************************************************************************
  * @file    Examples_Crypto/Src/example_aes128bits_gcm.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   AES-128 GCM Example
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
#include "example_aes128bits_gcm.h"

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Size of GCM Tag, fixed */
#define GCM_TAG_SIZE          16
/* length of plain and cipher text test vector of example  */
#define PLAIN_CIPHER_TEXT_LENGTH_AES128bitsGCM 60

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* key */
const uint8_t key_AES128bitsGCM [CRL_AES128_KEY] =
  {
    0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c, 0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08
  };
/*  IV */
const uint8_t IV_AES128bitsGCM [] =
  {
    0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad, 0xde, 0xca, 0xf8, 0x88
  };
/* header */
const uint8_t header_AES128bitsGCM[] =
  {
    0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
    0xab, 0xad, 0xda, 0xd2
  };
/* Expected tag */
const uint8_t expectedTag_AES128bitsGCM[GCM_TAG_SIZE] =
  {
    0x5b, 0xc9, 0x4f, 0xbc, 0x32, 0x21, 0xa5, 0xdb, 0x94, 0xfa, 0xe9, 0x5a, 0xe7, 0x12, 0x1a, 0x47
  };
/* Plaintext */
const uint8_t Plaintext_AES128bitsGCM[] =
  {
    0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5, 0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
    0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda, 0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
    0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53, 0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
    0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57, 0xba, 0x63, 0x7b, 0x39
  };
/* In encryption we expect this vector as result */
const uint8_t expectedCipherText_AES128bitsGCM[PLAIN_CIPHER_TEXT_LENGTH_AES128bitsGCM] =
  {
    0x42, 0x83, 0x1e, 0xc2, 0x21, 0x77, 0x74, 0x24, 0x4b, 0x72, 0x21, 0xb7, 0x84, 0xd0, 0xd4, 0x9c,
    0xe3, 0xaa, 0x21, 0x2f, 0x2c, 0x02, 0xa4, 0xe0, 0x35, 0xc1, 0x7e, 0x23, 0x29, 0xac, 0xa1, 0x2e,
    0x21, 0xd5, 0x14, 0xb2, 0x54, 0x66, 0x93, 0x1c, 0x7d, 0x8f, 0x6a, 0x5a, 0xac, 0x84, 0xaa, 0x05,
    0x1b, 0xa3, 0x0b, 0x39, 0x6a, 0x0a, 0xac, 0x97, 0x3d, 0x58, 0xe0, 0x91
  };

uint8_t Outputmessage_AES128bitsGCM [64];
uint8_t tag_AES128bitsGCM[GCM_TAG_SIZE];

/* Private function prototypes -----------------------------------------------*/

static int32_t STM32_AES_GCM_Encrypt(const uint8_t *InputMessage,
                                     uint32_t   InputMessageLength,
                                     const uint8_t *AES_Key,
                                     uint32_t   KeyLength,
                                     const uint8_t *IV,
                                     uint32_t   IVSize,
                                     const uint8_t *Header,
                                     uint32_t   HeaderSize,
                                     uint8_t   *Tag,
                                     uint32_t   TagSize,
                                     uint8_t   *OutputMessage);

static int32_t STM32_AES_GCM_Decrypt(const uint8_t *InputMessage,
                                     uint32_t   InputMessageLength,
                                     const uint8_t *AES_Key,
                                     uint32_t   KeyLength,
                                     const uint8_t *IV,
                                     uint32_t   IVSize,
                                     const uint8_t *Tag,
                                     uint32_t   TagSize,
                                     const uint8_t *Header,
                                     uint32_t   HeaderSize,
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
int ExampleAES128bitsGCM(void)
{

  int32_t status = AES_SUCCESS;
  int32_t example_status = 0;

  /* Encrypt data */
  status = STM32_AES_GCM_Encrypt(
             Plaintext_AES128bitsGCM, PLAIN_CIPHER_TEXT_LENGTH_AES128bitsGCM,
             key_AES128bitsGCM, CRL_AES128_KEY,
             IV_AES128bitsGCM, sizeof(IV_AES128bitsGCM),
             header_AES128bitsGCM, sizeof(header_AES128bitsGCM),
             tag_AES128bitsGCM, GCM_TAG_SIZE,
             Outputmessage_AES128bitsGCM);
  if (status ==  AES_SUCCESS)
  {
    if (Buffercmp(expectedCipherText_AES128bitsGCM, Outputmessage_AES128bitsGCM, PLAIN_CIPHER_TEXT_LENGTH_AES128bitsGCM) == PASSED)
    {
      /* add application traitment in case of AES GCM encryption is passed */

    }
    else
    {

      example_status = 0x0005;

    }

    if (Buffercmp(expectedTag_AES128bitsGCM, tag_AES128bitsGCM, GCM_TAG_SIZE) == PASSED)
    {
      /* add application traitment in case of AES GCM encryption is passed */

    }
    else
    {

      example_status = 0x0005;

    }
  }
  else
  {
    /* In case of encryption not success the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
     */

    example_status = 0x0005;

  }





  /* Decrypt data */
  status = STM32_AES_GCM_Decrypt(
             expectedCipherText_AES128bitsGCM, PLAIN_CIPHER_TEXT_LENGTH_AES128bitsGCM,
             key_AES128bitsGCM, CRL_AES128_KEY,
             IV_AES128bitsGCM, sizeof(IV_AES128bitsGCM),
             tag_AES128bitsGCM, GCM_TAG_SIZE,
             header_AES128bitsGCM, sizeof(header_AES128bitsGCM),
             Outputmessage_AES128bitsGCM);


  if (status == AUTHENTICATION_SUCCESSFUL)
  {

    if (Buffercmp(Plaintext_AES128bitsGCM, Outputmessage_AES128bitsGCM, PLAIN_CIPHER_TEXT_LENGTH_AES128bitsGCM) == PASSED)
    {
      /* add application traitment in case of AES GCM encryption is passed */

    }
    else
    {


      example_status = 0x0005;

    }
  }
  else
  {
    /* In case of AES GCM authentication is failed the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION, 
     * AUTHENTICATION_FAILED*/

    example_status = 0x0005;

  }
  return(example_status);
}

/**
  * @brief  AES GCM Encryption
  * @param  InputMessage: payload to encrypt
  * @param  InputMessageLength: length of payload
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  IV: Initialization Vector
  * @param  IVSize: length of IV
  * @param  Header: message header
  * @param  HeaderSize: length of message header
  * @param  Tag: generated tag
  * @param  TagSize: length of generated tag
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_AES_GCM_Encrypt(const uint8_t *InputMessage,
                              uint32_t   InputMessageLength,
                              const uint8_t *AES_Key,
                              uint32_t   KeyLength,
                              const uint8_t *IV,
                              uint32_t   IVSize,
                              const uint8_t *Header,
                              uint32_t   HeaderSize,
                              uint8_t   *Tag,
                              uint32_t   TagSize,
                              uint8_t   *OutputMessage)
{
  /* AES context, error status and output length */
  AccHw_AESGCMctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT;
  /* Set the key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the IV size in AES status */
  AESctx.mIvSize = IVSize;
  /* Set the tag size in AES status */
  AESctx.mTagSize = TagSize;
  /* Initialize the operation, by passing key and IV */
  error_status = AccHw_AES_GCM_Encrypt_Init(&AESctx, AES_Key, IV);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Process Header (data to be authenticated but NOT encrypted) */
    error_status = AccHw_AES_GCM_Header_Append(&AESctx, Header, HeaderSize);

    if (error_status == AES_SUCCESS)
    {
      /* Encrypt Data */
      error_status = AccHw_AES_GCM_Encrypt_Append(&AESctx, InputMessage,
                     InputMessageLength, OutputMessage, &outputLength);

      /* check for encryption errors */
      if (error_status == AES_SUCCESS)
      {
        /* Finalize data and write associated tag */
        error_status = AccHw_AES_GCM_Encrypt_Finish(&AESctx,
                       Tag, &outputLength);
      }
    }
  }

  return error_status;
}


/**
  * @brief  AES GCM Decryption
  * @param  InputMessage: pointer to input message to be decrypted
  * @param  InputMessageLength: input data message length in byte
  * @param  AES_Key: pointer to the AES key to be used in the operation
  * @param  KeyLength: length of the AES key
  * @param  IV: Initialization Vector
  * @param  Tag: tag for authenticate header and payload
  * @param  TagSize: size of tag
  * @param  Header: plain header
  * @param  HeaderSize: size of header
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER, AUTHENTICATION_FAILED if error occured.
  */
int32_t STM32_AES_GCM_Decrypt(const uint8_t *InputMessage,
                              uint32_t   InputMessageLength,
                              const uint8_t *AES_Key,
                              uint32_t   KeyLength,
                              const uint8_t *IV,
                              uint32_t   IVSize,
                              const uint8_t *Tag,
                              uint32_t   TagSize,
                              const uint8_t *Header,
                              uint32_t   HeaderSize,
                              uint8_t   *OutputMessage)
{
  /* AES context, error status and output length */
  AccHw_AESGCMctx_stt AESctx;
  uint32_t error_status = AES_SUCCESS;
  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT;
  /* Set the key size in AES status */
  AESctx.mKeySize = KeyLength;
  /* Set the IV size in AES status */
  AESctx.mIvSize = IVSize;
  /* Set the tag size in AES status */
  AESctx.mTagSize = TagSize;
  /* Set the tag in AES status */
  AESctx.pmTag = Tag;

  /* Initialize the operation, by passing the key and IV */
  error_status = AccHw_AES_GCM_Decrypt_Init(&AESctx, AES_Key, IV);

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Process header */
    error_status = AccHw_AES_GCM_Header_Append(&AESctx, Header, HeaderSize);

    if (error_status == AES_SUCCESS)
    {
      /* Decrypt Data */
      error_status = AccHw_AES_GCM_Decrypt_Append(&AESctx, InputMessage,
                     InputMessageLength, OutputMessage, &outputLength);

      /* Authenticate */
      if (error_status == AES_SUCCESS)
      {
        /* Finalize data */
        error_status = AccHw_AES_GCM_Decrypt_Finish(&AESctx, NULL, &outputLength);
      }
    }
  }

  return error_status;
}

/**
  * @}
  */
/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
