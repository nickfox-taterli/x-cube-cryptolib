/**
  ******************************************************************************
  * @file    AccHw_ecc.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Provides Elliptic Curve Cryptography (ECC) primitives 
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
/**
* \page Tutorial_ECC ECC Tutorial
*
* This library supports ECC functions for:
*  - ECDSA signature verification, Public Key Verification, Scalar Multiplication 
*  - ECDSA signature generation and ECC Key generation 
*
* Unlike other functions in the library ECC objects must be initialized and freed, and to set/get their values
* the user should use special functions.
*
* The first thing to do before starting en ECC operation is to initialize a \ref EC_stt structure containing
* the parameters of the particular ECC curve that the user want to use. This is done through the function
* \ref ECCinitEC and at the end of the ECC operation it can be freed by \ref ECCfreeEC .
* 
* After this initial call the user might want to initialize other objects for the functions he will call.
* For example initializing a :
*   - Private key (\ref ECCprivKey_stt) with \ref ECCinitPrivKey, settings its value through 
*     \ref ECCsetPrivKeyValue and at the end of the operation, freeing it with \ref ECCfreePrivKey
*   - EC point (\ref ECpoint_stt), which is also a public key, is done by \ref ECCinitPoint, its coordinate
*     can be set and get through \ref ECCsetPointCoordinate and \ref ECCgetPointCoordinate and it will be freed
*     through \ref ECCfreePoint
*   - ECDSA signature (\ref ECDSAsignature_stt) must be initialized by \ref ECDSAinitSign the two signature
*     values can be set by \ref ECDSAsetSignature and get by \ref ECDSAgetSignature. At the end it should be 
*     freed through \ref ECDSAfreeSign
*
* Please note that the functions \ref ECCkeyGen and \ref ECDSAsign, require an initialized random engine structure.
*
* Scalar multiplication is the ECC operation that it is used in ECDSA and in ECDH. It is also used to
* generate a public key.
* A simple usage of the ECC API for scalar multiplication to generate a public key from a known private key is shown below:
*
* \code
* #include <stdio.h>
* #include "crypto.h"
* int main()
* {
*   const uint8_t ecc_160_a[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFC};
*   const uint8_t ecc_160_b[]={0x1C,0x97,0xBE,0xFC,0x54,0xBD,0x7A,0x8B,0x65,0xAC,0xF8,0x9F,0x81,0xD4,0xD4,0xAD,0xC5,0x65,0xFA,0x45};
*   const uint8_t ecc_160_p[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF};
*   const uint8_t ecc_160_n[]={0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xF4,0xC8,0xF9,0x27,0xAE,0xD3,0xCA,0x75,0x22,0x57};
*   const uint8_t ecc_160_xG[]={0x4A,0x96,0xB5,0x68,0x8E,0xF5,0x73,0x28,0x46,0x64,0x69,0x89,0x68,0xC3,0x8B,0xB9,0x13,0xCB,0xFC,0x82};
*   const uint8_t ecc_160_yG[]={0x23,0xA6,0x28,0x55,0x31,0x68,0x94,0x7D,0x59,0xDC,0xC9,0x12,0x04,0x23,0x51,0x37,0x7A,0xC5,0xFB,0x32};
*   const uint8_t ecc_160_privkey[]={0xAA,0x37,0x4F,0xFC,0x3C,0xE1,0x44,0xE6,0xB0,0x73,0x30,0x79,0x72,0xCB,0x6D,0x57,0xB2,0xA4,0xE9,0x82};
*
*   // Buffer to keep the returned public key X coordinate
*   uint8_t pubKeyX[160/8];
*   // Buffer to keep the returned public key Y coordinate
*   uint8_t pubKeyY[160/8];
*   //integer that will keep the retuned size of the public key X coordinate
*   int32_t Xsize;
*   //integer that will keep the retuned size of the public key Y coordinate
*   int32_t Ysize;
*   // Structure that will keep the Elliptic Curve parameters (those values above)
*   EC_stt ECparams;
*   // These are the Elliptic Curve point objects. In ECC public key ARE just elliptic curve points.
*   ECpoint_stt *G = NULL, *PubKey = NULL;
*   // This will keep the scalar used in the scalar multiplication
*   ECCprivKey_stt *privkey = NULL;
*   int32_t retval;
*   membuf_stt mb;  
*   uint8_t preallocated_buffer[4096];
*
*   //Set up the membuf_stt structure to a preallocated (on stack) buffer of 4kB
*   mb.mSize = sizeof(preallocated_buffer);
*   mb.mUsed = 0;
*   mb.pmBuf = preallocated_buffer;
*
*   // Initialize the EC_stt structure with the known values. We also initialize to NULL and zero the unknown parameter
*   ECparams.mAsize = sizeof(ecc_160_a);
*   ECparams.pmA = ecc_160_a;
*   ECparams.mPsize = sizeof(ecc_160_p);
*   ECparams.pmP = ecc_160_p; 
*   ECparams.pmN = ecc_160_n;  
*   ECparams.mNsize = sizeof(ecc_160_n);
*   ECparams.pmB = NULL;    
*   ECparams.mBsize = 0;
*   ECparams.pmGx = ecc_160_xG;  
*   ECparams.mGxsize = sizeof(ecc_160_xG);
*   ECparams.pmGy = ecc_160_yG;  
*   ECparams.mGysize = sizeof(ecc_160_yG);
*
*   // Call the Elliptic Curve initialization function
*   retval = ECCinitEC(&ECparams, &mb);
*   if (retval != 0)
*   {
*     printf("Error! ECCinitEC returned %d\n", retval);
*     return(-1);
*   }
*   //Initialize the point that will contain the generator point
*   retval = ECCinitPoint(&G, &ECparams, &mb);
*   if (retval != 0)
*   {
*     printf("Error! ECCinitPoint returned %d\n", retval);
*     return(-1);
*   }
*
*   //Set the coordinates of the generator point inside G
*   retval = ECCsetPointGenerator(G, &ECparams);
*   if (retval != 0)
*   {
*     printf("Error! ECCsetPointGenerator returned %d\n", retval);
*     return(-1);
*   }
*
*   // Init the point the will keep the result of the scalar multiplication
*   retval = ECCinitPoint(&PubKey, &ECparams, &mb);
*   if (retval != 0)
*   {
*     printf("Error! ECCinitPoint returned %d\n", retval);
*     return(-1);
*   }
*
*   // Initialize the private key object
*   retval = ECCinitPrivKey(&privkey, &ECparams, &mb);
*   if (retval != 0)
*   {
*     printf("Error! ECCinitPrivKey returned %d\n", retval);
*     return(-1);
*   }
*   //Set the private key object
*   retval = ECCsetPrivKeyValue(privkey, ecc_160_privkey, sizeof(ecc_160_privkey));
*   if (retval != 0)
*   {
*     printf("Error! ECCsetPrivKeyValue returned %d\n", retval);
*     return(-1);
*   }
*
*   // All ECCscalarMul parameters are initalized and set, proceed.
*   retval = ECCscalarMul(G, privkey, PubKey, &ECparams, &mb);
*   if (retval != 0 )
*   {
*     printf("ECCscalarMul returned %d\n",retval);
*     return(-1);
*   }
*   // Now PubKey contains the result point, we can get its coordinates through
*   ECCgetPointCoordinate(PubKey, E_ECC_POINT_COORDINATE_X, pubKeyX, &Xsize);
*   ECCgetPointCoordinate(PubKey, E_ECC_POINT_COORDINATE_Y, pubKeyY, &Ysize);
*
*   // Finally we free everything we initialized
*   ECCfreePrivKey(&privkey, &mb);
*   ECCfreePoint(&G, &mb);
*   ECCfreePoint(&PubKey, &mb);
*   ECCfreeEC(&ECparams, &mb);
* }
* \endcode
*
* The following example will generate a key pair (both private and public key) and will use the private 
* key to generate a signature for an hash digest. It will export it and reimport it and verify the signature 
* with the public key. 
*
* This example will assume to have an already initialized EC_stt and RNGstate_stt.
*
* \code
* int32_t ECCkeygen_and_ECDSA_tests(EC_stt * pECparams, RNGstate_stt * pRNGstate)
* {
*  // SHA256("abc")
*  uint8_t digest[CRL_SHA256_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,
*                                     0x22,0x23,0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,
*                                     0xf2,0x00,0x15,0xad};  
*  // Structure that will contain the public key
*  ECpoint_stt *PubKey = NULL;  
*  // Structure that will contain the ECDSA signature
*  ECDSAsignature_stt *sign = NULL;
*  // Structure context used to call the ECDSAverify
*  ECDSAverifyCtx_stt verctx;
*  // Private Key Structure 
*  ECCprivKey_stt *privKey = NULL;
*  // Structure context used to call the ECDSAsign
*  ECDSAsignCtx_stt signCtx;
*  // Used to check the returned values 
*  int32_t retval;
*  //pointers that will keep the byte arrays of the signature object
*  uint8_t *signR = NULL, *signS = NULL;
*  int32_t signRsize, signSsize;
*
*  membuf_stt mb;  
*  uint8_t preallocated_buffer[4096];
*
*  //Set up the membuf_stt structure to a preallocated (on stack) buffer of 4kB
*  mb.mSize = sizeof(preallocated_buffer);
*  mb.mUsed = 0;
*  mb.pmBuf = preallocated_buffer;
*
*  //Init PubKey object
*  retval = ECCinitPoint(&PubKey, pECparams, &mb);
*  if (retval != 0)
*  {
*    printf("Error! ECCinitPoint returned %d\n", retval);
*    goto err;
*  }
*  //Init Privkey object
*  retval = ECCinitPrivKey(&privKey, pECparams, &mb);
*  if (retval != 0)
*  {
*    printf("Error! ECCinitPrivKey returned %d\n", retval);
*    goto err;
*  }
*  //Call the Key Generation Function
*  retval = ECCkeyGen(privKey, PubKey, pRNGstate, pECparams, &mb);
*  if (retval != 0)
*  {
*    printf("Error! ECCkeyGen returned %d\n",retval);
*  }
*  
*  // We proceed to sign the digest of "message" 
*  // First initialize the signature that will be returned
*  retval = ECDSAinitSign(&sign,pECparams, &mb);
*  if (retval != 0)
*  {
*    printf("Error! ECDSAinitSign returned %d\n",retval);
*  }
*  //Then fill the structure used to call to ECDSAsign function
*  // fill the EC_stt
*  signCtx.pmEC = pECparams;
*  // Fill the privkey
*  signCtx.pmPrivKey = privKey;
*  //Fill the random engine state
*  signCtx.pmRNG = pRNGstate;
*
*  // Call the signature generature function
*  retval = ECDSAsign(digest, CRL_SHA256_SIZE, sign, &signCtx, &mb);
*  if (retval != 0)
*  {
*    printf("Error! ECDSAsign returned %d\n",retval);
*  }
*  //The signature now it's inside object sign, let's export it to byte arrays
*  //First, allocate the needed size, which is the size of the curve's order (N)
*  signR = malloc (pECparams->mNsize);
*  signS = malloc (pECparams->mNsize);
*  if (signR == NULL || signS ==NULL ) { ... ERROR... }
*  
*  // Now export the signature
*  retval = ECDSAgetSignature(sign,E_ECDSA_SIGNATURE_R_VALUE, signR, &signRsize);
*  retval |= ECDSAgetSignature(sign,E_ECDSA_SIGNATURE_S_VALUE, signS, &signSsize);
*  if (retval != 0) { ... ERROR... }
*  
*  // Free the signature structure, reinit and reimport signature, this is just for testing...
*  ECDSAfreeSign(&sign, &mb);
*
*  retval = ECDSAinitSign(&sign, pECparams, &mb);
*  if (retval != 0)
*  {
*    printf("Error! ECDSAinitSign returned %d\n",retval);
*  }
*  retval = ECDSAsetSignature(sign,E_ECDSA_SIGNATURE_R_VALUE, signR, signRsize);
*  retval |= ECDSAsetSignature(sign,E_ECDSA_SIGNATURE_S_VALUE, signS, signSsize);
*  if (retval != 0) { ... ERROR... }
*
*  // We now have the signature of the message, we try to verify it
*  // First set the parameters for the verification structure
*  verctx.pmEC = pECparams;
*  verctx.pmPubKey = PubKey;
* 
*  // then we can call the verification function
*  retval = ECDSAverify(digest, CRL_SHA256_SIZE, sign, &verctx, &mb);
*  
*  if (retval == SIGNATURE_VALID)
*  {
*    printf("Signature VALID\n");
*  }
*  else
*  {
*    printf("Error! ECDSAverify returned %d\n",retval);
*  }
*
*  // Before returing clean the memory by freeing the signature and the public key
*  ECDSAfreeSign(sign, &mb);
*  ECCfreePoint(PubKey, &mb);
*  ECCfreePrivKey(privKey, &mb);
*
*  return(retval);
* }
* \endcode
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRL_AccHw_ECC_H__
#define __CRL_AccHw_ECC_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../Math/AccHw_math.h"   



/** @addtogroup ECC
  * @{
  */ 
  
  
   
