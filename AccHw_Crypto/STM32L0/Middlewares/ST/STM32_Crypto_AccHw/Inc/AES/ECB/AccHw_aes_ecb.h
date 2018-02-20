/**
  ******************************************************************************
  * @file    AccHw_aes_ecb.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   AES in ECB Mode
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
  *****************************************************************************/
/*! 
* \page Tutorial_AES_ECB AES-ECB Tutorial
*
* Here follows an example of AES-128-ECB encryption.
* Please remember that before starting to call the Encryption function the context \b requires user 
* initialization. The Key Size and Flags member must be initialized prior to calling the 
*  init function. Look at the each function documentation to see what is needed prior of calling.
*
* The API functions to be used are:
*  - \ref AES_ECB_Encrypt_Init initialize an \ref AESECBctx_stt context with key
*  - \ref AES_ECB_Encrypt_Append process the input and produces the output. 
*    It can be called multiple times but the input size must be multiple of 16. 
*  - \ref AES_ECB_Encrypt_Finish can be called only one time for the finalization process
*
* The following code performs a ECB encryption with AES-128 of 1024 in 4 Append calls.
* \code
* #include <stdio.h>
* #include "crypto.h"
* int32_t main()
* {
*   uint8_t key[CRL_AES128_KEY]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
*   uint8_t plaintext[1024]={...};
*   uint8_t ciphertext[1024];
*   // outSize is for output size, retval is for return value
*   int32_t outSize, retval;
*   AESECBctx_stt AESctx_st; // The AES context
*
*   // Initialize Context Flag with default value
*   AESctx_st.mFlags = E_SK_DEFAULT;
*   // Set Iv size to 16
*   AESctx_st.mIvSize=16;
*   // Set key size to 16
*   AESctx_st.mKeySize=CRL_AES128_KEY;
*   // call init function
*   retval = AES_ECB_Encrypt_Init(&AESctx_st, key, NULL);
*   if (retval != AES_SUCCESS)
*   {  ... }
*
*   // Loop to perform four calls to AES_CBC_Encrypt_Append, each processing 256 bytes
*   for (i = 0; i < 1024; i += 256)
*   { //Encrypt i bytes of plaintext. Put the output data in ciphertext and number 
*     //of written bytes in outSize
*     retval = AES_ECB_Encrypt_Append(&AESctx_st, plaintext, 256, ciphertext, &outSize);
*     if (retval != AES_SUCCESS)
*     {  ... }
*   }
*   //Do the finalization call (in CBC it will not return any output)
*   retval = AES_ECB_Encrypt_Finish(&AESctx_st, ciphertext+outSize, &outSize );
*   if (retval != AES_SUCCESS)
*   {  ... }
* }
* \endcode
*/
#ifndef __CRL_AccHw_AES_ECB_H__
#define __CRL_AccHw_AES_ECB_H__

#ifdef __cplusplus
 extern "C" {
#endif

/** @ingroup AESECB
  * @{
  */


/*---------**- Types and Constants definition -**-----------------------------------------------------------*/
/** ECB context = CBC context. AESECBctx_stt is equal to AESCBCctx_stt */
typedef AESCBCctx_stt AESECBctx_stt;

/*---------**-  HIGH LEVEL FUNCTIONS -**------------------------------------------------*/

#ifdef INCLUDE_AccHw_ENCRYPTION
/* load the key and ivec, eventually performs key schedule, init hw, etc. */
int32_t AccHw_AES_ECB_Encrypt_Init(AESECBctx_stt *P_pAESECBctx, const uint8_t *P_pKey, const uint8_t *P_pIv);

/* launch crypto operation , can be called several times */
int32_t AccHw_AES_ECB_Encrypt_Append (AESECBctx_stt *P_pAESECBctx,
                                const uint8_t *P_pInputBuffer,
                                int32_t        P_inputSize,
                                uint8_t       *P_pOutputBuffer,
                                int32_t       *P_pOutputSize);

/* Possible final output */
int32_t AccHw_AES_ECB_Encrypt_Finish (AESECBctx_stt *P_pAESECBctx,
                                uint8_t       *P_pOutputBuffer,
                                int32_t       *P_pOutputSize);
#endif /* ECB Encryption */
#ifdef INCLUDE_AccHw_DECRYPTION
/* load the key and ivec, eventually performs key schedule, init hw, etc. */
int32_t AccHw_AES_ECB_Decrypt_Init (AESECBctx_stt *P_pAESECBctx, const uint8_t *P_pKey, const uint8_t *P_pIv);

/* launch crypto operation , can be called several times */
int32_t AccHw_AES_ECB_Decrypt_Append (AESECBctx_stt *P_pAESECBctx,
                                const uint8_t *P_pInputBuffer,
                                int32_t        P_inputSize,
                                uint8_t       *P_pOutputBuffer,
                                int32_t       *P_pOutputSize);

/* Possible final output */
int32_t AccHw_AES_ECB_Decrypt_Finish (AESECBctx_stt *P_pAESECBctx,
                                uint8_t       *P_pOutputBuffer,
                                int32_t       *P_pOutputSize);
#endif /* ECB Decryption */

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /*__CRL_AccHw_AES_ECB_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
