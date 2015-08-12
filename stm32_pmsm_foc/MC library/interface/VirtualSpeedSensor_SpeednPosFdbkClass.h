/**
  ******************************************************************************
  * @file    VirtualSpeedSensor_SpeednPosFdbkClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of VirtualSpeedSensor class      
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
#ifndef __VIRTUALSPEEDSENSOR_SPEEDNPOSFDBKCLASS_H
#define __VIRTUALSPEEDSENSOR_SPEEDNPOSFDBKCLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup SpeednPosFdbk_VirtualSpeedSensor
  * @{
  */

/** @defgroup VirtualSpeedSensor_class_exported_types VirtualSpeedSensor class exported types
* @{
*/

/** 
  * @brief  Public VirtualSpeedSensor class definition
  */
typedef struct CVSS_SPD_t *CVSS_SPD;

/** 
  * @brief  VirtualSpeedSensor class parameters definition
  */
typedef const struct
{
  uint16_t hSpeedSamplingFreqHz; /*!< Frequency (Hz) at which motor speed is to 
                             be computed. It must be equal to the frequency
                             at which function SPD_CalcAvrgMecSpeed01Hz
                             is called.*/
  int16_t hTransitionSteps; /*< Number of steps to perform the transition phase
                             from CVSS_SPD to other CSPD; if the Transition PHase
                             should last TPH milliseconds, and the FOC Execution
                             Frequency is set to FEF kHz, then
                             hTransitionSteps = TPH * FEF*/
}VirtualSpeedSensorParams_t, *pVirtualSpeedSensorParams_t;
/**
  * @}
  */

/** @defgroup VirtualSpeedSensor_class_exported_methods VirtualSpeedSensor class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class VirtualSpeedSensor
  * @param  pSpeednPosFdbkParams pointer to an SpeednPosFdbk parameters structure
  * @param  pVirtualSpeedSensorParams pointer to an VirtualSpeedSensor parameters structure
  * @retval CVSS_SPD new instance of VirtualSpeedSensor object
  */
CVSS_SPD VSS_NewObject(pSpeednPosFdbkParams_t pSpeednPosFdbkParams, pVirtualSpeedSensorParams_t pVirtualSpeedSensorParams);

/**
  * @brief  Set the mechanical acceleration of virtual sensor. This acceleration
            is defined starting from current mechanical speed, final mechanical
            speed expressed in 0.1Hz and duration expressed in milliseconds.
  * @param  this related object of class CSTC.
  * @param  hFinalMecSpeed01Hz mechanical speed expressed in 0.1Hz assumed by 
            the virtual sensor at the end of the duration.
  * @param  hDurationms Duration expressed in ms. It can be 0 to apply 
            instantaneous the final speed. 
  * @retval none
  */
void  VSPD_SetMecAcceleration(CSPD this, int16_t  hFinalMecSpeed01Hz, 
                              uint16_t hDurationms);

/**
  * @brief  Set the command to Start the transition phase from CVSS_SPD to other CSPD.
            Transition is to be considered ended when Sensor information is
            declared 'Reliable' or if function returned value is FALSE
  * @param  this related object of class CSPD.
  * @param  bool TRUE to Start the transition phase, FALSE has no effect
  * @retval bool TRUE if Transition phase is enabled (started or not), FALSE if
            transition has been triggered but it's actually disabled
            (parameter hTransitionSteps = 0)
  */
bool VSPD_SetStartTransition(CSPD this, bool bCommand);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__VIRTUALSPEEDSENSOR_SPEEDNPOSFDBKCLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
