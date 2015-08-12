/**
  ******************************************************************************
  * @file    MCInterfaceClass.c
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of MCInterface class
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

/* Includes ------------------------------------------------------------------*/
#include "FOCDriveClass.h"
#include "SpeednTorqCtrlClass.h"
#include "StateMachineClass.h"

#include "MCInterfaceClass.h"
#include "MCInterfaceClassPrivate.h"
#include "MCInterfacePrivate.h"

#ifdef MC_CLASS_DYNAMIC
  #include "stdlib.h" /* Used for dynamic allocation */
#else
  #include "MC_type.h"
  #define MAX_MCI_NUM 2u

  _CMCI_t MCIpool[MAX_MCI_NUM];
  unsigned char MCI_Allocated = 0u;
#endif
  
#define CLASS_VARS   &((_CMCI)this)->Vars_str

/* This macro converts the exported enum from the state machine to the related 
   bit field.*/
#define BC(state) (1u<<((uint16_t)((uint8_t)(state))))

/* Private function prototypes */
bool MCI_ExecSpeedRampActions(CMCI this, int16_t hParam1, uint16_t hParam2);
bool MCI_ExecTorqueRampActions(CMCI this, int16_t hParam1, uint16_t hParam2);
bool MCI_SetCurrentReferencesActions(CMCI this, int16_t hParam1, uint16_t hParam2);
  
/**
  * @brief  Creates an object of the class MCInterface
  * @param  pMCInterfaceParams pointer to an MCInterface parameters structure
  * @retval CMCI new instance of MCInterface object
  */
CMCI MCI_NewObject(pMCInterfaceParams_t pMCInterfaceParams)
{
  _CMCI _oMCI;
  
  #ifdef MC_CLASS_DYNAMIC
    _oMCI = (_CMCI)calloc(1u,sizeof(_CMCI_t));
  #else
    if (MCI_Allocated  < MAX_MCI_NUM)
    {
      _oMCI = &MCIpool[MCI_Allocated++];
    }
    else
    {
      _oMCI = MC_NULL;
    }
  #endif
  
  _oMCI->pParams_str = (pParams_t)pMCInterfaceParams;
  
  return ((CMCI)_oMCI);
}

/**
  * @brief  Initializes all the object variables, usually it has to be called 
  *         once right after object creation. It is also used to assign the 
  *         state machine object, the speed and torque controller, and the FOC
  *         drive object to be used by MC Interface.
  * @param  this related object of class CMCI.
  * @param  oSTM the state machine object used by the MCI.
  * @param  oSTC the speed and torque controller used by the MCI.
  * @param  oFOC the FOC drive object used by the MCI.
  * @retval none.
  */
void MCI_Init(CMCI this, CSTM oSTM, CSTC oSTC, CFOC oFOC)
{
  pVars_t pVars = CLASS_VARS;

  pVars->oSTM = oSTM;
  pVars->oSTC = oSTC;
  pVars->oFOC = oFOC;

  /* Buffer related initialization */
  pVars->pActions = MC_NULL;
  pVars->hParam1 = 0;
  pVars->hParam2 = 0u;
  pVars->hTrigState = 0u; 
  pVars->CommandState = MCI_BUFFER_EMPTY;
}

/**
  * @brief  This is a buffered command to set a motor speed ramp. This commands
  *         don't become active as soon as it is called but it will be executed
  *         when the oSTM state is START_RUN or RUN. User can check the status
  *         of the command calling the MCI_IsCommandAcknowledged method.
  * @param  this related object of class CMCI.
  * @param  hFinalSpeed is the value of mechanical rotor speed reference at the
  *         end of the ramp expressed in tenths of HZ.
  * @param  hDurationms the duration of the ramp expressed in milliseconds. It 
  *         is possible to set 0 to perform an instantaneous change in the 
  *         value.
  * @retval none.
  */
