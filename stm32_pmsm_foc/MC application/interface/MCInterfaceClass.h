/**
  ******************************************************************************
  * @file    MCInterfaceClass.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCINTERFACECLASS_H
#define __MCINTERFACECLASS_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"

/** @addtogroup STM32F10x_PMSM_MC_Interface
  * @{
  */

/** @addtogroup MCInterface
  * @{
  */
  
/** @defgroup MCInterface_class_exported_types MCInterface class exported types
* @{
*/

typedef enum {
	MCI_BUFFER_EMPTY,                  /*!< If no buffered command has been 
                                             called.*/
	MCI_COMMAND_NOT_ALREADY_EXECUTED,  /*!< If the buffered command condition 
                                             hasn't already occurred.*/
	MCI_COMMAND_EXECUTED_SUCCESFULLY,  /*!< If the buffered command has been 
                                             executed successfully.*/
	MCI_COMMAND_EXECUTED_UNSUCCESFULLY /*!< If the buffered command has been 
                                             executed unsuccessfully.*/
} CommandState_t ;

/** 
  * @brief  Public MCInterface class definition 
  */
typedef struct CMCI_t *CMCI;

/** 
  * @brief  MCInterface class parameters definition  
  */
typedef const void MCInterfaceParams_t, *pMCInterfaceParams_t;
  
/**
* @}
*/

/** @defgroup MCInterface_class_exported_methods MCInterface class exported methods
  * @{
  */

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
void MCI_ExecSpeedRamp(CMCI this,  int16_t hFinalSpeed, uint16_t hDurationms);

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
void MCI_ExecTorqueRamp(CMCI this,  int16_t hFinalTorque, uint16_t hDurationms);

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
void MCI_SetCurrentReferences(CMCI this, Curr_Components Iqdref);

/**
  * @brief  This is a user command used to start the motor. If is possible, the
  *         command is executed instantaneously otherwise the command is 
  *         discarded. User must take care of this possibility by checking the 
  *         return value.
  *         It is mandatory to execute one of these commands:\n
  *         	- MCI_ExecSpeedRamp
  *         	- MCI_ExecTorqueRamp 
  *         	- MCI_SetCurrentReferences\n	
  *         before calling MCI_StartMotor. Otherwise the behaviour in run state
  *         will be unpredictable.
  * @param  this related object of class CMCI.
  * @retval bool It returns TRUE if the command is successfully executed 
  *         otherwise it return FALSE.
  */
bool MCI_StartMotor(CMCI this);

/**
  * @brief  This is a user command used to stop the motor. If is possible, the 
  *         command is executed instantaneously otherwise the command is 
  *         discarded. User must take care of this possibility by checking the 
  *         return value.
  * @param  this related object of class CMCI.
  * @retval bool It returns TRUE if the command is successfully executed 
  *         otherwise it return FALSE.
  */
bool MCI_StopMotor(CMCI this);

/**
  * @brief  This is a user command used to indicate that the user has seen the 
  *         error condition. If is possible, the command is executed 
  *         instantaneously otherwise the command is discarded. User must take 
  *         care of this possibility by checking the return value.
  * @param  this related object of class CMCI.
  * @retval bool It returns TRUE if the command is successfully executed 
  *         otherwise it return FALSE.
  */
bool MCI_FaultAcknowledged(CMCI this);

/**
  * @brief  This is a user command used to start the encoder alignment 
  *         procedure. If is possible, the command is executed instantaneously 
  *         otherwise the command is discarded. User must take care of this 
  *         possibility by checking the return value.
  * @param  this related object of class CMCI.
  * @retval bool It returns TRUE if the command is successfully executed 
  *         otherwise it return FALSE.
  */
bool MCI_EncoderAlign(CMCI this);

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
CommandState_t  MCI_IsCommandAcknowledged(CMCI this);

/**
  * @brief  It returns information about the state of the related oSTM object.
  * @param  this related object of class CMCI.
  * @retval State_t It returns the current state of the related oSTM object.
  */
State_t  MCI_GetSTMState(CMCI this);

/**
  * @brief  It returns information about the current mechanical rotor speed
  *         reference expressed in tenths of HZ.
  * @param  this related object of class CMCI.
  * @retval int16_t current mechanical rotor speed reference expressed in tenths
  *         of HZ.
  */
int16_t MCI_GetMecSpeedRef01Hz(CMCI this);

/**
  * @brief  It returns information about last computed average mechanical speed,
  *         expressed in 01Hz (tenth of Hertz).
  * @param  this related object of class CMCI.
  * @retval int16_t rotor average mechanical speed (01Hz).
  */
int16_t MCI_GetAvrgMecSpeed01Hz(CMCI this);

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
int16_t MCI_GetTorqueRef(CMCI this);

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
int16_t MCI_GetTorque(CMCI this);

/**
  * @brief  It returns information about stator current reference in 
  *         Curr_Components format.
  * @param  this related object of class CMCI.
  * @retval Curr_Components Stator current reference.
  */
Curr_Components MCI_GetCurrentsReference(CMCI this);

/**
  * @brief  It returns the motor phase current amplitude (0-to-peak) in s16A
  *         To convert s16A into Ampere following formula must be used: 
  *         Current(Amp) = [Current(s16A) * Vdd micro] / [65536 * Rshunt * Aop]
  * @param  this related object of class CMCI
  * @retval int16_t Motor phase current (0-to-peak) in s16A
  */
int16_t MCI_GetPhaseCurrentAmplitude(CMCI this);

/**
  * @brief  It returns the applied motor phase voltage amplitude (0-to-peak) in 
  *         s16V. To convert s16V into Volts following formula must be used: 
  *         PhaseVoltage(V) = [PhaseVoltage(s16A) * Vbus(V)] /[sqrt(3) *32767]
  * @param  this related object of class CMCI
  * @retval int16_t Motor phase voltage (0-to-peak) in s16V
  */
int16_t MCI_GetPhaseVoltageAmplitude(CMCI this);

/**
  * @brief  It returns the modality of the speed and torque controller. 
  * @param  this related object of class CMCI.
  * @retval STC_Modality_t It returns the modality of STC. It can be one of 
  *         these two values: STC_TORQUE_MODE or STC_SPEED_MODE.
  */
STC_Modality_t MCI_GetControlMode(CMCI this);

/**
  * @brief  It returns the motor direction imposed by the last command 
  *         (MCI_ExecSpeedRamp, MCI_ExecTorqueRamp or MCI_SetCurrentReferences).
  * @param  this related object of class CMCI.
  * @retval int16_t It returns 1 or -1 according the sign of hFinalSpeed, 
  *         hFinalTorque or Iqdref.qI_Component1 of the last command.
  */
int16_t MCI_GetImposedMotorDirection(CMCI this);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __MCINTERFACECLASS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
