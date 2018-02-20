/**
  ******************************************************************************
  * @file    stm32l476g_discovery_compass.c
  * @author  MCD Application Team
  * @version V0.2.0
  * @date    10-February-2015
  * @brief   This file provides a set of functions needed to manage the compass
  *          (ACCELEROMETER + MAGNETOMETER) MEMS available on STM32L476G-Discovery 
  *          board.
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
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_compass.h"
#include "../Components/lsm303c/lsm303c.h"
#include <math.h>
    
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32L476G_DISCOVERY
  * @{
  */ 

/** @addtogroup STM32L476G_DISCOVERY_COMPASS
  * @{
  */


/** @defgroup STM32L476G_DISCOVERY_COMPASS_Private_TypesDefinitions
  * @{
  */
  
/**
  * @}
  */

/** @defgroup STM32L476G_DISCOVERY_COMPASS_Private_Defines
  * @{
  */
#define PI                         (float)3.14159265f
    
/**
  * @}
  */

/** @defgroup STM32L476G_DISCOVERY_COMPASS_Private_Macros
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup STM32L476G_DISCOVERY_COMPASS_Private_Variables
  * @{
  */ 
static ACCELERO_DrvTypeDef *AccelerometerDrv;
static MAGNETO_DrvTypeDef  *MagnetoDrv;

/**
  * @}
  */

/** @defgroup STM32L476G_DISCOVERY_COMPASS_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup STM32L476G_DISCOVERY_COMPASS_Private_Functions
  * @{
  */
extern void  ACCELERO_IO_DeInit(void);
extern void  MAGNETO_IO_DeInit(void);
extern void  SPIx_DeInit(void);

/**
  * @brief  Set ACCELEROMETER Initialization.
  * @param  None
  * @retval ACCELERO_OK if no problem during initialization
  */
