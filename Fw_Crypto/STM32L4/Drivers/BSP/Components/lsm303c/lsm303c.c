/**
  ******************************************************************************
  * @file    lsm303c.c
  * @author  MCD Application Team
  * @version V0.1.0
  * @date    10-February-2105
  * @brief   This file provides a set of functions needed to manage the LSM303C
  *          MEMS accelerometer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
/* Includes ------------------------------------------------------------------*/
#include "lsm303c.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 

/** @addtogroup LSM303C
  * @{
  */

/** @defgroup LSM303C_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LSM303C_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup LSM303C_Private_Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LSM303C_Private_Functions
  * @{
  */

/* ACC functions */
void    LSM303C_AccInit(uint16_t InitStruct);
uint8_t LSM303C_AccReadID(void);
//void    LSM303C_AccRebootCmd(void);
void    LSM303C_AccFilterConfig(uint8_t FilterStruct);
void    LSM303C_AccFilterCmd(uint8_t HighPassFilterState);
void    LSM303C_AccReadXYZ(int16_t* pData);
void    LSM303C_AccFilterClickCmd(uint8_t HighPassFilterClickState);
void    LSM303C_AccIT1Enable(uint8_t LSM303C_IT);
void    LSM303C_AccIT1Disable(uint8_t LSM303C_IT);
void    LSM303C_AccIT2Enable(uint8_t LSM303C_IT);
void    LSM303C_AccIT2Disable(uint8_t LSM303C_IT);
//void    LSM303C_AccINT1InterruptEnable(uint8_t ITCombination, uint8_t ITAxes);
//void    LSM303C_AccINT1InterruptDisable(uint8_t ITCombination, uint8_t ITAxes);
//void    LSM303C_AccINT2InterruptEnable(uint8_t ITCombination, uint8_t ITAxes);
//void    LSM303C_AccINT2InterruptDisable(uint8_t ITCombination, uint8_t ITAxes);
void    LSM303C_AccClickITEnable(uint8_t ITClick);
void    LSM303C_AccClickITDisable(uint8_t ITClick);
void    LSM303C_AccZClickITConfig(void);

/* MAG functions */
void    LSM303C_MagInit(MAGNETO_InitTypeDef LSM303C_InitStruct);
uint8_t LSM303C_MagReadID(void);
void    LSM303C_MagReadXYZ(int16_t* pData);
uint8_t LSM303C_MagGetDataStatus(void);


/* COMPASS / ACCELERO IO functions */
extern void    ACCELERO_IO_Init(void);
extern void    ACCELERO_IO_ITConfig(void);
extern void    ACCELERO_IO_Write(uint8_t RegisterAddr, uint8_t Value);
extern uint8_t ACCELERO_IO_Read(uint8_t RegisterAddr);

/* COMPASS IO function */
extern void    MAGNETO_IO_Init(void);
extern void    MAGNETO_IO_ITConfig(void);
extern void    MAGNETO_IO_Write(uint8_t RegisterAddr, uint8_t Value);
extern uint8_t MAGNETO_IO_Read(uint8_t RegisterAddr);

/**
  * @}
  */ 


/** @defgroup LSM303C_Private_Variables
  * @{
  */ 
ACCELERO_DrvTypeDef Lsm303cDrv_accelero =
{
  LSM303C_AccInit,
  LSM303C_AccReadID,
  0, //  LSM303C_AccRebootCmd,
  0, //LSM303C_AccZClickITConfig,
  0,
  0,
  0,
  0,
  LSM303C_AccFilterConfig,
  0, //LSM303C_AccFilterCmd,
  LSM303C_AccReadXYZ
};

MAGNETO_DrvTypeDef Lsm303cDrv_magneto =
{
  LSM303C_MagInit,
  LSM303C_MagReadID,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  LSM303C_MagReadXYZ
  
};

/**
  * @}
  */


/**
  * @brief  Set LSM303C Initialization.
  * @param  InitStruct: Init parameters
  * @retval None
  */