/** 
  * @brief  Structure continaing the BigNum_stt that describes the parameters of an Elliptic Curve and its generator   
  */
typedef struct
{
  BigNum_stt *pmA;          /*!< Parameter a of the curve equation. */
  BigNum_stt *pmB;          /*!< Parameter b of the curve equation. */
  BigNum_stt *pmP;          /*!< Modulus p. */
  BigNum_stt *pmN;          /*!< Order of the curve n. */
  BigNum_stt *pmGx;         /*!< Coordinate pmX of curve's generator */
  BigNum_stt *pmGy;         /*!< Coordinate pmY of curve's generator*/
} AccHw_intEC_stt;


/** 
  * @brief  Structure that keeps the Elliptic Curve Parameter  
  */ 
typedef struct
{
  const uint8_t *pmA;  /*!< pointer to paramter "a" */
  
  int32_t mAsize;      /*!< size of paramter "a" */
  
  const uint8_t *pmB;  /*!< pointer to paramter "b" */
  
  int32_t mBsize;      /*!< size of paramter "b" */
  
  const uint8_t *pmP;  /*!<pointer to paramter "p" */
  
  int32_t mPsize;      /*!<size of paramter "p" */
  
  const uint8_t *pmN;  /*!< pointer to paramter "n" */
 
  int32_t mNsize;      /*!< size of paramter "n" */
  
  const uint8_t *pmGx; /*!< pointer to x coordinate of generator point */
  
  int32_t mGxsize;     /*!< size of x coordinate of generator point */
  
  const uint8_t *pmGy; /*!< pointer to y coordinate of generator point */
  
  int32_t mGysize;     /*!< size of y coordinate of generator point */
  
  AccHw_intEC_stt *pmInternalEC;  /*!< Pointer to internal structure for handling the parameters */
} AccHw_EC_stt;


