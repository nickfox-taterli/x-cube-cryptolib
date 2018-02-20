/**
******************************************************************************
* @file    ed25519.h
* @author  MCD Application Team
* @version V3.0.0
* @date    05-June-2015
* @brief   Container for ed25519 functionalities
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Image SW License Agreement V2, (the "License");
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

/*!
* \page Tutorial_ed25519 Ed25519 Tutorial
*
* This library supports ed25519 functions for:
*  - Key Generation
*  - Signature Generation
*  - Signature Verification
*
*  Please note that there are no special structures to handle private/public keys and signatures. \n
*  Everything is handled as byte arrays. In particular:
*  - A private key is a 64 byte array
*  - A public key is a 32 byte array
*  - A digital signature is a 64 byte array
*
*  There are 3 functions, at user level, to handle the functionalities, these are:
*  - \ref ED25519keyGen to generate both private and public keys
*  - \ref ED25519sign to generate a signature of a message
*  - \ref ED25519verify  to verify a signature of a message
*
*  The first example show how to call the ED25519keyGen in order to generate a key pair. \n
*  The function requires the caller to fill P_pPrivateKey with 32 random bytes before calling . \n
*
* \code
* #include <stdio.h>
* #include "crypto.h"
* int main()
* {
*   uint8_t pubKey[32];  //Buffer that will store the public key
*   uint8_t privKey[64]; //Buffer that will store the private key
*   int32_t retval;      // Used to check return values
*   RNGstate_stt randState_st; //Used for the random generation
*   RNGinitInput_stt RNGinit_st; //Structure required to call \ref RNGinit
*   uint8_t entropy_data[32]={...};   //It should contain entropy
*
*   //Let's Instantiate with entropy,nonce and no personalization string.
*   RNGinit_st.pmEntropyData = entropy_data;
*   RNGinit_st.mEntropyDataSize = sizeof(entropy_data);
*   RNGinit_st.pmNonce = NULL;
*   RNGinit_st.mNonceSize = 0;
*   RNGinit_st.pmPersData = NULL;
*   RNGinit_st.mPersDataSize = 0;
*
*   //Initialize the random engine, using a DRBG Based on AES-128
*   retval = RNGinit(&RNGinit_st, C_DRBG_AES128, &randState_st);
*   if (retval != RNG_SUCCESS)
*   {  ..handle error.. }
*   // We have an initialized random state, now we can call the random bytes generation
*   retval = RNGgenBytes(&RNGstate, NULL, privKey, 32);
*   if (retval != RNG_SUCCESS)
*   { ..handle error.. }
*   // privKey has 32 random bytes, now we can call ED25519KeyGen
*   retval = ED25519keyGen(privKey, pubKey);
*   if (retval != ED25519_SUCCESS)
*   { ..handle error.. }
*   // Now privKey and pubKey have been generated!
* }
* \endcode
*
* The second example will demonstrate how to generate and verify a signature. \n
* We make the assumption that we already have a valid private and public key. \n
* Please note that the verification function \ref ED25519verify will return \ref SIGNATURE_VALID
* in case of success. \n With \b all other return values the signature \b must be considered \b invalid
*
* \code
* #include <stdio.h>
* #include "crypto.h"
* int main()
* {
*   uint8_t pubKey[32]={...};  //Buffer that contains a valid public key
*   uint8_t privKey[64]={...}; //Buffer that contains a valid private key
*   int32_t retval;            // Used to check return values
*   const uint8_t message[1024]={...};   //The message we want to sign
*   uint8_t signature[64];     //Buffer that will store the signature
*
*   //Sign the message
*   retval = ED25519sign(signature, message, sizeof(message), privKey);
*   if (retval != ED25519_SUCCESS)
*   { ..handle error.. }
*   //We have generated our signature! Let's verify it!
*   retval = ED25519verify(message, sizeof(message), signature, pubKey);
*   if (retval != SIGNATURE_VALID)
*   { ..handle error.. }
*   // Here the signature is good!
* }
* \endcode
*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ED25519_H__
#define __ED25519_H__

#ifdef __cplusplus
extern "C"
{
#endif

  /** @addtogroup ED25519
  * @{
  */
  /* Includes ------------------------------------------------------------------*/
#include <stdint.h>
  /* Exported types ------------------------------------------------------------*/

  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported functions ------------------------------------------------------- */
  int32_t ED25519keyGen(uint8_t *P_pPrivateKey, uint8_t *P_pPublicKey);
  int32_t ED25519sign(uint8_t *P_pSignature, const uint8_t *P_pInput, int32_t P_InputSize, const uint8_t *P_pPrivateKey);
  int32_t ED25519verify(const uint8_t *P_pInput, int32_t P_InputSize, const uint8_t *P_pSignature, const uint8_t *P_pPublicKey);

  /**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __ED25519_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
