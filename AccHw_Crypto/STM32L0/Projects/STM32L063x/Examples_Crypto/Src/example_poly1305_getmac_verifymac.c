/**
  ******************************************************************************
  * @file    Examples_Crypto/Src/example_poly1305_getmac_verifymac.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   POLY1305 Get and Verification MAC Example
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
#include "example_poly1305_getmac_verifymac.h"

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined (__CC_ARM) /*!< ARM Compiler */
__align(4)
const uint8_t Key_POLY1305GetMACVerifMAC[]  =
  {
    0xec, 0x07, 0x4c, 0x83, 0x55, 0x80, 0x74, 0x17,
    0x01, 0x42, 0x5b, 0x62, 0x32, 0x35, 0xad, 0xd6,
    0x85, 0x1f, 0xc4, 0x0c, 0x34, 0x67, 0xac, 0x0b,
    0xe0, 0x5c, 0xc2, 0x04, 0x04, 0xf3, 0xf7, 0x00
  } ;

#elif defined (__ICCARM__) /*!< IAR Compiler */
#pragma data_alignment=4
const uint8_t Key_POLY1305GetMACVerifMAC[]  =
  {
    0xec, 0x07, 0x4c, 0x83, 0x55, 0x80, 0x74, 0x17,
    0x01, 0x42, 0x5b, 0x62, 0x32, 0x35, 0xad, 0xd6,
    0x85, 0x1f, 0xc4, 0x0c, 0x34, 0x67, 0xac, 0x0b,
    0xe0, 0x5c, 0xc2, 0x04, 0x04, 0xf3, 0xf7, 0x00
  } ;
#elif defined (__GNUC__) /*!< GNU Compiler */
__attribute__ ((aligned (4)))
const uint8_t Key_POLY1305GetMACVerifMAC[] =
{
  0xec, 0x07, 0x4c, 0x83, 0x55, 0x80, 0x74, 0x17,
  0x01, 0x42, 0x5b, 0x62, 0x32, 0x35, 0xad, 0xd6,
  0x85, 0x1f, 0xc4, 0x0c, 0x34, 0x67, 0xac, 0x0b,
  0xe0, 0x5c, 0xc2, 0x04, 0x04, 0xf3, 0xf7, 0x00
};
#endif /* __GNUC__ */

const uint8_t Nonce_POLY1305GetMACVerifMAC[] =
  {
    0xfb, 0x44, 0x73, 0x50, 0xc4, 0xe8, 0x68, 0xc5,
    0x2a, 0xc3, 0x27, 0x5c, 0xf9, 0xd4, 0x32, 0x7e
  };
const uint8_t Input_POLY1305GetMACVerifMAC[] =
  {
    0xf3, 0xf6
  };


/* Buffer to store the output data */
uint8_t OutputMessage_POLY1305GetMACVerifMAC[16];

/* Size of the output data */
uint32_t OutputMessageLength_POLY1305GetMACVerifMAC = 0;

const uint8_t Expected_Result_POLY1305GetMACVerifMAC[] =
  {
    0xf4, 0xc6, 0x33, 0xc3, 0x04, 0x4f, 0xc1, 0x45,
    0xf8, 0x4f, 0x33, 0x5c, 0xb8, 0x19, 0x53, 0xde
  };

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_POLY1305_GET_MAC(const uint8_t *input,
                               const uint8_t *key,
                               const uint8_t *nonce,
                               int32_t inputSize,
                               uint8_t  *OutputMessage,
                               uint32_t *OutputMessageLength);
int32_t STM32_POLY1305_VERIFY_MAC
(const uint8_t *input,
 const uint8_t *key,
 const uint8_t *nonce,
 int32_t inputSize,
 const uint8_t *expectedResult);


TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int ExamplePOLY1305GetMACVerifMAC(void)
{

  int32_t status = POLY1305_SUCCESS;
  int32_t example_status = 0;

  status = STM32_POLY1305_GET_MAC(Input_POLY1305GetMACVerifMAC,
                                  Key_POLY1305GetMACVerifMAC,
                                  Nonce_POLY1305GetMACVerifMAC,
                                  sizeof(Input_POLY1305GetMACVerifMAC),
                                  OutputMessage_POLY1305GetMACVerifMAC,
                                  &OutputMessageLength_POLY1305GetMACVerifMAC);


  if (status == POLY1305_SUCCESS)
  {
    if ((Buffercmp(Expected_Result_POLY1305GetMACVerifMAC, OutputMessage_POLY1305GetMACVerifMAC, 16) == PASSED) || OutputMessageLength_POLY1305GetMACVerifMAC == 16)
    {
      /* add application traitment in case of POLY1305 encryption is passed */

    }
    else
    {


      example_status = 0x00A0;

    }
  }
  else
  {
    /* In case of POLY1305 encryption not success possible values of status:
       * POLY1305_ERR_BAD_CONTEXT, POLY1305_ERR_BAD_PARAMETER, POLY1305_ERR_BAD_OPERATION
       */

    example_status = 0x00A0;
  }
  status = STM32_POLY1305_VERIFY_MAC(Input_POLY1305GetMACVerifMAC,
                                     Key_POLY1305GetMACVerifMAC,
                                     Nonce_POLY1305GetMACVerifMAC,
                                     sizeof(Input_POLY1305GetMACVerifMAC),
                                     OutputMessage_POLY1305GetMACVerifMAC);

  if (status == AUTHENTICATION_SUCCESSFUL)
  {
    /* add application traitment in case of POLY1305 authentication is successful */

  }
  else
  {
    /* In case of POLY1305 authentication is failed possible values of status:
       * POLY1305_ERR_BAD_CONTEXT, POLY1305_ERR_BAD_PARAMETER, POLY1305_ERR_BAD_OPERATION, 
       * AUTHENTICATION_FAILED*/

    example_status = 0x00A0;
  }
  return(example_status);
}

/**
* @brief  Function to test the TAG Generation Functionalities of Poly1305-AES
* @param[in]  *input          Input message to be authenticated
* @param[in]  *key            Key
* @param[in]  *nonce          Nonce
* @param[in]   inputSize      Size of input
* @retval error status: can be POLY1305_SUCCESS if success or one of
*         POLY1305_ERR_BAD_CONTEXT, POLY1305_ERR_BAD_PARAMETER, POLY1305_ERR_BAD_OPERATION
*         if error occured.
*/
int32_t STM32_POLY1305_GET_MAC(const uint8_t *input, const uint8_t *key, const uint8_t *nonce, int32_t inputSize, uint8_t  *OutputMessage,
                               uint32_t *OutputMessageLength)
{

  int32_t outputLength = 16;
  AccHw_Poly1305ctx_stt polyctx;
  uint32_t error_status = POLY1305_SUCCESS;


  /* Initialize Context by setting the size of the required TAG */
  polyctx.mTagSize = 16;

  /* Initialize operation */
  error_status = AccHw_Poly1305_Auth_Init(&polyctx, key, nonce);

  if (error_status == POLY1305_SUCCESS)
  {
    error_status = AccHw_Poly1305_Auth_Append(&polyctx,
                   input,
                   inputSize);


    if (error_status == POLY1305_SUCCESS)
    {

      error_status = AccHw_Poly1305_Auth_Finish(&polyctx, OutputMessage , &outputLength);

    }
  }

  return error_status;
}


/**
* @brief  Function to test the TAG Verification Functionalities of Poly1305-AES
* @param[in]  *input          Input message to be authenticated
* @param[in]  *key            Key
* @param[in]  *nonce          Nonce
* @param[in]   inputSize      Size of input
* @param[in]  *expectedResult Expected Result, used in verification
* @retval error status: can be AUTHENTICATION_SUCCESSFUL if success or one of
*         POLY1305_ERR_BAD_CONTEXT, POLY1305_ERR_BAD_PARAMETER, POLY1305_ERR_BAD_OPERATION, AUTHENTICATION_FAILED
*         if error occured.
*/
int32_t STM32_POLY1305_VERIFY_MAC(const uint8_t *input, const uint8_t *key, const uint8_t *nonce, int32_t inputSize, const uint8_t *expectedResult)
{
  uint32_t error_status ;
  AccHw_Poly1305ctx_stt polyctx;

  /* Initialize Context by setting the size of the required TAG and pointer to TAG to be verified */
  polyctx.mTagSize = 16;
  polyctx.pmTag = expectedResult;

  /* Initialize operation */
  error_status = AccHw_Poly1305_Verify_Init(&polyctx, key, nonce);
  if (error_status == POLY1305_SUCCESS)
  {
    error_status = AccHw_Poly1305_Verify_Append(&polyctx, input, inputSize);

    if (error_status == POLY1305_SUCCESS)
    {
      /* Generate TAG */
      error_status = AccHw_Poly1305_Verify_Finish(&polyctx, NULL, NULL);
    }

  }
  return error_status;
}

/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/