/** 
  * @brief  Enumeration to specify the possible flags for an Elliptic Curve Point
  */  
typedef enum AccHw_ECPntFlags_e 
{
  
  AccHw_E_POINT_GENERAL = 0,    /*!< The point is not normalized (Coordinate Z != 1) */
  
  AccHw_E_POINT_NORMALIZED = 1, /*!< The point is normalized (Coordinate Z == 1)*/

  AccHw_E_POINT_INFINITY = 2,   /*!< The point is the O point */
  
  AccHw_E_POINT_MONTY = 4       /*!< The point's coordinates are expressed in Montgomery domain */
} AccHw_ECPntFlags_et;

/** 
  * @brief  Object used to store an elliptic curve point.
  */
typedef struct
 {
 
  BigNum_stt *pmX ;     /*!< pmX coordinate. */
 
  BigNum_stt *pmY ;     /*!< pmY coordinate. */
 
  BigNum_stt *pmZ ;     /*!< pmZ coordinate, used in projective representations. */
  
  AccHw_ECPntFlags_et mFlag;  /*!< Point Flag, allowed values are: \n
                         * - flag=CRL_EPOINT_GENERAL for a point which may have pmZ different from 1
                         * - flag=CRL_EPOINT_NORMALIZED for a point which has pmZ equal to 1
                         * - flag=CRL_EPOINT_INFINITY to denote the infinity point
                        */
} AccHw_ECpoint_stt;

