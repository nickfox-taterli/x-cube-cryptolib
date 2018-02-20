/**
  ******************************************************************************
  * @file    Examples_Crypto/Src/example_aes128bits_ccm.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   AES-128 CCM Example
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
#include "example_aes128bits_ccm.h"

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TAG_LENGTH_AES128bitsCCM 4
#define PLAINTEXT_LENGTH_AES128bitsCCM 4
#define CIPHER_TEXT_LENGTH_AES128bitsCCM PLAINTEXT_LENGTH_AES128bitsCCM + TAG_LENGTH_AES128bitsCCM

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Header message, will be authenticated but not encrypted */
const uint8_t HeaderMessage_AES128bitsCCM[] =
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
  };

uint32_t HeaderLength_AES128bitsCCM = sizeof (HeaderMessage_AES128bitsCCM) ;

/* string length only, without '\0' end of string marker */


/* Payload message, will be authenticated and encrypted */
const uint8_t Plaintext_AES128bitsCCM[] =
  {
    0x20, 0x21, 0x22, 0x23
  };

/* string length only, without '\0' end of string marker */
uint32_t InputLength_AES128bitsCCM = sizeof (Plaintext_AES128bitsCCM) ;

/* Key to be used for AES encryption/decryption */
uint8_t Key_AES128bitsCCM[CRL_AES128_KEY] =
  {
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f
  };

/* Initialization Vector, used only in non-ECB modes */
uint8_t IV_AES128bitsCCM[] =
  {
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16
  };

/* NIST example 1 ciphertext vector: in encryption we expect this vector as result */
const uint8_t Expected_Ciphertext_AES128bitsCCM[CIPHER_TEXT_LENGTH_AES128bitsCCM] =
  {
    0x71, 0x62, 0x01, 0x5b, 0x4d, 0xac, 0x25, 0x5d
  };

/* Buffer to store the output data and the authentication TAG */
uint8_t encrypt_OutputMessage_AES128bitsCCM[64];
uint8_t decrypt_OutputMessage_AES128bitsCCM[64];
int32_t encrypt_OutputMessageLength_AES128bitsCCM = 0;
int32_t decrypt_OutputMessageLength_AES128bitsCCM = 0;
int32_t AuthenticationTAGLength_AES128bitsCCM = 0;
uint8_t tag_AES128bitsCCM[64];
/* Private function prototypes -----------------------------------------------*/
static int32_t STM32_AES_CCM_Encrypt(uint8_t*  HeaderMessage,
                                     uint32_t  HeaderMessageLength,
                                     uint8_t*  InputMessage,
                                     uint32_t  InputMessageLength,
                                     uint8_t  *AES128_Key,
                                     uint8_t  *InitializationVector,
                                     uint32_t  IvLength,
                                     uint8_t  *OutputMessage,
                                     int32_t *OutputMessageLength,
                                     int32_t *AuthenticationTAGLength
                                    );


static int32_t STM32_AES_CCM_Decrypt(uint8_t*  HeaderMessage,
                                     uint32_t  HeaderMessageLength,
                                     uint8_t*  InputMessage,
                                     uint32_t  InputMessageLength,
                                     uint8_t  *AES128_Key,
                                     uint8_t  *InitializationVector,
                                     uint32_t  IvLength,
                                     uint8_t  *OutputMessage,
                                     int32_t *OutputMessageLength,
                                     int32_t  AuthenticationTAGLength);

TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int ExampleAES128bitsCCM(void)
{

  int32_t status = AES_SUCCESS;
  int32_t example_status = 0;

  /* Encrypt DATA with AES in CCM mode and generate authentication TAG */

  status = STM32_AES_CCM_Encrypt( (uint8_t *) HeaderMessage_AES128bitsCCM, HeaderLength_AES128bitsCCM , (uint8_t *) Plaintext_AES128bitsCCM,
                                  InputLength_AES128bitsCCM, Key_AES128bitsCCM, IV_AES128bitsCCM, sizeof(IV_AES128bitsCCM), encrypt_OutputMessage_AES128bitsCCM,
                                  &encrypt_OutputMessageLength_AES128bitsCCM, &AuthenticationTAGLength_AES128bitsCCM);
  if (status == AES_SUCCESS)
  {

    if (Buffercmp(Expected_Ciphertext_AES128bitsCCM, encrypt_OutputMessage_AES128bitsCCM, CIPHER_TEXT_LENGTH_AES128bitsCCM) == PASSED)
    {
      /* add application traitment in case of AES CCM encryption is passed */

    }
    else
    {

      example_status = 0x0001;

    }
  }
  else
  {

    /* In case of encryption/decryption not success possible values of status:
    * AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER
    */

    example_status = 0x0001;


  }

  /* Decrypt DATA with AES in CCM mode and check the authentication TAG */
  status = STM32_AES_CCM_Decrypt( (uint8_t *) HeaderMessage_AES128bitsCCM, sizeof(HeaderMessage_AES128bitsCCM), (uint8_t *) encrypt_OutputMessage_AES128bitsCCM,
                                  encrypt_OutputMessageLength_AES128bitsCCM, Key_AES128bitsCCM, IV_AES128bitsCCM, sizeof(IV_AES128bitsCCM), decrypt_OutputMessage_AES128bitsCCM,
                                  &decrypt_OutputMessageLength_AES128bitsCCM, AuthenticationTAGLength_AES128bitsCCM);
  if (status == AUTHENTICATION_SUCCESSFUL)
  {

    if (Buffercmp(Plaintext_AES128bitsCCM, decrypt_OutputMessage_AES128bitsCCM, PLAINTEXT_LENGTH_AES128bitsCCM) == PASSED)
    {
      /* add application traitment in case of AES CCM encryption is passed */

    }
    else
    {

      example_status = 0x0001;


    }
    /* Add application traitment in case of AES CCM authentication is successful */
  }
  else
  {
    /*  In case of AES CCM authentication is failed possible values
      *  of status:
      * AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, 
      * AUTHENTICATION_FAILED
      */

    example_status = 0x0001;


  }
  return(example_status);
}


