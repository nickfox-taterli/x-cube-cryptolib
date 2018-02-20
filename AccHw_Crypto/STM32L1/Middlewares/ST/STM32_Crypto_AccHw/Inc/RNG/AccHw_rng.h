/**
  ******************************************************************************
  * @file    AccHw_rng.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Provides the random engine to the crypto library
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
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

/*! \page Tutorial_RNG RNG Tutorial
  *
  * Here follows an example of RNG (random generation) functionality.
  * The RNG API can be used to generate cryptographically strong pseudorandom numbers or accessing the 
  * TRNG (True Random Number Generator) hw engine present in some STM32 models.
  *
  * The API is based on a Init/Generate/Deinit model, with the expection that there is a reseed function
  * to provide the RNG with new entropy.
  * Note that some cryptographic functions of this library (i.e., ECDSA signature generation)
  * require an initialied RNG context. In this context the user is required to initialize the RNG
  * context and free it at the end of the execution.
  * 
  * The complete set of RNG API is:
  *  - \ref RNGinit Used to initialize the RNG context
  *  - \ref RNGgenBytes Used to generate a random byte string
  *  - \ref RNGgenWords  Used to generate a random word (32-bit) string
  *  - \ref RNGreseed  Used to provide with additional entropy the generator
  *  - \ref RNGfree Used to deinit the generator
  *
  * During the \ref RNGinit call the user is required to specify which RNG engine he will use. \n 
  * Currently available options are:
  * - C_DRBG_AES128 which indicates the use of a NIST DRBG based on AES-128
  * - C_HW_RNG which indicates the use of the STM32 TRNG (if available)
  *
  * Note that when the TRNG is used, any call to the RNGreseed function will result in an error.
  *
  * Please remember to initialize the proper input structures before calling the RNG API, in particular:
  * - \ref RNGinit requires a properly user-initialized \ref RNGinitInput_stt
  * - \ref RNGreseed requires a properly user-initialized \ref RNGreInput_stt
  * - \ref RNGgenBytes and \ref RNGgenWords may optionally receive a properly initialized \ref RNGaddInput_stt 
  *   structure (or NULL)
  *
  * The following code initialize a DRBG-AES-128 RNG context and use it to generate a random 16 byte string.
  * \code
  * #include <stdio.h>
  * #include "crypto.h"
  * int32_t main()
  * {
  *   //RNG context
  *   RNGstate_stt RNGstate;
  *   //RNG init structure
  *   RNGinitInput_stt RNGinit_st;
  *   // String of entropy 
  *   uint8_t entropy_data[32]={...};   //Its size can vary between 16 and 32 bytes
  *   uint8_t nonce[8]={...}; //Its size can vary between 0 and 16 bytes
  *   uint8_t AES_iv[16]; //It will be the output of our RNG call
  *
	*   //Let's Instantiate with entropy,nonce and no personalization string. 
  *   RNGinit_st.pmEntropyData = entropy_input;
  *   RNGinit_st.mEntropyDataSize = sizeof(entropy_input);
  *   RNGinit_st.pmNonce = nonce;
  *   RNGinit_st.mNonceSize = sizeof(nonce);
  *   RNGinit_st.pmPersData = NULL; 
  *   RNGinit_st.mPersDataSize = 0;
  *
  *   //Let's initialize the RNG state/context
  *   retval = RNGinit(&RNGinit_st, C_DRBG_AES128, &RNGstate);
  *   if (retval != RNG_SUCCESS)
  *   { ... }
  *
  *   //Now we can generate the 16 bytes random string
  *   retval = RNGgenBytes(&RNGstate,NULL,AES_iv,sizeof(AES_iv));
  *   //Note that "NULL" parameter is due the fact that we didn't provide any additional input
  *   if (retval != RNG_SUCCESS)
  *   { ... }
  *
  *   //Free the RNG state
  *   RNGfree(&RNGstate);
  *   if (retval != RNG_SUCCESS)
  *   { ... }
  *
  * }
  * \endcode
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRL_AccHw_RNG_H__
#define __CRL_AccHw_RNG_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "DRBG_AES128/AccHw_drbg.h"


/** @addtogroup RNG
  * @{
  */ 
  
#define C_DRBG_AES128 0  /*!< Constant associated with the DRBG based on AES-128 to be used as DRBG for the random engine */

#define C_HW_RNG 1          /*!< Constant associated with the use of an HW TRNG for the random engine */

/** 
  * @brief  Structure that contains the RNG stat
  */
typedef struct
{  
  uint8_t mRNGstate[CRL_DRBG_AES128_STATE_SIZE];  /*!< Underlying DRBG context. It is initialized by \ref RNGinit */
  
  uint32_t mFlag;        /*!< Used to check if the random state has been mFlag */
} AccHw_RNGstate_stt;


/** 
  * @brief  Structure used by RNGinit to initialize a DRBG
  */
typedef struct
{
  
  uint8_t* pmEntropyData;   /*!< The entropy data input */
  
  int32_t mEntropyDataSize; /*!< Size of the entropy data input */
  
  uint8_t* pmNonce;         /*!< The Nonce data */
  
  int32_t mNonceSize;       /*!< Size of the Nonce */
  
  uint8_t* pmPersData;      /*!< Personalization String */
  
  int32_t mPersDataSize;    /*!< Size of personalization string*/
} AccHw_RNGinitInput_stt;


/** 
  * @brief  Structure used by RNGreseed to reseed a DRBG
  */
typedef struct
{
  
  uint8_t* pmEntropyData;   /*!< The entropy data input */
  
  int32_t mEntropyDataSize; /*!< Size of the entropy data input */
  
  uint8_t* pmAddInput;      /*!< Additional input */
  
  int32_t mAddInputSize;    /*!< Size of additional input */
} AccHw_RNGreInput_stt;

/** 
  * @brief  Structure used by RNGgenBytes or RNGgenWords to provide the optional additional input
  */
typedef struct
{    
  uint8_t* pmAddInput;      /*!< Additional input */
  
  int32_t mAddInputSize;    /*!< Size of additional input */
} AccHw_RNGaddInput_stt;


/* Exported functions ------------------------------------------------------- */
/* Reseed random **************************************************************/
int32_t AccHw_RNGreseed(const AccHw_RNGreInput_stt *P_pInputData,
                  AccHw_RNGstate_stt *P_pRandomState);

/* Initialize random **********************************************************/
int32_t AccHw_RNGinit(const AccHw_RNGinitInput_stt *P_pInputData,
                AccHw_RNGstate_stt *P_pRandomState);
/* Free random ****************************************************************/
int32_t AccHw_RNGfree( AccHw_RNGstate_stt *P_pRandomState );

/* Generate random octets to a buffer *****************************************/
int32_t AccHw_RNGgenBytes(AccHw_RNGstate_stt *P_pRandomState,
                    const AccHw_RNGaddInput_stt *P_pAddInput, 
                    uint8_t *P_pOutput, 
                    int32_t P_OutLen);

/* Return a random int32_t ****************************************************/
int32_t AccHw_RNGgenWords(AccHw_RNGstate_stt *P_pRandomState, 
                    const AccHw_RNGaddInput_stt *P_pAddInput, 
                    uint32_t *P_pWordBuf, 
                    int32_t P_BufSize);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */


#endif /* __CRL_AccHw_RAND_H__ */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