/** 
  * @brief   Enumeration for the coordinates of an elliptic curve point
  */  
typedef enum AccHw_ECcoordinate_e 
{  
  AccHw_E_ECC_POINT_COORDINATE_X = 0,  /*!< Coordinate X */
  
  AccHw_E_ECC_POINT_COORDINATE_Y = 1,   /*!< Coordinate Y */
 
  AccHw_E_ECC_POINT_COORDINATE_Z = 2,   /*!< Coordinate Z */
} AccHw_ECcoordinate_et;


/** 
  * @brief   Object used to store an ECC private key
  */  
typedef struct 
{ 
  BigNum_stt *pmD;   /*!<  BigNum Representing the Private Key */
} AccHw_ECCprivKey_stt;

/** 
  * @brief   Object used to store an ECDSA signature
  */  
typedef struct
{
  /** R */
  BigNum_stt *pmR ;  /*!< pointer to paramter R*/
  /** S */
  BigNum_stt *pmS ; /*!< pointer to paramter S*/
} AccHw_ECDSAsignature_stt;


/** 
  * @brief  Enumeration for the values inside the ECDSA signature
  */  
typedef enum AccHw_ECDSAsignValues_e 
{
  AccHw_E_ECDSA_SIGNATURE_R_VALUE = 0,  /*!<  Value R  */
  AccHw_E_ECDSA_SIGNATURE_S_VALUE = 1,  /*!<  Value S */
} AccHw_ECDSAsignValues_et;

