/**
  ******************************************************************************
  * @file    AccHw_stm32l1xx.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Header File. 
  *          This file contains all the peripheral register's definitions, bits 
  *          definitions and memory mapping for STM32L1xx High-density, Medium-density,
  *          Medium-density and XL-density Plus devices.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral’s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_STDPERIPH_DRIVER"
  *              - To change few application-specific parameters such as the HSE 
  *                crystal frequency
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral’s registers hardware
  *
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l4xx
  * @{
  */
    
#ifndef __AccHw_STM32L4XX_H
#define __AccHw_STM32L4XX_H

#ifdef __cplusplus
 extern "C" {
#endif 
  
/** 
  * @brief AES hardware accelerator
  */

typedef struct
{
  __IO uint32_t CR;          /*!< AES control register,                        Address offset: 0x00 */
  __IO uint32_t SR;          /*!< AES status register,                         Address offset: 0x04 */
  __IO uint32_t DINR;        /*!< AES data input register,                     Address offset: 0x08 */
  __IO uint32_t DOUTR;       /*!< AES data output register,                    Address offset: 0x0C */
  __IO uint32_t KEYR0;       /*!< AES key register 0,                          Address offset: 0x10 */
  __IO uint32_t KEYR1;       /*!< AES key register 1,                          Address offset: 0x14 */
  __IO uint32_t KEYR2;       /*!< AES key register 2,                          Address offset: 0x18 */
  __IO uint32_t KEYR3;       /*!< AES key register 3,                          Address offset: 0x1C */
  __IO uint32_t IVR0;        /*!< AES initialization vector register 0,        Address offset: 0x20 */
  __IO uint32_t IVR1;        /*!< AES initialization vector register 1,        Address offset: 0x24 */
  __IO uint32_t IVR2;        /*!< AES initialization vector register 2,        Address offset: 0x28 */
  __IO uint32_t IVR3;        /*!< AES initialization vector register 3,        Address offset: 0x2C */
  __IO uint32_t KEYR4;       /*!< AES key register 4,                          Address offset: 0x30 */
  __IO uint32_t KEYR5;       /*!< AES key register 5,                          Address offset: 0x34 */
  __IO uint32_t KEYR6;       /*!< AES key register 6,                          Address offset: 0x38 */
  __IO uint32_t KEYR7;       /*!< AES key register 7,                          Address offset: 0x3C */
  __IO uint32_t SUSP0R;      /*!< AES Suspend register 0,                      Address offset: 0x40 */
  __IO uint32_t SUSP1R;      /*!< AES Suspend register 1,                      Address offset: 0x44 */
  __IO uint32_t SUSP2R;      /*!< AES Suspend register 2,                      Address offset: 0x48 */
  __IO uint32_t SUSP3R;      /*!< AES Suspend register 3,                      Address offset: 0x4C */
  __IO uint32_t SUSP4R;      /*!< AES Suspend register 4,                      Address offset: 0x50 */
  __IO uint32_t SUSP5R;      /*!< AES Suspend register 5,                      Address offset: 0x54 */
  __IO uint32_t SUSP6R;      /*!< AES Suspend register 6,                      Address offset: 0x58 */
  __IO uint32_t SUSP7R;      /*!< AES Suspend register 7,                      Address offset: 0x6C */
} AccHw_AES_TypeDef;  

/** 
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t CR;          /*!< RCC clock control register,                                              Address offset: 0x00 */
  __IO uint32_t ICSCR;       /*!< RCC Internal Clock Sources Calibration Register,                         Address offset: 0x04 */
  __IO uint32_t CFGR;        /*!< RCC clock configuration register,                                        Address offset: 0x08 */
  __IO uint32_t PLLCFGR;     /*!< RCC System PLL configuration register,                                   Address offset: 0x0C */
  __IO uint32_t PLLSAI1CFGR; /*!< RCC PLL SAI1 Configuration Register,                                     Address offset: 0x10 */
  __IO uint32_t PLLSAI2CFGR; /*!< RCC PLL SAI2 Configuration Register,                                     Address offset: 0x14 */
  __IO uint32_t CIER;        /*!< RCC Clock Interrupt Enable Register,                                     Address offset: 0x18 */
  __IO uint32_t CIFR;        /*!< RCC Clock Interrupt Flag Register,                                       Address offset: 0x1C */
  __IO uint32_t CICR;        /*!< RCC Clock Interrupt Clear Register,                                      Address offset: 0x20 */
  uint32_t      RESERVED0;   /*!< Reserved,                                                                Address offset: 0x24 */
  __IO uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x28 */
  __IO uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x2C */
  __IO uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x30 */
  uint32_t      RESERVED1;   /*!< Reserved,                                                                Address offset: 0x34 */
  __IO uint32_t APB1RSTR1;   /*!< RCC LowSpeed APB1 macrocells resets Low Word,                            Address offset: 0x38 */
  __IO uint32_t APB1RSTR2;   /*!< RCC LowSpeed APB1 macrocells resets High Word,                           Address offset: 0x3C */
  __IO uint32_t APB2RSTR;    /*!< RCC High Speed APB macrocells resets,                                    Address offset: 0x40 */
  uint32_t      RESERVED2;   /*!< Reserved,                                                                Address offset: 0x44 */
  __IO uint32_t AHB1ENR;     /*!< RCC AHB1 peripheral clock enable register,                               Address offset: 0x48 */
  __IO uint32_t AHB2ENR;     /*!< RCC AHB2 peripheral clock enable register,                               Address offset: 0x4C */
  __IO uint32_t AHB3ENR;     /*!< RCC AHB3 peripheral clock enable register,                               Address offset: 0x50 */
  uint32_t      RESERVED3;   /*!< Reserved,                                                                Address offset: 0x54 */
  __IO uint32_t APB1ENR1;    /*!< RCC LowSpeed APB1 macrocells clock enables Low Word,                     Address offset: 0x58 */
  __IO uint32_t APB1ENR2;    /*!< RCC LowSpeed APB1 macrocells clock enables High Word,                    Address offset: 0x5C */
  __IO uint32_t APB2ENR;     /*!< RCC High Speed APB macrocells clock enabled,                             Address offset: 0x60 */
  uint32_t      RESERVED4;   /*!< Reserved,                                                                Address offset: 0x64 */
  __IO uint32_t AHB1SMENR;   /*!< RCC AHB1 macrocells clocks enables in sleep mode,                        Address offset: 0x60 */
  __IO uint32_t AHB2SMENR;   /*!< RCC AHB2 macrocells clock enables in sleep mode,                         Address offset: 0x64 */
  __IO uint32_t AHB3SMENR;   /*!< RCC AHB3 macrocells clock enables in sleep mode,                         Address offset: 0x70 */
  uint32_t      RESERVED5;   /*!< Reserved,                                                                Address offset: 0x74 */
  __IO uint32_t APB1SMENR1;  /*!< RCC LowSpeed APB1 macrocells clock enables in sleep mode Low Word,       Address offset: 0x78 */
  __IO uint32_t APB1SMENR2;  /*!< RCC LowSpeed APB1 macrocells clock enables in sleep mode High Word,      Address offset: 0x7C */
  __IO uint32_t APB2SMENR;   /*!< RCC High Speed APB macrocells clock enabled in sleep mode,               Address offset: 0x80 */
  uint32_t      RESERVED6;   /*!< Reserved,                                                                Address offset: 0x84 */
  __IO uint32_t CCIPR;       /*!< RCC IPs Clocks Configuration Register,                                   Address offset: 0x88 */
  __IO uint32_t RESERVED7;   /*!< Reserved,                                                                Address offset: 0x8C */
  __IO uint32_t BDCR;        /*!< RCC Vswitch Backup Domain Control Register,                              Address offset: 0x90 */
  __IO uint32_t CSR;         /*!< RCC clock control & status register,                                     Address offset: 0x94 */
} AccHw_RCC_TypeDef;