COMPASS_StatusTypeDef BSP_COMPASS_Init(void)
{  
  COMPASS_StatusTypeDef ret = COMPASS_OK;
  uint16_t ctrl = 0x0000;
  ACCELERO_InitTypeDef LSM303C_InitStructure;
  ACCELERO_FilterConfigTypeDef LSM303C_FilterStructure;
  MAGNETO_InitTypeDef LSM303C_InitStructureMag;
 
  if(Lsm303cDrv_accelero.ReadID() != LMS303C_ACC_ID)
  {
    ret = COMPASS_ERROR;
  }
  else
  {
    /* Initialize the gyroscope driver structure */
    AccelerometerDrv = &Lsm303cDrv_accelero;
  
    /* MEMS configuration ------------------------------------------------------*/
    /* Fill the accelerometer structure */
    LSM303C_InitStructure.AccOutput_DataRate = LSM303C_ACC_ODR_50_HZ;
    LSM303C_InitStructure.Axes_Enable= LSM303C_ACC_AXES_ENABLE;
    LSM303C_InitStructure.AccFull_Scale = LSM303C_ACC_FULLSCALE_2G;
    LSM303C_InitStructure.BlockData_Update = LSM303C_ACC_BDU_CONTINUOUS;
    LSM303C_InitStructure.High_Resolution = LSM303C_ACC_HR_DISABLE;
    LSM303C_InitStructure.Communication_Mode = LSM303C_ACC_SPI_MODE;
        
    /* Configure MEMS: data rate, power mode, full scale and axes */
    ctrl =  (LSM303C_InitStructure.High_Resolution | LSM303C_InitStructure.AccOutput_DataRate | \
                       LSM303C_InitStructure.Axes_Enable | LSM303C_InitStructure.BlockData_Update);
    
    ctrl |= (LSM303C_InitStructure.AccFull_Scale | LSM303C_InitStructure.Communication_Mode) << 8;
    
    /* Configure the accelerometer main parameters */
    AccelerometerDrv->Init(ctrl);
  
    /* Fill the accelerometer HPF structure */
    LSM303C_FilterStructure.HighPassFilter_Mode_Selection = LSM303C_ACC_HPM_NORMAL_MODE;
    LSM303C_FilterStructure.HighPassFilter_CutOff_Frequency = LSM303C_ACC_DFC1_ODRDIV50;
    LSM303C_FilterStructure.HighPassFilter_Stat = LSM303C_ACC_HPI2S_INT1_DISABLE | LSM303C_ACC_HPI2S_INT2_DISABLE;
    
    /* Configure MEMS: mode, cutoff frquency, Filter status, Click, AOI1 and AOI2 */
    ctrl = (uint8_t) (LSM303C_FilterStructure.HighPassFilter_Mode_Selection |\
                      LSM303C_FilterStructure.HighPassFilter_CutOff_Frequency|\
                      LSM303C_FilterStructure.HighPassFilter_Stat);

    /* Configure the accelerometer LPF main parameters */
    AccelerometerDrv->FilterConfig(ctrl);
  }  

  if(Lsm303cDrv_magneto.ReadID() != LMS303C_MAG_ID)
  {
    ret = COMPASS_ERROR;
  }
  else
  {
    /* Initialize the gyroscope driver structure */
    MagnetoDrv = &Lsm303cDrv_magneto;
    
    /* MEMS configuration ------------------------------------------------------*/
    /* Fill the COMPASSmeter structure */
    LSM303C_InitStructureMag.Register1 = LSM303C_MAG_TEMPSENSOR_DISABLE | LSM303C_MAG_OM_XY_ULTRAHIGH | LSM303C_MAG_ODR_40_HZ;
    LSM303C_InitStructureMag.Register2 = LSM303C_MAG_FS_16_GA | LSM303C_MAG_REBOOT_DEFAULT | LSM303C_MAG_SOFT_RESET_DEFAULT;
    LSM303C_InitStructureMag.Register3 = LSM303C_MAG_SPI_MODE | LSM303C_MAG_CONFIG_NORMAL_MODE | LSM303C_MAG_CONTINUOUS_MODE;
    LSM303C_InitStructureMag.Register4 = LSM303C_MAG_OM_Z_ULTRAHIGH | LSM303C_MAG_BLE_LSB;
    LSM303C_InitStructureMag.Register5 = LSM303C_MAG_BDU_CONTINUOUS;
    /* Configure the COMPASSmeter main parameters */
    MagnetoDrv->Init(LSM303C_InitStructureMag);
  } 

  return ret;
}

/**
  * @brief  Set COMPASS DeInitialization.
  * @param  None
  * @retval None.
  */
void BSP_COMPASS_DeInit(void)
{
  ACCELERO_IO_DeInit();
  MAGNETO_IO_DeInit();
  SPIx_DeInit();
}

/**
  * @brief  Get XYZ acceleration
  * @param pDataXYZ Pointeur on 3 angular accelerations 
  *                 pDataXYZ[0] = X axis, pDataXYZ[1] = Y axis, pDataXYZ[2] = Z axis
  * @retval None
  */
void BSP_COMPASS_AccGetXYZ(int16_t *pDataXYZ)
{
  if(AccelerometerDrv->GetXYZ!= NULL)
  {   
    AccelerometerDrv->GetXYZ(pDataXYZ);
  }
}

/**
  * @brief  Get XYZ magnetometer
  * @param pDataXYZ Pointeur on 3 magnetometer 
  *                 pDataXYZ[0] = X axis, pDataXYZ[1] = Y axis, pDataXYZ[2] = Z axis 
  * @retval None
  */
void BSP_COMPASS_MagGetXYZ(int16_t *pDataXYZ)
{
  if(MagnetoDrv->GetXYZ!= NULL)
  {   
    MagnetoDrv->GetXYZ(pDataXYZ);
  }
}

/**
  * @brief  Get Headingr
  * @param None
  * @retval the heading value
  */
int16_t BSP_COMPASS_GetHeading(void)
{
  /* Not implemented */  
  return 0;
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