/** 
  * @brief  Structure used in ECDSA signature verification function
  */
typedef struct
 {
  
  AccHw_ECpoint_stt *pmPubKey;  /*!<  Pointer to the ECC Public Key used in the verification */
  
  AccHw_EC_stt      *pmEC;      /*!<  Pointer to Elliptic Curve parameters */
} AccHw_ECDSAverifyCtx_stt;

 
/** 
  * @brief  Structure used in ECDSA signature generation function 
  */  
typedef struct 
{
  
  AccHw_ECCprivKey_stt *pmPrivKey;  /*!<  Pointer to the ECC Private Key used in the verification */
  
  AccHw_EC_stt         *pmEC;       /*!<  Pointer to Elliptic Curve parameters */
  
  AccHw_RNGstate_stt   *pmRNG;      /*!<  Pointer to an Initialized Random Engine Status */
} AccHw_ECDSAsignCtx_stt;

/* Exported functions ------------------------------------------------------- */
int32_t AccHw_ECCinitEC(AccHw_EC_stt *P_pECctx, membuf_stt *P_pMemBuf);
int32_t AccHw_ECCfreeEC(AccHw_EC_stt *P_pECctx, membuf_stt *P_pMemBuf);
int32_t AccHw_ECCinitPoint(AccHw_ECpoint_stt **P_ppECPnt, const AccHw_EC_stt *P_pECctx, membuf_stt *P_pMemBuf);
int32_t AccHw_ECCfreePoint(AccHw_ECpoint_stt **P_pECPnt, membuf_stt *P_pMemBuf);
int32_t AccHw_ECCsetPointCoordinate(AccHw_ECpoint_stt *P_pECPnt,
                              AccHw_ECcoordinate_et P_Coordinate,
                              const uint8_t *P_pCoordinateValue,
                              int32_t P_coordinateSize);