/**
  * @brief RNG
  */

typedef struct
{
  __IO uint32_t CR;  /*!< RNG control register, Address offset: 0x00 */
  __IO uint32_t SR;  /*!< RNG status register,  Address offset: 0x04 */
  __IO uint32_t DR;  /*!< RNG data register,    Address offset: 0x08 */
} AccHw_RNG_TypeDef;

/** @addtogroup Peripheral_registers_structures
  * @{
  */   
  
/**
  * @}
  */

/** @addtogroup Peripheral_memory_map
  * @{
  */
#define AccHw_PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address */


/*!< Peripheral memory map */
#define AccHw_APB1PERIPH_BASE        AccHw_PERIPH_BASE
#define AccHw_APB2PERIPH_BASE       (AccHw_PERIPH_BASE + 0x00010000)
#define AccHw_AHB1PERIPH_BASE       (AccHw_PERIPH_BASE + 0x00020000)
#define AccHw_AHB2PERIPH_BASE       (AccHw_PERIPH_BASE + 0x08000000)


/*!< AHB1 peripherals */
#define AccHw_RCC_BASE              (AccHw_AHB1PERIPH_BASE + 0x1000)





/*!< AHB2 peripherals */


#define AccHw_AES_BASE              (AccHw_AHB2PERIPH_BASE + 0x08060000)
#define AccHw_RNG_BASE              (AccHw_AHB2PERIPH_BASE + 0x08060800)


/**
  * @}
  */

/** @addtogroup Peripheral_declaration
  * @{
  */
#define AccHw_RCC                 ((AccHw_RCC_TypeDef *) AccHw_RCC_BASE)

