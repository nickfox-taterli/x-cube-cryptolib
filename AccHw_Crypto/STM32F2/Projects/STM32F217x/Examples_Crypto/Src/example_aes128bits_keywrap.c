/**
  ******************************************************************************
  * @file    Examples_Crypto/Src/example_aes128bits_keywrap.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   AES-128 KEYWRAP Example
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
#include "example_aes128bits_keywrap.h"

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PLAINTEXT_LENGTH_AES128bitsKEYWRAP 16
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t OutputMessage_AES128bitsKEYWRAP[128];
int32_t OutputMessageLength_AES128bitsKEYWRAP;
const uint8_t Plaintext_AES128bitsKEYWRAP[PLAINTEXT_LENGTH_AES128bitsKEYWRAP] =
  {
    0x00, 0x11, 0x22, 0x33, 0x44,
    0x55, 0x66, 0x77, 0x88, 0x99,
    0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
  };

uint8_t key_AES128bitsKEYWRAP[] =
  {
    0x00, 0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08, 0x09,
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
  };

uint8_t IV_AES128bitsKEYWRAP[CRL_AES_KWRAP_BLOCK] =
  {
    0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6,
    0xA6
  };

uint8_t Expected_Ciphertext_AES128bitsKEYWRAP[3*CRL_AES_KWRAP_BLOCK] =
  {
    0x1F, 0xA6,
    0x8B, 0x0A, 0x81, 0x12, 0xB4, 0x47, 0xAE, 0xF3, 0x4B, 0xD8, 0xFB, 0x5A, 0x7B, 0x82, 0x9D, 0x3E,
    0x86, 0x23, 0x71, 0xD2, 0xCF, 0xE5
  };

/* Private function prototypes -----------------------------------------------*/
static int32_t STM32_AES_kwrap_Encrypt(uint8_t*  InputMessage,
                                       uint8_t  InputMessageLength,
                                       uint8_t  *Key,
                                       uint8_t  *IV,
                                       uint8_t  IvLength,
                                       uint8_t  *OutputMessage,
                                       int32_t *OutputMessageLength);

static int32_t STM32_AES_kwrap_Decrypt(uint8_t*  InputMessage,
                                       uint8_t  InputMessageLength,
                                       uint8_t  *Key,
                                       uint8_t  *IV,
                                       uint8_t  IvLength,
                                       uint8_t  *OutputMessage,
                                       int32_t *OutputMessageLength);

TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int ExampleAES128bitsKEYWRAP(void)
{
  int32_t status = AES_SUCCESS;
  int32_t example_status = 0;

  /* Encrypt DATA with AES in KEYWRAP mode */
  status = STM32_AES_kwrap_Encrypt( (uint8_t *) Plaintext_AES128bitsKEYWRAP, PLAINTEXT_LENGTH_AES128bitsKEYWRAP, key_AES128bitsKEYWRAP, IV_AES128bitsKEYWRAP, sizeof(IV_AES128bitsKEYWRAP), OutputMessage_AES128bitsKEYWRAP,
                                    &OutputMessageLength_AES128bitsKEYWRAP);

  if (status == AES_SUCCESS)
  {
    if (Buffercmp(Expected_Ciphertext_AES128bitsKEYWRAP, OutputMessage_AES128bitsKEYWRAP, 3*CRL_AES_KWRAP_BLOCK) == PASSED)
    {
      /* add application traitment in case of AES keywrap encryption is passed */

    }
    else
    {

      example_status = 0x0006;

    }
  }
  else
  {
    /* In case of encryption/decryption not success, the possible values of status:
      * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION
    */

    example_status = 0x0006;



  }
  /* Decrypt DATA with AES in KEYWRAP mode */
  status = STM32_AES_kwrap_Decrypt( (uint8_t *) Expected_Ciphertext_AES128bitsKEYWRAP, 3 * CRL_AES_KWRAP_BLOCK , key_AES128bitsKEYWRAP, IV_AES128bitsKEYWRAP, sizeof(IV_AES128bitsKEYWRAP), OutputMessage_AES128bitsKEYWRAP,
                                    &OutputMessageLength_AES128bitsKEYWRAP);
  if (status == AUTHENTICATION_SUCCESSFUL)
  {
    /* add application traitment in case of AES keywrap authentication is successful*/
  }
  else
  {

    /* add application traitment in case of AES keywrap encryption is failed */
    /* add application traitment in case of AES keywrap authentication is failed, possible values
    *  of status:
    * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, 
    * AUTHENTICATION_FAILED
    */
    example_status = 0x0006;
  }
  return(example_status);
}



/**
  * @brief  AES kwrap Encryption example.
  * @param  InputMessage: pointer to input message to be encrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_INPUT_SIZE, AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER if error occured.
  */
static int32_t STM32_AES_kwrap_Encrypt(uint8_t*  InputMessage,
                                       uint8_t  InputMessageLength,
                                       uint8_t  *Key,
                                       uint8_t  *IV,
                                       uint8_t  IvLength,
                                       uint8_t  *OutputMessage,
                                       int32_t *OutputMessageLength)
{
  int32_t outputLength = 0;
  int32_t status = AES_SUCCESS;
  AccHw_AESKWctx_stt KWctx_st;
  KWctx_st.mKeySize = CRL_AES128_KEY;
  KWctx_st.mFlags = AccHw_E_SK_DEFAULT;

  status = AccHw_AES_KeyWrap_Encrypt_Init(&KWctx_st, Key, IV);
  if (status == AES_SUCCESS)
  {
    status = AccHw_AES_KeyWrap_Encrypt_Append(&KWctx_st, InputMessage, CRL_AES128_KEY, OutputMessage, &outputLength);
    if (status == AES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      status = AccHw_AES_KeyWrap_Encrypt_Finish(&KWctx_st, OutputMessage, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }
  return status;
}


/**
  * @brief  AES kwrap Decryption example.
  * @param  InputMessage: pointer to input message to be decrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @param  OutputMessageLength: pointer to decrypted message length.
  * @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of
  *         AES_ERR_BAD_OPERATION, AES_ERR_BAD_CONTEXT
  *         AES_ERR_BAD_PARAMETER, AES_ERR_BAD_INPUT_SIZE, AUTHENTICATION_FAILED if error occured.
  */
static int32_t STM32_AES_kwrap_Decrypt(uint8_t*  InputMessage,
                                       uint8_t  InputMessageLength,
                                       uint8_t  *Key,
                                       uint8_t  *IV,
                                       uint8_t  IvLength,
                                       uint8_t  *OutputMessage,
                                       int32_t *OutputMessageLength)
{
  int32_t outputLength = 0;
  int32_t status = AES_SUCCESS;
  AccHw_AESKWctx_stt KWctx_st;
  KWctx_st.mKeySize = CRL_AES128_KEY;
  KWctx_st.mFlags = AccHw_E_SK_DEFAULT;

  /* Initialize the operation, by passing the key.*/
  status = AccHw_AES_KeyWrap_Decrypt_Init(&KWctx_st, Key, IV);

  /* check for initialization errors */
  if (status == AES_SUCCESS)
  {
    /* Decrypt Data */
    status = AccHw_AES_KeyWrap_Decrypt_Append(&KWctx_st,
             InputMessage,
             InputMessageLength,
             OutputMessage,
             &outputLength );

    if (status == AES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      status = AccHw_AES_KeyWrap_Decrypt_Finish(&KWctx_st, OutputMessage, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return status;
}

/**
  * @}
  */


/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/