int32_t AccHw_ECCgetPointCoordinate(const AccHw_ECpoint_stt *P_pECPnt,
                              AccHw_ECcoordinate_et P_Coordinate,
                              uint8_t *P_pCoordinateValue,
                              int32_t *P_pCoordinateSize);
int32_t AccHw_ECCsetPointGenerator(AccHw_ECpoint_stt *P_pPoint, const AccHw_EC_stt *P_pECctx);
int32_t AccHw_ECCcopyPoint(const AccHw_ECpoint_stt *P_pOriginalPoint, AccHw_ECpoint_stt *P_pCopyPoint);
int32_t AccHw_ECCinitPrivKey(AccHw_ECCprivKey_stt **P_ppECCprivKey, const AccHw_EC_stt *P_pECctx, membuf_stt *P_pMemBuf);
int32_t AccHw_ECCfreePrivKey(AccHw_ECCprivKey_stt **P_pECCprivKey, membuf_stt *P_pMemBuf);
int32_t AccHw_ECCsetPrivKeyValue(AccHw_ECCprivKey_stt *P_pECCprivKey,
                      const uint8_t *P_pPrivateKey,
                      int32_t P_privateKeySize);
int32_t AccHw_ECCgetPrivKeyValue(const AccHw_ECCprivKey_stt *P_pECCprivKey,
                      uint8_t *P_pPrivateKey,
                      int32_t *P_pPrivateKeySize);
int32_t AccHw_ECCscalarMul(const AccHw_ECpoint_stt *P_pECbasePnt,
                     const AccHw_ECCprivKey_stt *P_pECCprivKey,
                     AccHw_ECpoint_stt *P_pECresultPnt,
                     const AccHw_EC_stt *P_pECctx,
                     membuf_stt *P_pMemBuf);
int32_t AccHw_ECDSAinitSign(AccHw_ECDSAsignature_stt **P_ppSignature, const AccHw_EC_stt *P_pECctx, membuf_stt *P_pMemBuf);
int32_t AccHw_ECDSAfreeSign(AccHw_ECDSAsignature_stt **P_pSignature, membuf_stt *P_pMemBuf);
int32_t AccHw_ECDSAsetSignature(AccHw_ECDSAsignature_stt *P_pSignature,
                          AccHw_ECDSAsignValues_et P_RorS,
                          const uint8_t *P_pValue,
                          int32_t P_valueSize);
int32_t AccHw_ECDSAgetSignature(const AccHw_ECDSAsignature_stt *P_pSignature,
                          AccHw_ECDSAsignValues_et P_RorS,
                          uint8_t *P_pValue,
                          int32_t *P_pValueSize);
int32_t AccHw_ECDSAverify(const uint8_t      *P_pDigest,
                    int32_t             P_digestSize,
                    const AccHw_ECDSAsignature_stt   *P_pSignature,
                    const AccHw_ECDSAverifyCtx_stt *P_pVerifyCtx, 
                    membuf_stt *P_pMemBuf);
int32_t AccHw_ECCvalidatePubKey(const AccHw_ECpoint_stt *pECCpubKey, const AccHw_EC_stt *P_pECctx, membuf_stt *P_pMemBuf);
int32_t AccHw_ECCkeyGen(AccHw_ECCprivKey_stt *P_pPrivKey,
                  AccHw_ECpoint_stt    *P_pPubKey,
                  AccHw_RNGstate_stt * P_pRandomState,
                  const AccHw_EC_stt    *P_pECctx,
                  membuf_stt *P_pMemBuf);
int32_t AccHw_ECDSAsign(const uint8_t         *P_pDigest,
                  int32_t                P_digestSize,
                  const AccHw_ECDSAsignature_stt *P_pSignature,
                  const AccHw_ECDSAsignCtx_stt *P_pSignCtx, 
                  membuf_stt *P_pMemBuf);
int32_t AccHw_ECCgetPointFlag(const AccHw_ECpoint_stt *P_pECPnt);
void AccHw_ECCsetPointFlag(AccHw_ECpoint_stt *P_pECPnt, AccHw_ECPntFlags_et P_newFlag);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __ECC_AccHw_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
