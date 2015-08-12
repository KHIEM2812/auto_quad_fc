/**
  ******************************************************************************
  * @file    EncAlignCtrlClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of EncAlignCtrl class      
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
#ifndef __ENCALIGNCTRLCLASS_H
#define __ENCALIGNCTRLCLASS_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"
#include "SpeednTorqCtrlClass.h"
#include "VirtualSpeedSensor_SpeednPosFdbkClass.h"
#include "ENCODER_SpeednPosFdbkClass.h"

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */

/** @addtogroup EncAlignCtrl
  * @{
  */
  
/** @defgroup EncAlignCtrl_class_exported_types EncAlignCtrl class exported types
* @{
*/

/** 
  * @brief  Public EncAlignCtrl class definition 
  */
typedef struct CEAC_t *CEAC;

/** 
  * @brief  EncAlignCtrl class parameters definition  
  */
typedef const struct
{
  uint16_t hEACFrequencyHz; /*!< Frequency expressed in Hz at which the user 
                                 clocks the EAC calling EAC_Exec method */
  int16_t hFinalTorque;     /*!< Motor torque reference imposed by STC at the 
                                 end of programmed alignment. This value 
                                 represents actually the Iq current expressed in
                                 digit.*/
  int16_t hElAngle;        /*!< Electrical angle of programmed alignment 
                                 expressed in s16degrees.*/
  uint16_t hDurationms;     /*!< Duration of the programmed alignment expressed
                                 in milliseconds.*/
}EncAlignCtrlParams_t, *pEncAlignCtrlParams_t;
  
/**
* @}
*/

/** @defgroup EncAlignCtrl_class_exported_methods EncAlignCtrl class exported methods
  * @{
  */

/**
  * @brief  Creates an object of the class EncAlignCtrl
  * @param  pEncAlignCtrlParams pointer to an EncAlignCtrl parameters structure
  * @retval CEAC new instance of EncAlignCtrl object
  */
CEAC EAC_NewObject(pEncAlignCtrlParams_t pEncAlignCtrlParams);

/**
  * @brief  Initializes all the object variables, usually it has to be called 
  *         once right after object creation. It is also used to assign the 
  *         speed and torque controller, the virtual speed sensor objects and 
  *         the encoder object to be used by encoder alignment controller.
  * @param  this related object of class CEAC.
  * @param  oSTC the speed and torque controller used by the EAC.
  * @param  oVSS the virtual speed sensor used by the EAC.
  * @param  oENC the encoder object used by the EAC.
  * @retval none.
  */
void EAC_Init(CEAC this, CSTC oSTC, CVSS_SPD oVSS, CENC_SPD oENC );

/**
  * @brief  It is called to start the encoder alignment procedure.
  *	       	It configure the VSS with the required angle and sets the STC to 
  *         execute the required torque ramp.
  * @param  this related object of class CEAC.
  * @retval none.
  */
void EAC_StartAlignment(CEAC this);

/**
  * @brief  It clocks the encoder alignment controller and must be called with a 
  *         frequency equal to the one settled in the parameters 
  *         hEACFrequencyHz. Calling this method the EAC is possible to verify 
  *         if the alignment duration has been finished. At the end of alignment 
  *         the encoder object it is set to the defined electrical angle.
  *         Note: STC, VSS, ENC are not clocked by EAC_Exec.
  * @param  this related object of class CEAC.
  * @retval bool It returns TRUE when the programmed alignment has been 
  *         completed. 
  */
bool EAC_Exec(CEAC this);
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __ENCALIGNCTRLCLASS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