void LSM303C_AccInit(uint16_t InitStruct)
{  
  uint8_t ctrl = 0x00;
  
  /*  Low level init */
  ACCELERO_IO_Init();
  
  /* Write value to ACC MEMS CTRL_REG1 register */
  ctrl = (uint8_t) InitStruct;
  ACCELERO_IO_Write(LSM303C_CTRL_REG1_A, ctrl);
  
  /* Write value to ACC MEMS CTRL_REG4 register */
  ctrl = ((uint8_t) (InitStruct >> 8));
  ACCELERO_IO_Write(LSM303C_CTRL_REG4_A, ctrl);
}

/**
  * @brief  Read LSM303C ID.
  * @param  None
  * @retval ID 
  */
uint8_t LSM303C_AccReadID(void)
{  
  uint8_t ctrl = 0x00;
  
  /* Low level init */
  ACCELERO_IO_Init();
  
  /* Enabled SPI/I2C read communication */
  ACCELERO_IO_Write(LSM303C_CTRL_REG4_A, 0x5);
  
  /* Read value at Who am I register address */
  ctrl = ACCELERO_IO_Read(LSM303C_WHO_AM_I_ADDR);
  
  return ctrl;
}

/**
  * @brief  Set High Pass Filter Modality
  * @param  FilterStruct: contains data for filter config
  * @retval None
  */
void LSM303C_AccFilterConfig(uint8_t FilterStruct) 
{
  uint8_t tmpreg;
  
//  /* Read CTRL_REG2 register */
//  tmpreg = ACCELERO_IO_Read(LSM303C_CTRL_REG2_A);
//  
//  tmpreg &= 0x0C;
  tmpreg = FilterStruct;
  
  /* Write value to ACC MEMS CTRL_REG2 register */
  ACCELERO_IO_Write(LSM303C_CTRL_REG2_A, tmpreg);
}

/**
  * @brief  Read X, Y & Z Acceleration values 
  * @param  pData: Data out pointer
  * @retval None
  */
void LSM303C_AccReadXYZ(int16_t* pData)
{
  int16_t pnRawData[3];
  uint8_t ctrlx[2]={0,0};
  uint8_t buffer[6];
  uint8_t i = 0;
  uint8_t sensitivity = LSM303C_ACC_SENSITIVITY_2G;
  
  /* Read the acceleration control register content */
  ctrlx[0] = ACCELERO_IO_Read(LSM303C_CTRL_REG4_A);
  ctrlx[1] = ACCELERO_IO_Read(LSM303C_CTRL_REG5_A);
  
  /* Read output register X, Y & Z acceleration */
  buffer[0] = ACCELERO_IO_Read(LSM303C_OUT_X_L_A); 
  buffer[1] = ACCELERO_IO_Read(LSM303C_OUT_X_H_A);
  buffer[2] = ACCELERO_IO_Read(LSM303C_OUT_Y_L_A);
  buffer[3] = ACCELERO_IO_Read(LSM303C_OUT_Y_H_A);
  buffer[4] = ACCELERO_IO_Read(LSM303C_OUT_Z_L_A);
  buffer[5] = ACCELERO_IO_Read(LSM303C_OUT_Z_H_A);
  
  /* Check in the control register4 the data alignment*/
//  if(!(ctrlx[0] & LSM303C_BLE_MSB)) 
//  {
//    for(i=0; i<3; i++)
//    {
//      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i]);
//    }
//  }
//  else /* Big Endian Mode */
  {
    for(i=0; i<3; i++)
    {
      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i]);
    }
  }
  
  /* Normal mode */
  /* Switch the sensitivity value set in the CRTL4 */
  switch(ctrlx[0] & LSM303C_ACC_FULLSCALE_8G)
  {
  case LSM303C_ACC_FULLSCALE_2G:
    sensitivity = LSM303C_ACC_SENSITIVITY_2G;
    break;
  case LSM303C_ACC_FULLSCALE_4G:
    sensitivity = LSM303C_ACC_SENSITIVITY_4G;
    break;
  case LSM303C_ACC_FULLSCALE_8G:
    sensitivity = LSM303C_ACC_SENSITIVITY_8G;
    break;
  }
  
  /* Obtain the mg value for the three axis */
  for(i=0; i<3; i++)
  {
    pData[i]=(pnRawData[i] * sensitivity);
  }
}