#define AccHw_AES                 ((AccHw_AES_TypeDef *) AccHw_AES_BASE)
#define AccHw_RNG                 ((AccHw_RNG_TypeDef *) AccHw_RNG_BASE)

/**
  * @}
  */

/** @addtogroup Exported_constants
  * @{
  */

/** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */

/******************************************************************************/
/*                         Peripheral Registers_Bits_Definition               */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                       Advanced Encryption Standard (AES)                   */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for AES_CR register  *********************/
#define  AccHw_AES_CR_EN                           ((uint32_t)0x00000001)        /*!< AES Enable */
#define  AccHw_AES_CR_DATATYPE                     ((uint32_t)0x00000006)        /*!< Data type selection */
#define  AccHw_AES_CR_DATATYPE_0                   ((uint32_t)0x00000002)        /*!< Bit 0 */
#define  AccHw_AES_CR_DATATYPE_1                   ((uint32_t)0x00000004)        /*!< Bit 1 */

#define  AccHw_AES_CR_MODE                         ((uint32_t)0x00000018)        /*!< AES Mode Of Operation */
#define  AccHw_AES_CR_MODE_0                       ((uint32_t)0x00000008)        /*!< Bit 0 */
#define  AccHw_AES_CR_MODE_1                       ((uint32_t)0x00000010)        /*!< Bit 1 */

#define  AccHw_AES_CR_CHMOD                        ((uint32_t)0x00010060)        /*!< AES Chaining Mode */
#define  AccHw_AES_CR_CHMOD_0                      ((uint32_t)0x00000020)        /*!< Bit 0 */
#define  AccHw_AES_CR_CHMOD_1                      ((uint32_t)0x00000040)        /*!< Bit 1 */
#define  AccHw_AES_CR_CHMOD_2                      ((uint32_t)0x00010000)        /*!< Bit 2 */

#define  AccHw_AES_CR_CCFC                         ((uint32_t)0x00000080)        /*!< Computation Complete Flag Clear */
#define  AES_CR_ERRC                         ((uint32_t)0x00000100)        /*!< Error Clear */
#define  AccHw_AES_CR_CCFIE                        ((uint32_t)0x00000200)        /*!< Computation Complete Flag Interrupt Enable */
#define  AccHw_AES_CR_ERRIE                        ((uint32_t)0x00000400)        /*!< Error Interrupt Enable */
#define  AccHw_AES_CR_DMAINEN                      ((uint32_t)0x00000800)        /*!< Enable data input phase DMA management  */
#define  AccHw_AES_CR_DMAOUTEN                     ((uint32_t)0x00001000)        /*!< Enable data output phase DMA management */

#define  AccHw_AES_CR_GCMPH                         ((uint32_t)0x00006000)        /*!< GCM Phase */
#define  AccHw_AES_CR_GCMPH_0                       ((uint32_t)0x00002000)        /*!< Bit 0 */
#define  AccHw_AES_CR_GCMPH_1                       ((uint32_t)0x00004000)        /*!< Bit 1 */

#define  AccHw_AES_CR_KEYSIZE                       ((uint32_t)0x00040000)        /*!< Key size selection */

/*******************  Bit definition for AES_SR register  *********************/
#define  AccHw_AES_SR_CCF                          ((uint32_t)0x00000001)        /*!< Computation Complete Flag */
#define  AccHw_AES_SR_RDERR                        ((uint32_t)0x00000002)        /*!< Read Error Flag */
#define  AccHw_AES_SR_WRERR                        ((uint32_t)0x00000004)        /*!< Write Error Flag */
#define  AccHw_AES_SR_BUSY                         ((uint32_t)0x00000008)        /*!< Busy Flag */

/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/


/********************  Bit definition for RCC_AHB2ENR register  ***************/

#define  AccHw_RCC_AHB2ENR_AESEN                   ((uint32_t)0x00010000)
#define  AccHw_RCC_AHB2ENR_RNGEN                   ((uint32_t)0x00040000)
        
/******************************************************************************/
/*                                                                            */
/*                                    RNG                                     */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RNG_CR register  *******************/
#define AccHw_RNG_CR_RNGEN                         ((uint32_t)0x00000004)
#define AccHw_RNG_CR_IE                            ((uint32_t)0x00000008)

/********************  Bits definition for RNG_SR register  *******************/
#define AccHw_RNG_SR_DRDY                          ((uint32_t)0x00000001)
#define AccHw_RNG_SR_CECS                          ((uint32_t)0x00000002)
#define AccHw_RNG_SR_SECS                          ((uint32_t)0x00000004)
#define AccHw_RNG_SR_CEIS                          ((uint32_t)0x00000020)
#define AccHw_RNG_SR_SEIS                          ((uint32_t)0x00000040)



/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AccHw_STM32L4XX_H */

/**
  * @}
  */

  /**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
