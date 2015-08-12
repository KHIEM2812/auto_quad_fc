/**
  ******************************************************************************
  * @file    MotorPowerMeasurementClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of MotorPowerMeasurement class      
  ******************************************************************************
  * <br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTORPOWERMEASUREMENTCLASS_H
#define __MOTORPOWERMEASUREMENTCLASS_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */

/** @addtogroup MotorPowerMeasurement
  * @{
  */
  
/** @defgroup MotorPowerMeasurement_class_exported_types MotorPowerMeasurement class exported types
* @{
*/

/** 
  * @brief  Public MotorPowerMeasurement class definition 
  */
typedef struct CMPM_t *CMPM;

/** 
  * @brief  MotorPowerMeasurement class init struct definition  
  */
typedef void* pMPMInitStruct_t;
  
/**
* @}
*/

/** @defgroup MotorPowerMeasurement_class_exported_methods MotorPowerMeasurement class exported methods
  * @{
  */

/**
  * @brief Initializes all the object variables, usually it has to be called 
  *        once right after object creation.
  * @param this related object of class CMPM.
  * @param pMPMInitStruct the pointer of the init structure, required by derived
  *       class, up-casted to pMPMInitStruct_t.
  * @retval none.
  */
void MPM_Init(CMPM this, pMPMInitStruct_t pMPMInitStruct);

/**
  * @brief  It should be called before each motor restart. It clears the 
  *         measurement buffer and initialize the index.
  * @param this related object of class CMPM.
  * @retval none.
  */
void MPM_Clear(CMPM this);

/**
  * @brief  This method should be called with periodicity. It computes and 
  *         returns the measured motor power expressed in watt. It is also used
  *         to fill, with that measure, the buffer used to compute the average
  *         motor power. 
  * @param this related object of class CMPM.
  * @retval int16_t The measured motor power expressed in watt.
  */
int16_t MPM_CalcElMotorPower(CMPM this);

/**
  * @brief  This method is used to get the last measured motor power 
  *         (instantaneous value) expressed in watt.
  * @param this related object of class CMPM.
  * @retval int16_t The last measured motor power (instantaneous value) 
  *         expressed in watt.
  */
int16_t MPM_GetElMotorPowerW(CMPM this);

/**
  * @brief  This method is used to get the average measured motor power 
  *         expressed in watt.
  * @param this related object of class CMPM.
  * @retval int16_t The average measured motor power expressed in watt.
  */
int16_t MPM_GetAvrgElMotorPowerW(CMPM this);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __MOTORPOWERMEASUREMENTCLASS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
