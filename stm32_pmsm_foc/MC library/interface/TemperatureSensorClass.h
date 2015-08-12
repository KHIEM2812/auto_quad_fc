/**
  ******************************************************************************
  * @file    TemperatureSensorClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of Temperature Sensor class      
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
#ifndef __TEMPERATURESENSORCLASS_H
#define __TEMPERATURESENSORCLASS_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"
#include "PWMnCurrFdbkClass.h"

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */

/** @addtogroup TemperatureSensor
  * @{
  */
  
/** @defgroup Temperature_Sensor_class_exported_types Temperature Sensor class exported types
* @{
*/

/** 
  * @brief  Public temperature sensor class definition 
  */
typedef struct CTSNS_t *CTSNS;

/** 
  * @brief  Temperature sensor class parameters definition  
  */
typedef const struct
{
  SensorType_t  bSensorType;   /*!< It contains the information about the type 
                                   of instanced temperature sensor object.  
                                   It can be equal to REAL_SENSOR or 
                                   VIRTUAL_SENSOR */
}TempSensorParams_t, *pTempSensorParams_t;
  
/**
* @}
*/

/** @defgroup Temperature_sensor_class_exported_methods Temperature sensor class exported methods
  * @{
  */

/**
  * @brief  It initializes temperature sensing conversions. It must be called 
  *         only after current sensor initialization (PWMC_Init)
  * @param  this related object of class CTSNS
  * @param  oPWMnCurrentSensor CPWMC object to be used for regular conversions
  * @retval none
  */
void TSNS_Init(CTSNS this, CPWMC oPWMnCurrentSensor);

/**
  * @brief  It clears FW variable containing average temperature measurement 
  *         value
  * @param  this related object of class CTSNS
  * @retval none
  */
void TSNS_Clear(CTSNS this);

/**
  * @brief  It clock the temperature sensing. It performes ADC conversion and 
  *         updates the average. It returns MC_OVER_TEMP or 
  *         MC_NO_ERROR depending on temperature average value measurement 
  *         and protection threshold values
  * @param  this related object of class CTSNS
  * @retval uint16_t Fault code error
  */
uint16_t TSNS_CalcAvTemp(CTSNS this);

/**
  * @brief  It return latest averaged temperature measurement expressed in 
  *         u16Celsius
  * @param  this related object of class CTSNS
  * @retval uint16_t Latest averaged temperature measurement in u16Celsius
  */
uint16_t TSNS_GetAvTemp_d(CTSNS this);

/**
  * @brief  It returns latest averaged temperature measurement expressed in 
  *         Celsius degrees
  * @param  this related object of class CTSNS
  * @retval int16_t Latest averaged temperature measurement in Celsius degrees
  */
int16_t TSNS_GetAvTemp_C(CTSNS this);


/**
  * @brief  It returns MC_OVER_TEMP or MC_NO_ERROR depending on
  *         temperature measurement and protection threshold values
  * @param  this related object of class CTSNS
  * @retval uint16_t Fault code error
  */
uint16_t TSNS_CheckTemp(CTSNS this);
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __TEMPERATURESENSORCLASS_H */
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