void MCI_ExecSpeedRamp(CMCI this,  int16_t hFinalSpeed, uint16_t hDurationms)
{
  pVars_t pVars = CLASS_VARS;

  pVars->pActions = &MCI_ExecSpeedRampActions;
  pVars->hParam1 = hFinalSpeed;
  pVars->hParam2 = hDurationms;
  pVars->hTrigState = BC(RUN) | BC(START_RUN);
  pVars->CommandState = MCI_COMMAND_NOT_ALREADY_EXECUTED;
}

/**
  * @brief  This is the implementation of the buffered command 
  *         MCI_ExecSpeedRamp. 
  * @param  this related object of class CMCI.
  * @param  hParam1 is the value of mechanical rotor speed reference at the
  *         end of the ramp expressed in tenths of HZ.
  * @param  hParam2 the duration of the ramp expressed in milliseconds. It 
  *         is possible to set 0 to perform an instantaneous change in the 
  *         value.
  * @retval bool It returns TRUE if the command has been executed succesfully
            othervise it returns FALSE.
  */
bool MCI_ExecSpeedRampActions(CMCI this, int16_t hParam1, uint16_t hParam2)
{
  pVars_t pVars = CLASS_VARS;
  
  FOC_SetDriveInput(pVars->oFOC, INTERNAL);
  STC_SetControlMode(pVars->oSTC, STC_SPEED_MODE);
  return STC_ExecRamp(pVars->oSTC, hParam1, hParam2);
}

/**
  * @brief  This is a buffered command to set a motor torque ramp. This commands
  *         don't become active as soon as it is called but it will be executed
  *         when the oSTM state is START_RUN or RUN. User can check the status
  *         of the command calling the MCI_IsCommandAcknowledged method.
  * @param  this related object of class CMCI.
  * @param  hFinalTorque is the value of motor torque reference at the end of 
  *         the ramp. This value represents actually the Iq current expressed in
  *         digit.
  *         To convert current expressed in Amps to current expressed in digit
  *         is possible to use the formula:
  *         Current (digit) = [Current(Amp) * 65536 * Rshunt * Aop] / Vdd micro.
  * @param  hDurationms the duration of the ramp expressed in milliseconds. It
  *         is possible to set 0 to perform an instantaneous change in the 
  *         value.
  * @retval none.
  */
void MCI_ExecTorqueRamp(CMCI this,  int16_t hFinalTorque, uint16_t hDurationms)
{
  pVars_t pVars = CLASS_VARS;
  
  pVars->pActions = &MCI_ExecTorqueRampActions;
  pVars->hParam1 = hFinalTorque;
  pVars->hParam2 = hDurationms;
  pVars->hTrigState = BC(RUN) | BC(START_RUN);
  pVars->CommandState = MCI_COMMAND_NOT_ALREADY_EXECUTED;
}

/**
  * @brief  This is the implementation of the buffered command 
  *         MCI_ExecTorqueRamp. 
  * @param  this related object of class CMCI.
  * @param  hParam1 is the value of motor torque reference at the end of 
  *         the ramp. This value represents actually the Iq current expressed in
  *         digit.
  *         To convert current expressed in Amps to current expressed in digit
  *         is possible to use the formula:
  *         Current (digit) = [Current(Amp) * 65536 * Rshunt * Aop] / Vdd micro.
  * @param  hParam2 the duration of the ramp expressed in milliseconds. It
  *         is possible to set 0 to perform an instantaneous change in the 
  *         value.
  * @retval bool It returns TRUE if the command has been executed succesfully
            othervise it returns FALSE.
  */
bool MCI_ExecTorqueRampActions(CMCI this, int16_t hParam1, uint16_t hParam2)
{
  pVars_t pVars = CLASS_VARS;
  
  FOC_SetDriveInput(pVars->oFOC, INTERNAL);
  STC_SetControlMode(pVars->oSTC, STC_TORQUE_MODE);
  return STC_ExecRamp(pVars->oSTC, hParam1, hParam2);
}

