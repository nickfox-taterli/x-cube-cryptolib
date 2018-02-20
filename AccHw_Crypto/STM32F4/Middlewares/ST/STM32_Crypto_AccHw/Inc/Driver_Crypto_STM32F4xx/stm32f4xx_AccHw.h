/**
  ******************************************************************************
  * @file    stm32f217xx.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   CMSIS STM32F217xx Device Peripheral Access Layer Header File.
  *          This file contains :
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral’s registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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

/** @addtogroup stm32f217xx
  * @{
  */

#ifndef __AccHw_STM32F21x_H
#define __AccHw_STM32F21x_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /** @addtogroup Peripheral_interrupt_number_definition
    * @{
    */

  /** @addtogroup Peripheral_registers_structures
    * @{
    */

  /**
    * @brief Crypto Processor
    */

  typedef struct
  {
    __IO uint32_t CR;     /*!< CRYP control register,                            Address offset: 0x00 */
    __IO uint32_t SR;     /*!< CRYP status register,                             Address offset: 0x04 */
    __IO uint32_t DR;     /*!< CRYP data input register,                         Address offset: 0x08 */
    __IO uint32_t DOUT;   /*!< CRYP data output register,                        Address offset: 0x0C */
    __IO uint32_t DMACR;  /*!< CRYP DMA control register,                        Address offset: 0x10 */
    __IO uint32_t IMSCR;  /*!< CRYP interrupt mask set/clear register,           Address offset: 0x14 */
    __IO uint32_t RISR;   /*!< CRYP raw interrupt status register,               Address offset: 0x18 */
    __IO uint32_t MISR;   /*!< CRYP masked interrupt status register,            Address offset: 0x1C */
    __IO uint32_t K0LR;   /*!< CRYP key left  register 0,                        Address offset: 0x20 */
    __IO uint32_t K0RR;   /*!< CRYP key right register 0,                        Address offset: 0x24 */
    __IO uint32_t K1LR;   /*!< CRYP key left  register 1,                        Address offset: 0x28 */
    __IO uint32_t K1RR;   /*!< CRYP key right register 1,                        Address offset: 0x2C */
    __IO uint32_t K2LR;   /*!< CRYP key left  register 2,                        Address offset: 0x30 */
    __IO uint32_t K2RR;   /*!< CRYP key right register 2,                        Address offset: 0x34 */
    __IO uint32_t K3LR;   /*!< CRYP key left  register 3,                        Address offset: 0x38 */
    __IO uint32_t K3RR;   /*!< CRYP key right register 3,                        Address offset: 0x3C */
    __IO uint32_t IV0LR;  /*!< CRYP initialization vector left-word  register 0, Address offset: 0x40 */
    __IO uint32_t IV0RR;  /*!< CRYP initialization vector right-word register 0, Address offset: 0x44 */
    __IO uint32_t IV1LR;  /*!< CRYP initialization vector left-word  register 1, Address offset: 0x48 */
    __IO uint32_t IV1RR;  /*!< CRYP initialization vector right-word register 1, Address offset: 0x4C */
  }
  AccHw_CRYP_TypeDef;

  /**
    * @brief RNG
    */

  typedef struct
  {
    __IO uint32_t CR;  /*!< RNG control register, Address offset: 0x00 */
    __IO uint32_t SR;  /*!< RNG status register,  Address offset: 0x04 */
    __IO uint32_t DR;  /*!< RNG data register,    Address offset: 0x08 */
  }
  AccHw_RNG_TypeDef;





  /**
    * @brief Peripheral_memory_map
    */
#define AccHw_PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

  /*!< Peripheral memory map */
#define AccHw_AHB2PERIPH_BASE       (AccHw_PERIPH_BASE + 0x10000000)


  /*!< AHB2 peripherals */
#define AccHw_CRYP_BASE             (AccHw_AHB2PERIPH_BASE + 0x60000)
#define AccHw_RNG_BASE              (AccHw_AHB2PERIPH_BASE + 0x60800)

  /**
    * @}
    */

  /** @addtogroup Peripheral_declaration
    * @{
    */

#define AccHw_CRYP                ((AccHw_CRYP_TypeDef *) AccHw_CRYP_BASE)
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
  /*                            Crypto Processor                                */
  /*                                                                            */
  /******************************************************************************/
  /******************* Bits definition for CRYP_CR register  ********************/
#define AccHw_CRYP_CR_ALGODIR                      ((uint32_t)0x00000004)
#define AccHw_CRYP_CR_ALGOMODE                     ((uint32_t)0x00000038)
#define AccHw_CRYP_CR_DATATYPE                     ((uint32_t)0x000000C0)
#define AccHw_CRYP_CR_KEYSIZE                      ((uint32_t)0x00000300)
#define AccHw_CRYP_CR_FFLUSH                       ((uint32_t)0x00004000)
#define AccHw_CRYP_CR_CRYPEN                       ((uint32_t)0x00008000)

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
#endif /* __cplusplus */

#endif /* __STM32F217xx_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

