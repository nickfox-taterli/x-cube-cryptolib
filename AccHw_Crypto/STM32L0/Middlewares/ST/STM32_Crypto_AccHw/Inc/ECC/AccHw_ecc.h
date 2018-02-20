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
  
//  AccHw_RNGstate_stt   *pmRNG;      /*!<  Pointer to an Initialized Random Engine Status */
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
//                  AccHw_RNGstate_stt * P_pRandomState,
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
