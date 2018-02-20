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

/** @addtogroup stm32l1xx
  * @{
  */
    
#ifndef __AccHw_STM32L1XX_H
#define __AccHw_STM32L1XX_H

#ifdef __cplusplus
 extern "C" {
#endif 
  
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
  __IO uint32_t CFGR;          /*!< RCC Clock configuration register,                             Address offset: 0x08 */
  __IO uint32_t CIR;           /*!< RCC Clock interrupt register,                                 Address offset: 0x0C */
  __IO uint32_t AHBRSTR;       /*!< RCC AHB peripheral reset register,                            Address offset: 0x10 */
  __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           Address offset: 0x14 */
  __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           Address offset: 0x18 */
  __IO uint32_t AHBENR;        /*!< RCC AHB peripheral clock enable register,                     Address offset: 0x1C */
  __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                    Address offset: 0x20 */
  __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                    Address offset: 0x24 */
  __IO uint32_t AHBLPENR;      /*!< RCC AHB peripheral clock enable in low power mode register,   Address offset: 0x28 */
  __IO uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register,  Address offset: 0x2C */
  __IO uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register,  Address offset: 0x30 */
  __IO uint32_t CSR;           /*!< RCC Control/status register,                                  Address offset: 0x34 */
} AccHw_RCC_TypeDef;


/** @addtogroup Peripheral_registers_structures
  * @{
  */   
  
/** @addtogroup Peripheral_memory_map
  * @{
  */
#define AccHw_PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */


/*!< Peripheral memory map */
#define AccHw_AHBPERIPH_BASE        (AccHw_PERIPH_BASE + 0x20000)


#define AccHw_RCC_BASE              (AccHw_AHBPERIPH_BASE + 0x3800)

#define AccHw_AES_BASE              ((uint32_t)0x50060000)
/**
  * @}
  */
  
/** @addtogroup Peripheral_declaration
  * @{
  */  

#define AccHw_RCC                 ((AccHw_RCC_TypeDef *) AccHw_RCC_BASE)

#define AccHw_AES                 ((AccHw_AES_TypeDef *) AccHw_AES_BASE)

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
#define  AccHw_AES_CR_ERRC                         ((uint32_t)0x00000100)        /*!< Error Clear */
#define  AccHw_AES_CR_DMAINEN                      ((uint32_t)0x00000800)        /*!< DMA ENable managing the data input phase */
#define  AccHw_AES_CR_DMAOUTEN                     ((uint32_t)0x00001000)        /*!< DMA Enable managing the data output phase */

/*******************  Bit definition for AES_SR register  *********************/
#define  AccHw_AES_SR_CCF                          ((uint32_t)0x00000001)        /*!< Computation Complete Flag */

/******************************************************************************/
/*                                                                            */
/*                      Reset and Clock Control (RCC)                         */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for RCC_AHBENR register  ******************/

#define  AccHw_RCC_AHBENR_AESEN                    ((uint32_t)0x08000000)        /*!< AES clock enable */


/**
  * @}
  */

 /**
  * @}
  */ 



/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __AccHw_STM32L1XX_H */

/**
  * @}
  */

  /**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
