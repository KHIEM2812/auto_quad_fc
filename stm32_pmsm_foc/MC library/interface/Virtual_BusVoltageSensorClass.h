/**
  ******************************************************************************
  * @file    Virtual_BusVoltageSensorClass.h
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
#ifndef __VIRTUAL_BUSVOLTAGESENSORCLASS_H
#define __VIRTUAL_BUSVOLTAGESENSORCLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup BusVoltageSensor_Virtual
  * @{
  */

/** @defgroup Virtual_class_exported_types Virtual Vbus sensor class exported types
* @{
*/

/** 
  * @brief  Public Virtual Vbus sensor class definition
  */
typedef struct CVVBS_VBS_t *CVVBS_VBS;

/** 
  * @brief  Virtual Vbus sensor class parameters definition
  */
typedef const struct
{
  uint16_t hExpectedVbus_d;           /*!< Expected Vbus voltage expressed in 
                                           digital value 
                                          hOverVoltageThreshold(digital value)= 
                                          Over Voltage Threshold (V) * 65536 
                                                          / 500 */                                                                        
}VirtualParams_t, *pVirtualParams_t;
/**
  * @}
  */

/** @defgroup Virtual_class_exported_methods Virtual Vbus sensor class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class Virtual Vbus sensor
  * @param  pBusVoltageSensorParams pointer to an BusVoltageSensor parameters 
  *         structure
  * @param  pVirtualParams pointer to an Virtual Vbus sensor parameters structure
  * @retval CVVBS_VBS new instance of Virtual Vbus sensor object
  */
CVVBS_VBS VVBS_NewObject(pBusVoltageSensorParams_t pBusVoltageSensorParams, 
                                               pVirtualParams_t pVirtualParams);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__VIRTUAL_BUSVOLTAGESENSORCLASS_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
