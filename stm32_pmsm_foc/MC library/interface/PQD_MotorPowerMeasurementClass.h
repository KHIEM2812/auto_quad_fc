/**
  ******************************************************************************
  * @file    PQD_MotorPowerMeasurementClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of PQD class      
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
#ifndef __PQD_MOTORPOWERMEASUREMENTCLASS_H
#define __PQD_MOTORPOWERMEASUREMENTCLASS_H

#include "FOCDriveClass.h"
#include "BusVoltageSensorClass.h"

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup MotorPowerMeasurement_PQD
  * @{
  */

/** @defgroup PQD_class_exported_types PQD class exported types
* @{
*/

/** 
  * @brief  Public PQD class definition
  */
typedef struct CPQD_MPM_t *CPQD_MPM;

/** 
  * @brief  PQD class parameters definition
  */
typedef const struct
{
  int32_t wConvFact; /* It is the conversion factor used to convert the 
                         variables expressed in digit into variables expressed 
                         in physical measurement unit. It is used to convert the
                         power in watts. It must be equal to 
                         (1000 * 3 * Vddµ)/(sqrt(3) * Rshunt * Aop) */
}PQDParams_t, *pPQDParams_t;

/** 
  * @brief  PQD class init struct definition  
  */
typedef struct {
	CFOC oFOC; /*!< FOC drive object used by MPM.*/
	CVBS oVBS; /*!< Bus voltage sensor object used by MPM.*/
} PQD_MPMInitStruct_t, *pPQD_MPMInitStruct_t;


/**
  * @}
  */

/** @defgroup PQD_class_exported_methods PQD class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class PQD
  * @param  pMotorPowerMeasurementParams pointer to an MotorPowerMeasurement parameters structure
  * @param  pPQDParams pointer to an PQD parameters structure
  * @retval CPQD_MPM new instance of PQD object
  */
CPQD_MPM PQD_NewObject(pPQDParams_t pPQDParams);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__PQD_MOTORPOWERMEASUREMENTCLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
