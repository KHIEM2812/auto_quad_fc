/**
  ******************************************************************************
  * @file    MCTuningClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains private interface of MCTuning class       
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
#ifndef __MCTUNINGCLASSPRIVATE_H
#define __MCTUNINGCLASSPRIVATE_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"

/** @addtogroup STM32F10x_PMSM_MC_Interface
  * @{
  */

/** @addtogroup MCTuning
  * @{
  */
  
/** @defgroup MCTuning_class_exported_types MCTuning class exported types
* @{
*/

/** 
  * @brief  MC tuning internal objects initialization structure type;
  */
typedef struct
{
  CFOC  oFOCDrive;
  CPI   oPIDSpeed;
  CPI   oPIDIq;
  CPI   oPIDId;
  CPI   oPIDFluxWeakening;
  CPWMC oPWMnCurrFdbk;
  CRUC  oRevupCtrl;
  CSPD  oSpeedSensorMain;
  CSPD  oSpeedSensorAux;
  CSPD  oSpeedSensorVirtual;
  CSTC  oSpeednTorqueCtrl;
  CSTM  oStateMachine;
  CTSNS oTemperatureSensor;
  CVBS  oBusVoltageSensor;
  CDOUT oBrakeDigitalOutput;
  CDOUT oNTCRelay;
  CMPM  oMPM;
} MCTuningInitStruct_t;
  
/**
* @}
*/

/** @defgroup MCTuning_class_private_methods MCTuning class private methods
  * @{
  */

/**
  * @brief  Creates an object of the class MCTuning
  * @param  pMCTuningParams pointer to an MCTuning parameters structure
  * @retval CMCT new instance of MCTuning object
  */
CMCT MCT_NewObject(pMCTuningParams_t pMCTuningParams);

/**
  * @brief  Example of public method of the class MCTuning
  * @param  this related object of class CMCT
  * @retval none
  */
void MCT_Init(CMCT this, MCTuningInitStruct_t MCTuningInitStruct);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __MCTUNINGCLASSPRIVATE_H */





/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