/**
  * @brief  This is a buffered command to set directly the motor current 
  *         references Iq and Id. This commands don't become active as soon as 
  *         it is called but it will be executed when the oSTM state is 
  *         START_RUN or RUN. User can check the status of the command calling 
  *         the MCI_IsCommandAcknowledged method.
  * @param  this related object of class CMCI.
  * @param  Iqdref current references on qd reference frame in Curr_Components
  *         format.
  * @retval none.
  */
void MCI_SetCurrentReferences(CMCI this, Curr_Components Iqdref)
{
  pVars_t pVars = CLASS_VARS;
  
  pVars->pActions = &MCI_SetCurrentReferencesActions;
  pVars->hParam1 = Iqdref.qI_Component1;
  pVars->hParam2 = (uint16_t)Iqdref.qI_Component2;
  pVars->hTrigState = BC(RUN) | BC(START_RUN);
  pVars->CommandState = MCI_COMMAND_NOT_ALREADY_EXECUTED;
}

/**
  * @brief  This is the implementation of the buffered command 
  *         MCI_SetCurrentReferences. 
  * @param  this related object of class CMCI.
  * @param  hParam1 is the value of Iq reference.
  * @param  hParam2 is the value of Id reference.  
  * @retval bool It returns TRUE if the command has been executed succesfully
            othervise it returns FALSE.
  */
bool MCI_SetCurrentReferencesActions(CMCI this, int16_t hParam1, uint16_t hParam2)
{
  pVars_t pVars = CLASS_VARS;
  Curr_Components Iqdref;
  
  FOC_SetDriveInput(pVars->oFOC, EXTERNAL);
  Iqdref.qI_Component1 = hParam1;
  Iqdref.qI_Component2 = (int16_t)hParam2;
  FOC_SetIqdref(pVars->oFOC, Iqdref);
  return TRUE;
}

/**
  * @brief  This is a user command used to start the motor. If is possible, the
  *         command is executed instantaneously otherwise the command is 
  *         discarded. User must take care of this possibility by checking the 
  *         return value.
  *         It is mandatory to execute one of these commands:\n
  *         - MCI_ExecSpeedRamp,\n
  *         - MCI_ExecTorqueRamp or \n
  *         - MCI_SetCurrentReferences.\n
  *         before calling MCI_StartMotor. Otherwise the behaviour in run state
  *         will be unpredictable.
  * @param  this related object of class CMCI.
  * @retval bool It returns TRUE if the command is successfully executed 
  *         otherwise it return FALSE.
  */
bool MCI_StartMotor(CMCI this)
{
  pVars_t pVars = CLASS_VARS;
  bool RetVal = STM_NextState(((_CMCI)this)->Vars_str.oSTM,IDLE_START);
  
  if (RetVal == TRUE)
  {
    pVars->CommandState = MCI_COMMAND_NOT_ALREADY_EXECUTED;
  }
  
  return RetVal;
}

/**
  * @brief  This is a user command used to stop the motor. If is possible, the 
  *         command is executed instantaneously otherwise the command is 
  *         discarded. User must take care of this possibility by checking the 
  *         return value.
  * @param  this related object of class CMCI.
  * @retval bool It returns TRUE if the command is successfully executed 
  *         otherwise it return FALSE.
  */
bool MCI_StopMotor(CMCI this)
{
  return STM_NextState(((_CMCI)this)->Vars_str.oSTM,ANY_STOP);
}

/**
  * @brief  This is a user command used to indicate that the user has seen the 
  *         error condition. If is possible, the command is executed 
  *         instantaneously otherwise the command is discarded. User must take 
  *         care of this possibility by checking the return value.
  * @param  this related object of class CMCI.
  * @retval bool It returns TRUE if the command is successfully executed 
  *         otherwise it return FALSE.
  */
bool MCI_FaultAcknowledged(CMCI this)
{
  return STM_FaultAcknowledged(((_CMCI)this)->Vars_str.oSTM);
}