/**
  * @brief  AES CCM Authenticated Encryption example.
  * @param  HeaderMessage: pointer to the header message. It will be authenticated but not encrypted.
  * @param  HeaderMessageLength: header message length in byte.
  * @param  Plaintext: pointer to input message to be encrypted.
  * @param  PlaintextLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message and TAG
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @param  AuthenticationTAGLength: authentication TAG length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
int32_t STM32_AES_CCM_Encrypt(uint8_t*  HeaderMessage,
                              uint32_t  HeaderMessageLength,
                              uint8_t*  Plaintext,
                              uint32_t  PlaintextLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              int32_t *OutputMessageLength,
                              int32_t *AuthenticationTAGLength
                             )
{
  AccHw_AESCCMctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = 16;

  /* Set nonce size field to IvLength, note that valid values are 7,8,9,10,11,12,13*/
  AESctx.mNonceSize = IvLength;

  /* Size of returned authentication TAG */
  AESctx.mTagSize = 4;

  /* Set the size of the header */
  AESctx.mAssDataSize = HeaderMessageLength;

  /* Set the size of thepayload */
  AESctx.mPayloadSize = PlaintextLength;

  /* Initialize the operation, by passing the key and IV */
  error_status = AccHw_AES_CCM_Encrypt_Init(&AESctx, AES128_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Process Header */
    error_status = AccHw_AES_CCM_Header_Append(&AESctx,
                   HeaderMessage,
                   HeaderMessageLength);
    if (error_status == AES_SUCCESS)
    {
      /* Encrypt Data */
      error_status = AccHw_AES_CCM_Encrypt_Append(&AESctx,
                     Plaintext,
                     PlaintextLength,
                     OutputMessage,
                     OutputMessageLength);

      if (error_status == AES_SUCCESS)
      {
        /* Do the Finalization, write the TAG at the end of the encrypted message */
        error_status = AccHw_AES_CCM_Encrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, AuthenticationTAGLength);
      }
    }
  }

  return error_status;
}


/**
  * @brief  AES CCM Authenticated Decryption example.
  * @param  HeaderMessage: pointer to the header message. It will be authenticated but not Decrypted.
  * @param  HeaderMessageLength: header message length in byte.
  * @param  Plaintext: pointer to input message to be Decrypted.
  * @param  PlaintextLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the Decrypted message and TAG
  * @param  OutputMessageLength: pointer to Decrypted message length.
  * @param  AuthenticationTAGLength: authentication TAG length.
  * @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER, AUTHENTICATION_FAILED if error occured.
  */
int32_t STM32_AES_CCM_Decrypt(uint8_t*  HeaderMessage,
                              uint32_t  HeaderMessageLength,
                              uint8_t*  Plaintext,
                              uint32_t  PlaintextLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              int32_t *OutputMessageLength,
                              int32_t  AuthenticationTAGLength
                             )
{
  AccHw_AESCCMctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  /* Set flag field to default value */
  AESctx.mFlags = AccHw_E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = 16;

  /* Set nonce size field to IvLength, note that valid values are 7,8,9,10,11,12,13*/
  AESctx.mNonceSize = IvLength;

  /* Size of returned authentication TAG */
  AESctx.mTagSize = 4;

  /* Set the size of the header */
  AESctx.mAssDataSize = HeaderMessageLength;

  /* Set the size of thepayload */
  AESctx.mPayloadSize = PlaintextLength;

  /* Set the pointer to the TAG to be checked */
  AESctx.pmTag = Plaintext + PlaintextLength;

  /* Size of returned authentication TAG */
  AESctx.mTagSize = AuthenticationTAGLength;


  /* Initialize the operation, by passing the key and IV */
  error_status = AccHw_AES_CCM_Decrypt_Init(&AESctx, AES128_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Process Header */
    error_status = AccHw_AES_CCM_Header_Append(&AESctx,
                   HeaderMessage,
                   HeaderMessageLength);
    if (error_status == AES_SUCCESS)
    {
      /* Decrypt Data */
      error_status = AccHw_AES_CCM_Decrypt_Append(&AESctx,
                     Plaintext,
                     PlaintextLength,
                     OutputMessage,
                     OutputMessageLength);

      if (error_status == AES_SUCCESS)
      {
        /* Do the Finalization, check the authentication TAG*/
        error_status = AccHw_AES_CCM_Decrypt_Finish(&AESctx, NULL, &AuthenticationTAGLength);
      }
    }
  }

  return error_status;
}


/**
  * @}
  */


/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/