/***********************************************************************************************
  Magnetometer driver 
***********************************************************************************************/

/**
  * @brief  Set LSM303C Mag Initialization.
  * @param  LSM303C_InitStruct: pointer to a LSM303C_MagInitTypeDef structure 
  *         that contains the configuration setting for the LSM303C.
  * @retval None
  */
void LSM303C_MagInit(MAGNETO_InitTypeDef LSM303C_InitStruct)
{  
  MAGNETO_IO_Write(LSM303C_CTRL_REG1_M, LSM303C_InitStruct.Register1);
  uint8_t tmp = MAGNETO_IO_Read(LSM303C_CTRL_REG1_M);
  MAGNETO_IO_Write(LSM303C_CTRL_REG2_M, LSM303C_InitStruct.Register2);
  tmp = MAGNETO_IO_Read(LSM303C_CTRL_REG2_M);
  MAGNETO_IO_Write(LSM303C_CTRL_REG3_M, LSM303C_InitStruct.Register3);
  tmp = MAGNETO_IO_Read(LSM303C_CTRL_REG3_M);
  MAGNETO_IO_Write(LSM303C_CTRL_REG4_M, LSM303C_InitStruct.Register4);
  tmp = MAGNETO_IO_Read(LSM303C_CTRL_REG4_M);
  MAGNETO_IO_Write(LSM303C_CTRL_REG5_M, LSM303C_InitStruct.Register5);
  tmp = MAGNETO_IO_Read(LSM303C_CTRL_REG5_M);
}

/**
  * @brief  Read LSM303C ID.
  * @param  None
  * @retval ID 
  */
uint8_t LSM303C_MagReadID(void)
{  
  /* Low level init */
  MAGNETO_IO_Init();
  
  /* Enabled the SPI/I2C read operation */
  MAGNETO_IO_Write(LSM303C_CTRL_REG3_M, 0x84);
  
  /* Read value at Who am I register address */
  return MAGNETO_IO_Read(LSM303C_WHO_AM_I_ADDR);
}

/**
  * @brief  Get status for Mag LSM303C data
  * @param  None
  * @retval Data status in a LSM303C Data register
  */
uint8_t LSM303C_MagGetDataStatus(void)
{
  /* Read Mag STATUS register */
  return MAGNETO_IO_Read(LSM303C_STATUS_REG_M);
}

/**
  * @brief  Read X, Y & Z Magnetometer values 
  * @param  pData: Data out pointer
  * @retval None
  */
void LSM303C_MagReadXYZ(int16_t* pData)
{
  uint8_t ctrlx;
  uint8_t buffer[6];
  
  /* Read the magnetometer control register content */
  ctrlx = MAGNETO_IO_Read(LSM303C_CTRL_REG4_M);

  /* Read output register X, Y & Z magnetometer */
  buffer[0] = MAGNETO_IO_Read(LSM303C_OUT_X_L_M); 
  buffer[1] = MAGNETO_IO_Read(LSM303C_OUT_X_H_M);
  buffer[2] = MAGNETO_IO_Read(LSM303C_OUT_Y_L_M);
  buffer[3] = MAGNETO_IO_Read(LSM303C_OUT_Y_H_M);
  buffer[4] = MAGNETO_IO_Read(LSM303C_OUT_Z_L_M);
  buffer[5] = MAGNETO_IO_Read(LSM303C_OUT_Z_H_M);
  
  /* Check in the control register4 the data alignment*/
  if((ctrlx & LSM303C_MAG_BLE_MSB)) 
  {
    for(uint8_t i=0; i<3; i++)
    {
      pData[i]=((int16_t)((uint16_t)buffer[2*i] << 8) + buffer[2*i+1]);
    }
  }
  else
  {
    for(uint8_t i=0; i<3; i++)
    {
      pData[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i]);
    }
  }
}

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
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/     