/**
  * @brief  This is a user command used to start the encoder alignment 
  *         procedure. If is possible, the command is executed instantaneously 
  *         otherwise the command is discarded. User must take care of this 
  *         possibility by checking the return value.
  * @param  this related object of class CMCI.
  * @retval bool It returns TRUE if the command is successfully executed 
  *         otherwise it return FALSE.
  */
bool MCI_EncoderAlign(CMCI this)
{
  return STM_NextState(((_CMCI)this)->Vars_str.oSTM,IDLE_ALIGNMENT);
}

/**
  * @brief  This is usually a method managed by task. It must be called 
  *         periodically in order to check the status of the related oSTM object
  *         and eventually to execute the buffered command if the condition 
  *         occurs.
  * @param  this related object of class CMCI.
  * @retval none.
  */
void MCI_UpdateCommand(CMCI this)
{
  pVars_t pVars = CLASS_VARS;
  
  if (pVars->CommandState == MCI_COMMAND_NOT_ALREADY_EXECUTED)
  {
    /* Check for trigger condition */
    uint16_t hTmp = 1u;

    if ( (pVars->hTrigState & 
          (uint16_t)(hTmp << (uint16_t)((uint8_t)STM_GetState(pVars->oSTM)))) 
        != 0u)
    {
      if ((*pVars->pActions)(this, pVars->hParam1, pVars->hParam2))
      {
        pVars->CommandState = MCI_COMMAND_EXECUTED_SUCCESFULLY;
      }
      else
      {
        pVars->CommandState = MCI_COMMAND_EXECUTED_UNSUCCESFULLY;
      }
    }
  }
}

/**
  * @brief  It returns information about the state of the last buffered command.
  * @param  this related object of class CMCI.
  * @retval CommandState_t  It can be one of the following codes:
  *         - MCI_BUFFER_EMPTY if no buffered command has been called.
	*         - MCI_COMMAND_NOT_ALREADY_EXECUTED if the buffered command 
  *         condition hasn't already occurred.
  *         - MCI_COMMAND_EXECUTED_SUCCESFULLY if the buffered command has 
  *         been executed successfully. In this case calling this function reset 
  *         the command state to BC_BUFFER_EMPTY.
  *         - MCI_COMMAND_EXECUTED_UNSUCCESFULLY if the buffered command has 
  *         been executed unsuccessfully. In this case calling this function 
  *         reset the command state to BC_BUFFER_EMPTY.
  */
CommandState_t  MCI_IsCommandAcknowledged(CMCI this)
{
  pVars_t pVars = CLASS_VARS;
  CommandState_t retVal = pVars->CommandState;
  
  if ((retVal == MCI_COMMAND_EXECUTED_SUCCESFULLY) | 
      (retVal == MCI_COMMAND_EXECUTED_UNSUCCESFULLY))
  {
    pVars->CommandState = MCI_BUFFER_EMPTY;
  }
  return retVal;
}

/**
  * @brief  It returns information about the state of the related oSTM object.
  * @param  this related object of class CMCI.
  * @retval State_t It returns the current state of the related oSTM object.
  */
State_t  MCI_GetSTMState(CMCI this)
{
  return STM_GetState(((_CMCI)this)->Vars_str.oSTM);
}

/**
  * @brief  It returns information about the current mechanical rotor speed
  *         reference expressed in tenths of HZ.
  * @param  this related object of class CMCI.
  * @retval int16_t current mechanical rotor speed reference expressed in tenths
  *         of HZ.
  */
int16_t MCI_GetMecSpeedRef01Hz(CMCI this)
{
  return FOC_GetMecSpeedRef01Hz(((_CMCI)this)->Vars_str.oFOC);
}

/**
  * @brief  It returns information about last computed average mechanical speed,
  *         expressed in 01Hz (tenth of Hertz).
  * @param  this related object of class CMCI.
  * @retval int16_t rotor average mechanical speed (01Hz).
  */
int16_t MCI_GetAvrgMecSpeed01Hz(CMCI this)
{
  return FOC_GetAvrgMecSpeed01Hz(((_CMCI)this)->Vars_str.oFOC);
}

