/**
  ******************************************************************************
  * @file    AccHw_stm32l0xx.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer Header File. 
  *          This file contains all the peripheral register's definitions, bits 
  *          definitions and memory mapping for STM32L0xx devices.  
  *          
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral’s registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


/** @addtogroup stm32l0xx
  * @{
  */
    
#ifndef __AccHw_STM32L0XX_H
#define __AccHw_STM32L0XX_H

#ifdef __cplusplus
 extern "C" {
#endif 
  



/** @addtogroup Peripheral_registers_structures
  * @{
  */   

/** 
  * @brief AES hardware accelerator
  */

typedef struct
{
  __IO uint32_t CR;           /*!< AES control register,                        Address offset: 0x00 */
  __IO uint32_t SR;           /*!< AES status register,                         Address offset: 0x04 */
  __IO uint32_t DINR;         /*!< AES data input register,                     Address offset: 0x08 */
  __IO uint32_t DOUTR;        /*!< AES data output register,                    Address offset: 0x0C */
  __IO uint32_t KEYR0;        /*!< AES key register 0,                          Address offset: 0x10 */
  __IO uint32_t KEYR1;        /*!< AES key register 1,                          Address offset: 0x14 */
  __IO uint32_t KEYR2;        /*!< AES key register 2,                          Address offset: 0x18 */
  __IO uint32_t KEYR3;        /*!< AES key register 3,                          Address offset: 0x1C */
  __IO uint32_t IVR0;         /*!< AES initialization vector register 0,        Address offset: 0x20 */
  __IO uint32_t IVR1;         /*!< AES initialization vector register 1,        Address offset: 0x24 */
  __IO uint32_t IVR2;         /*!< AES initialization vector register 2,        Address offset: 0x28 */
  __IO uint32_t IVR3;         /*!< AES initialization vector register 3,        Address offset: 0x2C */
} AccHw_AES_TypeDef;



/** 
  * @brief Reset and Clock Control
  */
typedef struct
{
  __IO uint32_t CR;            /*!< RCC clock control register,                                   Address offset: 0x00 */
  __IO uint32_t ICSCR;         /*!< RCC Internal clock sources calibration register,              Address offset: 0x04 */
  __IO uint32_t CRRCR;        /*!< RCC Clock recovery RC register,                               Address offset: 0x08 */
  __IO uint32_t CFGR;          /*!< RCC Clock configuration register,                             Address offset: 0x0C */
  __IO uint32_t CIER;          /*!< RCC Clock interrupt enable register,                          Address offset: 0x10 */
  __IO uint32_t CIFR;          /*!< RCC Clock interrupt flag register,                            Address offset: 0x14 */
  __IO uint32_t CICR;          /*!< RCC Clock interrupt clear register,                           Address offset: 0x18 */
  __IO uint32_t IOPRSTR;       /*!< RCC IO port reset register,                                   Address offset: 0x1C */
  __IO uint32_t AHBRSTR;       /*!< RCC AHB peripheral reset register,                            Address offset: 0x20 */
  __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           Address offset: 0x24 */
  __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           Address offset: 0x28 */
  __IO uint32_t IOPENR;        /*!< RCC Clock IO port enable register,                            Address offset: 0x2C */
  __IO uint32_t AHBENR;        /*!< RCC AHB peripheral clock enable register,                     Address offset: 0x30 */
  __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral enable register,                          Address offset: 0x34 */
  __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral enable register,                          Address offset: 0x38 */
  __IO uint32_t IOPSMENR;      /*!< RCC IO port clock enable in sleep mode register,              Address offset: 0x3C */
  __IO uint32_t AHBSMENR;      /*!< RCC AHB peripheral clock enable in sleep mode register,       Address offset: 0x40 */
  __IO uint32_t APB2SMENR;     /*!< RCC APB2 peripheral clock enable in sleep mode register,      Address offset: 0x44 */
  __IO uint32_t APB1SMENR;     /*!< RCC APB1 peripheral clock enable in sleep mode register,      Address offset: 0x48 */
  __IO uint32_t CCIPR;         /*!< RCC clock configuration register,                             Address offset: 0x4C */
  __IO uint32_t CSR;           /*!< RCC Control/status register,                                  Address offset: 0x50 */
} AccHw_RCC_TypeDef;


/** 
  * @brief Random numbers generator
  */
typedef struct 
{
  __IO uint32_t CR;  /*!< RNG control register, Address offset: 0x00 */
  __IO uint32_t SR;  /*!< RNG status register,  Address offset: 0x04 */
  __IO uint32_t DR;  /*!< RNG data register,    Address offset: 0x08 */
} AccHw_RNG_TypeDef;




/**
  * @}
  */
  
/** @addtogroup Peripheral_memory_map
  * @{
  */

#define AccHw_PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

/*!< Peripheral memory map */
#define AccHw_APBPERIPH_BASE        AccHw_PERIPH_BASE
#define AccHw_AHBPERIPH_BASE        (AccHw_PERIPH_BASE + 0x00020000)





#define AccHw_RCC_BASE              (AccHw_AHBPERIPH_BASE + 0x00001000)

#define AccHw_RNG_BASE              (AccHw_AHBPERIPH_BASE + 0x00005000)
#define AccHw_AES_BASE              (AccHw_AHBPERIPH_BASE + 0x00006000)



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
/*                         Peripheral Registers Bits Definition               */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                       Advanced Encryption Standard (AES)                   */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for AES_CR register  *********************/
#define  AccHw_AES_CR_EN                           ((uint32_t)0x00000001)        /*!< AES Enable */
#define  AccHw_AES_CR_DATATYPE                     ((uint32_t)0x00000006)        /*!< Data type selection */
#define  AccHw_AES_CR_DATATYPE_1                   ((uint32_t)0x00000004)        /*!< Bit 1 */

#define  AccHw_AES_CR_MODE_0                       ((uint32_t)0x00000008)        /*!< Bit 0 */
#define  AccHw_AES_CR_MODE_1                       ((uint32_t)0x00000010)        /*!< Bit 1 */

#define  AccHw_AES_CR_CCFC                         ((uint32_t)0x00000080)        /*!< Computation Complete Flag Clear */

/*******************  Bit definition for AES_SR register  *********************/
#define  AccHw_AES_SR_CCF                          ((uint32_t)0x00000001)        /*!< Computation Complete Flag */

/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for RCC_CR register  ********************/

/*****************  Bit definition for RCC_AHBENR register  ******************/
#define  AccHw_RCC_AHBENR_RNGEN                    ((uint32_t)0x00100000)        /*!< RNG clock enable */
#define  AccHw_RCC_AHBENR_CRYPEN                  ((uint32_t)0x01000000)        /*!< Crypto clock enable*/

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

#endif /* __AccHw_STM32L0XX_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
