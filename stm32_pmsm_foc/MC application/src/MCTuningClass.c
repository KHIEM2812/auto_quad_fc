/**
  ******************************************************************************
  * @file    MCTuningClass.c
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of MCTuning class
  ******************************************************************************
  * @<br>
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

/* Includes ------------------------------------------------------------------*/
#include "MCTuningClass.h"
#include "MCTuningClassPrivate.h"
#include "MCTuningPrivate.h"

#ifdef MC_CLASS_DYNAMIC
  #include "stdlib.h" /* Used for dynamic allocation */
#else
  #include "MC_type.h"
  #define MAX_MCT_NUM 2u

  _CMCT_t MCTpool[MAX_MCT_NUM];
  unsigned char MCT_Allocated = 0u;
#endif

/**
  * @brief  Creates an object of the class MCTuning
  * @param  pMCTuningParams pointer to an MCTuning parameters structure
  * @retval CMCT new instance of MCTuning object
  */
CMCT MCT_NewObject(pMCTuningParams_t pMCTuningParams)
{
  _CMCT _oMCT;
  
  #ifdef MC_CLASS_DYNAMIC
    _oMCT = (_CMCT)calloc(1u,sizeof(_CMCT_t));
  #else
    if (MCT_Allocated  < MAX_MCT_NUM)
    {
      _oMCT = &MCTpool[MCT_Allocated++];
    }
    else
    {
      _oMCT = MC_NULL;
    }
  #endif
  
  _oMCT->pParams_str = (pParams_t)pMCTuningParams;
  
  return ((CMCT)_oMCT);
}

/**
  * @brief  Example of public method of the class MCTuning
  * @param  this related object of class CMCT
  * @retval none
  */
void MCT_Init(CMCT this, MCTuningInitStruct_t MCTuningInitStruct)
{
  ((_CMCT)this)->Vars_str.MCTuningInitStruct = MCTuningInitStruct;
}

/**
  * @brief  It returns the FOCDrive object
  * @param  this related object of class CMCT
  * @retval none
  */
CFOC MCT_GetFOCDrive(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oFOCDrive);
}

/**
  * @brief  It returns the speed control loop PI(D) object
  * @param  this related object of class CMCT
  * @retval none
  */
CPI MCT_GetSpeedLoopPID(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oPIDSpeed);
}

/**
  * @brief  It returns the Iq current control loop PI(D) object
  * @param  this related object of class CMCT
  * @retval none
  */
CPI MCT_GetIqLoopPID(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oPIDIq);
}

/**
  * @brief  It returns the Id current control loop PI(D) object
  * @param  this related object of class CMCT
  * @retval none
  */
CPI MCT_GetIdLoopPID(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oPIDId);
}

/**
  * @brief  It returns the Flux Weakening control loop PI(D) object
  * @param  this related object of class CMCT
  * @retval none
  */
CPI MCT_GetFluxWeakeningLoopPID(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oPIDFluxWeakening);
}

/**
  * @brief  It returns the PWMnCurrFdbk object
  * @param  this related object of class CMCT
  * @retval CPWMC, instance of PWMnCurrFdbkClass
  */
CPWMC MCT_GetPWMnCurrFdbk(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oPWMnCurrFdbk);
}

/**
  * @brief  It returns the RevupCtrl object
  * @param  this related object of class CMCT
  * @retval CRUC, instance of RevupCtrlClass
  */
CRUC MCT_GetRevupCtrl(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oRevupCtrl);
}

/**
  * @brief  It returns the Main Speed'n Position sensor object.
  * Main position sensor is considered the one used to execute FOC
  * @param  this related object of class CMCT
  * @retval CSPD, instance of SpeednPosFdbkClass
  */
CSPD MCT_GetSpeednPosSensorMain(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oSpeedSensorMain);
}

/**
  * @brief  It returns the Auxiliary Speed'n Position sensor object.
  *         Auxiliary position sensor is considered the one used to backup/tune
  *         the main one
  * @param  this related object of class CMCT
  * @retval CSPD, instance of SpeednPosFdbkClass; MC_NULL if no auxiliary sensor
  *         is active
  */
CSPD MCT_GetSpeednPosSensorAuxiliary(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oSpeedSensorAux);
}

/**
  * @brief  It returns the Virtual Speed'n Position sensor object.
  *         Virtual position sensor is considered the one used to rev-up the
  *         motor during the start-up procedure required by the state-observer
  *         sensorless algorithm
  * @param  this related object of class CMCT
  * @retval CSPD, instance of SpeednPosFdbkClass; MC_NULL if no auxiliary sensor
  *         is active
  */
CSPD MCT_GetSpeednPosSensorVirtual(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oSpeedSensorVirtual);
}

/**
  * @brief  It returns the Speed'n Torque Controller object.
  * @param  this related object of class CMCT
  * @retval CSTC, instance of SpeednTorqCtrlClass
  */
CSTC MCT_GetSpeednTorqueController(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oSpeednTorqueCtrl);
}

/**
  * @brief  It returns the State Machine object.
  * @param  this related object of class CMCT
  * @retval CSTM, instance of StateMachineClass
  */
CSTM MCT_GetStateMachine(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oStateMachine);
}

/**
  * @brief  It returns the Temperature sensor object.
  * @param  this related object of class CMCT
  * @retval CTSNS, instance of TemperatureSensorClass
  */
CTSNS MCT_GetTemperatureSensor(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oTemperatureSensor);
}

/**
  * @brief  It returns the Bus Voltage sensor object
  * @param  this related object of class CMCT
  * @retval CVBS, instance of BusVoltageSensorClass
  */
CVBS MCT_GetBusVoltageSensor(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oBusVoltageSensor);
}

/**
  * @brief  It returns the Brake resistor object
  * @param  this related object of class CMCT
  * @retval CDOUT, instance of DigitalOutput Class; MC_NULL if no Brake resistor
  *         is active
  */
CDOUT MCT_GetBrakeResistor(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oBrakeDigitalOutput);
}

/**
  * @brief  It returns the NTC Relay object
  * @param  this related object of class CMCT
  * @retval CDOUT, instance of DigitalOutput Class; MC_NULL if no Relay
  *         is active
  */
CDOUT MCT_GetNTCRelay(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oNTCRelay);
}

/**
  * @brief  It returns the MotorPowerMeasurement object
  * @param  this related object of class CMCT
  * @retval CMPM, instance of MotorPowerMeasurement Class; MC_NULL if no MPM
  *         is active
  */
CMPM MCT_GetMotorPowerMeasurement(CMCT this)
{
  return (((_CMCT)this)->Vars_str.MCTuningInitStruct.oMPM);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