/**
  * @brief  It returns information about the current motor torque reference.
  *         This value represents actually the Iq current reference expressed 
  *         in digit.
  *         To convert current expressed in digit to current expressed in Amps
  *         is possible to use the formula: 
  *         Current(Amp) = [Current(digit) * Vdd micro] / [65536 * Rshunt * Aop]
  * @param  this related object of class CMCI.
  * @retval int16_t current motor torque reference. This value represents 
  *         actually the Iq ref current expressed in digit.
  */
int16_t MCI_GetTorqueRef(CMCI this)
{
  return FOC_GetTeref(((_CMCI)this)->Vars_str.oFOC);
}

/**
  * @brief  It returns information about current motor measured torque. This
  *         value represents actually the Iq current expressed in digit.
  *         To convert current expressed in digit to current expressed in Amps
  *         is possible to use the formula: 
  *         Current(Amp) = [Current(digit) * Vdd micro] / [65536 * Rshunt * Aop]
  * @param  this related object of class CMCI.
  * @retval int16_t current motor measured torque. This value represents 
  *         actually the Iq ref current expressed in digit.
  */
int16_t MCI_GetTorque(CMCI this)
{
  return FOC_GetIqd(((_CMCI)this)->Vars_str.oFOC).qI_Component1;
}

/**
  * @brief  It returns information about stator current reference in 
  *         Curr_Components format.
  * @param  this related object of class CMCI.
  * @retval Curr_Components Stator current reference.
  */
Curr_Components MCI_GetCurrentsReference(CMCI this)
{
  return FOC_GetIqdref(((_CMCI)this)->Vars_str.oFOC);
}

/**
  * @brief  It returns the motor phase current amplitude (0-to-peak) in s16A
  *         To convert s16A into Ampere following formula must be used: 
  *         Current(Amp) = [Current(s16A) * Vdd micro] / [65536 * Rshunt * Aop]
  * @param  this related object of class CMCI
  * @retval int16_t Motor phase current (0-to-peak) in s16A
  */
int16_t MCI_GetPhaseCurrentAmplitude(CMCI this)
{
  return FOC_GetPhaseCurrentAmplitude(((_CMCI)this)->Vars_str.oFOC);
}

/**
  * @brief  It returns the applied motor phase voltage amplitude (0-to-peak) in 
  *         s16V. To convert s16V into Volts following formula must be used: 
  *         PhaseVoltage(V) = [PhaseVoltage(s16A) * Vbus(V)] /[sqrt(3) *32767]
  * @param  this related object of class CMCI
  * @retval int16_t Motor phase voltage (0-to-peak) in s16V
  */
int16_t MCI_GetPhaseVoltageAmplitude(CMCI this)
{
  return FOC_GetPhaseVoltageAmplitude(((_CMCI)this)->Vars_str.oFOC);
}

/**
  * @brief  It returns the modality of the speed and torque controller. 
  * @param  this related object of class CMCI.
  * @retval STC_Modality_t It returns the modality of STC. It can be one of 
  *         these two values: STC_TORQUE_MODE or STC_SPEED_MODE.
  */
STC_Modality_t MCI_GetControlMode(CMCI this)
{
  return STC_GetControlMode(((_CMCI)this)->Vars_str.oSTC);
}

/**
  * @brief  It returns the motor direction imposed by the last command 
  *         (MCI_ExecSpeedRamp, MCI_ExecTorqueRamp or MCI_SetCurrentReferences).
  * @param  this related object of class CMCI.
  * @retval int16_t It returns 1 or -1 according the sign of hFinalSpeed, 
  *         hFinalTorque or Iqdref.qI_Component1 of the last command.
  */
int16_t MCI_GetImposedMotorDirection(CMCI this)
{
  int16_t retVal = 1;
  pVars_t pVars = CLASS_VARS;
  
  if (pVars->hParam1 < 0)
  {
    retVal = -1;
  }
  
  return retVal;
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
