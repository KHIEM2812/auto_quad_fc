/**
  ******************************************************************************
  * @file    Virtual_TemperatureSensorClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of Virtual Vbus sensor class      
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
#ifndef __VIRTUAL_TEMPERATURESENSORCLASS_H
#define __VIRTUAL_TEMPERATURESENSORCLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup TemperatureSensor_Virtual
  * @{
  */

/** @defgroup VirtualTemp_class_exported_types Virtual Temperature sensor class exported types
* @{
*/

/** 
  * @brief  Public Virtual Temperature sensor class definition
  */
typedef struct CVTS_TSNS_t *CVTS_TSNS;

/** 
  * @brief  Virtual temperature sensor class parameters definition
  */
typedef const struct
{ 
  uint16_t hExpectedTemp_d;          /*!< Value returned by base class method
										  TSNS_GetAvTemp_d */
  int16_t  hExpectedTemp_C;          /*!< Expected temperature in degrees 
										  (value returned by base class method
										   TSNS_GetAvTemp_C) */
}VirtualTParams_t, *pVirtualTParams_t;
/**
  * @}
  */

/** @defgroup VirtualTemp_class_exported_methods Virtual Temperature sensor class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class Virtual temperature sensor
  * @param  pTempSensorParams pointer to an TempSensor parameters 
  *         structure
  * @param  pVirtualParams pointer to a virtual temperature sensor parameters structure
  * @retval CVTS_TSNS new instance of virtual temperature sensor object
  */
CVTS_TSNS VTS_NewObject(pTempSensorParams_t pTempSensorParams, 
                                               pVirtualTParams_t pVirtualParams);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__VIRTUAL_TEMPERATURESENSORCLASS_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
