/**
  ******************************************************************************
  * @file    UserInterfaceClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of UserInterface class      
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
#ifndef __USERINTERFACECLASS_H
#define __USERINTERFACECLASS_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"
#include "MCInterfaceClass.h"
#include "MCTuningClass.h"

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */

/** @addtogroup UserInterface
  * @{
  */
  
/** @defgroup UserInterface_class_exported_types UserInterface class exported types
* @{
*/

/* Exported defines-----------------------------------------------------------*/

/** @defgroup UserInterface_class_exported_SensorCode UserInterface sensor code
* @{
*/
/* @brief To configure the UI use MAIN Sensor (4bit)|AUX Sensor (4 bit) as first byte of CFG.*/
#define UI_SCODE_NONE     0x0u 
#define UI_SCODE_HALL     0x1u /*!< This code identifies the Hall sensor.*/
#define UI_SCODE_ENC      0x2u /*!< This code identifies the Encoder sensor.*/
#define UI_SCODE_STO_PLL  0x9u /*!< This code identifies the State observer + PLL sensor.*/
#define UI_SCODE_STO_CR   0xAu /*!< This code identifies the State observer + CORDIC sensor.*/
/**
* @}
*/

/** @defgroup UserInterface_class_exported_ConfigOption UserInterface configuration option
* @{
*/
/* @brief */
#define UI_CFGOPT_NONE            0x00000000u /*!< Enable this option when no other 
                                              option is selected.*/
#define UI_CFGOPT_FW              0x00000001u /*!< Enable this option when the flux 
                                              weakening is enabled in the MC 
                                              firmware.*/
#define UI_CFGOPT_SPEED_KD        0x00000002u /*!< Enable this option when the speed
                                              controller has derivative action.
                                              */
#define UI_CFGOPT_Iq_KD           0x00000004u /*!< Enable this option when the Iq
                                              controller has derivative action.
                                              */
#define UI_CFGOPT_Id_KD           0x00000008u /*!< Enable this option when the Id
                                              controller has derivative action.
                                              */
#define UI_CFGOPT_DAC             0x00000010u /*!< Enable this option if a DAC object
                                              will be associated with the UI.*/
#define UI_CFGOPT_SETIDINSPDMODE  0x00000020u /*!< Enable this option to allow setting
                                              the Id reference when MC is in
                                              speed mode.*/
#define UI_CFGOPT_PLLTUNING       0x00000040u /*!< Enable this option to allow setting
                                              the PLL KP and KI.*/
/**
* @}
*/

#define MC_PROTOCOL_CODE_SET_REG        0x01
#define MC_PROTOCOL_CODE_GET_REG        0x02
#define MC_PROTOCOL_CODE_EXECUTE_CMD    0x03
#define MC_PROTOCOL_CODE_STORE_TOADDR   0x04
#define MC_PROTOCOL_CODE_LOAD_FROMADDR  0x05
#define MC_PROTOCOL_CODE_GET_BOARD_INFO 0x06
#define MC_PROTOCOL_CODE_SET_RAMP       0x07
#define MC_PROTOCOL_CODE_GET_REVUP_DATA 0x08
#define MC_PROTOCOL_CODE_SET_REVUP_DATA 0x09
#define MC_PROTOCOL_CODE_SET_CURRENT_REF 0x0A

typedef enum {
  MC_PROTOCOL_REG_TARGET_MOTOR,
  MC_PROTOCOL_REG_FLAGS,
  MC_PROTOCOL_REG_STATUS,
  MC_PROTOCOL_REG_CONTROL_MODE,
  MC_PROTOCOL_REG_SPEED_REF,
  MC_PROTOCOL_REG_SPEED_KP,
  MC_PROTOCOL_REG_SPEED_KI,
  MC_PROTOCOL_REG_SPEED_KD,
  MC_PROTOCOL_REG_TORQUE_REF,
  MC_PROTOCOL_REG_TORQUE_KP,
  MC_PROTOCOL_REG_TORQUE_KI,
  MC_PROTOCOL_REG_TORQUE_KD,
  MC_PROTOCOL_REG_FLUX_REF,
  MC_PROTOCOL_REG_FLUX_KP,
  MC_PROTOCOL_REG_FLUX_KI,
  MC_PROTOCOL_REG_FLUX_KD,
  MC_PROTOCOL_REG_OBSERVER_C1,
  MC_PROTOCOL_REG_OBSERVER_C2,
  MC_PROTOCOL_REG_OBSERVER_CR_C1,
  MC_PROTOCOL_REG_OBSERVER_CR_C2,
  MC_PROTOCOL_REG_PLL_KI,
  MC_PROTOCOL_REG_PLL_KP,
  MC_PROTOCOL_REG_FLUXWK_KP,
  MC_PROTOCOL_REG_FLUXWK_KI,
  MC_PROTOCOL_REG_FLUXWK_BUS,
  MC_PROTOCOL_REG_BUS_VOLTAGE,
  MC_PROTOCOL_REG_HEATS_TEMP,
  MC_PROTOCOL_REG_MOTOR_POWER,
  MC_PROTOCOL_REG_DAC_OUT1,
  MC_PROTOCOL_REG_DAC_OUT2,
  MC_PROTOCOL_REG_SPEED_MEAS,
  MC_PROTOCOL_REG_TORQUE_MEAS,
  MC_PROTOCOL_REG_FLUX_MEAS,
  MC_PROTOCOL_REG_FLUXWK_BUS_MEAS,
  MC_PROTOCOL_REG_RUC_STAGE_NBR,
  MC_PROTOCOL_REG_I_A,
  MC_PROTOCOL_REG_I_B,
  MC_PROTOCOL_REG_I_ALPHA,
  MC_PROTOCOL_REG_I_BETA,
  MC_PROTOCOL_REG_I_Q,
  MC_PROTOCOL_REG_I_D,
  MC_PROTOCOL_REG_I_Q_REF,
  MC_PROTOCOL_REG_I_D_REF,
  MC_PROTOCOL_REG_V_Q,
  MC_PROTOCOL_REG_V_D,
  MC_PROTOCOL_REG_V_ALPHA,
  MC_PROTOCOL_REG_V_BETA,
  MC_PROTOCOL_REG_MEAS_EL_ANGLE,
  MC_PROTOCOL_REG_MEAS_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_EL_ANGLE,
  MC_PROTOCOL_REG_OBS_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_I_ALPHA,
  MC_PROTOCOL_REG_OBS_I_BETA,
  MC_PROTOCOL_REG_OBS_BEMF_ALPHA,
  MC_PROTOCOL_REG_OBS_BEMF_BETA,
  MC_PROTOCOL_REG_OBS_CR_EL_ANGLE,
  MC_PROTOCOL_REG_OBS_CR_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_CR_I_ALPHA,
  MC_PROTOCOL_REG_OBS_CR_I_BETA,
  MC_PROTOCOL_REG_OBS_CR_BEMF_ALPHA,
  MC_PROTOCOL_REG_OBS_CR_BEMF_BETA,
  MC_PROTOCOL_REG_DAC_USER1,
  MC_PROTOCOL_REG_DAC_USER2,
  MC_PROTOCOL_REG_MAX_APP_SPEED,
  MC_PROTOCOL_REG_MIN_APP_SPEED,
  MC_PROTOCOL_REG_IQ_SPEEDMODE,
  MC_PROTOCOL_REG_EST_BEMF_LEVEL,
  MC_PROTOCOL_REG_OBS_BEMF_LEVEL,
  MC_PROTOCOL_REG_EST_CR_BEMF_LEVEL,
  MC_PROTOCOL_REG_OBS_CR_BEMF_LEVEL,
  MC_PROTOCOL_REG_UNDEFINED
} MC_Protocol_REG_t;

#define MC_PROTOCOL_CMD_START_MOTOR   0x01
#define MC_PROTOCOL_CMD_STOP_MOTOR    0x02
#define MC_PROTOCOL_CMD_STOP_RAMP     0x03
#define MC_PROTOCOL_CMD_RESET         0x04
#define MC_PROTOCOL_CMD_PING          0x05
#define MC_PROTOCOL_CMD_START_STOP    0x06
#define MC_PROTOCOL_CMD_FAULT_ACK     0x07
#define MC_PROTOCOL_CMD_ENCODER_ALIGN 0x08

#define GUI_ERROR_CODE 0xFFFFFFFF

typedef enum {
	DAC_CH0,
	DAC_CH1,
	DAC_CH2,
	DAC_CH3,
	DAC_MAX_Channel_nbr
} DAC_Channel_t;

/** 
  * @brief  Public UserInterface class definition 
  */
typedef struct CUI_t *CUI;

/** 
  * @brief  UserInterface class parameters definition  
  */
typedef const void UserInterfaceParams_t, *pUserInterfaceParams_t;
  
/**
* @}
*/

/** @defgroup UserInterface_class_exported_methods UserInterface class exported methods
  * @{
  */

/**
  * @brief  Creates an object of the class UserInterface
  * @param  pUserInterfaceParams pointer to an UserInterface parameters structure
  * @retval CUI new instance of UserInterface object
  */
CUI UI_NewObject(pUserInterfaceParams_t pUserInterfaceParams);

/**
  * @brief  Initialization of UI object. It perform the link between the UI
  *         object and the MC interface and MC tuning objects. It must be called
  *         before the derived class initialization.
  * @param  this related object of class CUI.
  * @param  bMCNum  Is the total number of MC object presnet in the list.
  * @param  pMCI is the pointer of the list of MC interface objects to be linked
  *         with the UI.
  * @param  pMCT is the pointer of the list of MC tuning objects to be linked
  *         with the UI.
  * @param  pUICfg is the pointer of the user interface configuration list. Each 
  *         element of the list must be a bit field containing one (or more) of 
  *         the exported configuration option UI_CFGOPT_xxx (eventually OR-ed).
  * @retval none.
  */
void UI_Init(CUI this, uint8_t bMCNum, CMCI* pMCI, CMCT* pMCT, uint32_t* pUICfg);

/**
  * @brief  It is used to select the MC on which UI operates.
  * @param  this related object of class CUI.
  * @param  bSelectMC The new selected MC, zero based, on which UI operates.
  * @retval bool It return true if the bSelectMC is valid oterwise return false.
  */
bool UI_SelectMC(CUI this,uint8_t bSelectMC);

/**
  * @brief  It is used to retrive the MC on which UI currently operates.
  * @param  this related object of class CUI.
  * @retval uint8_t It returns the currently selected MC, zero based, on which
  *         UI operates.
  */
uint8_t UI_GetSelectedMC(CUI this);

/**
  * @brief  It is used to retrive the configuration of the MC on which UI 
  *         currently operates.
  * @param  this related object of class CUI.
  * @retval uint32_t It returns the currently configuration of selected MC on 
  *         which UI operates.
  *         It represents a bit field containing one (or more) of 
  *         the exported configuration option UI_CFGOPT_xxx (eventually OR-ed).
  */
uint32_t UI_GetSelectedMCConfig(CUI this);

/**
  * @brief  It is used to execute a SetReg command coming from the user.
  * @param  this related object of class CUI.
  * @param  bRegID Code of register to be updated. Valid code is one of the 
  *         MC_PROTOCOL_REG_xxx values exported by UserInterfaceClass.
  * @param  wValue is the new value to be set.
  * @retval bool It returns true if the SetReg command has been performed 
  *         succesfully otherwise returns false.
  */
bool UI_SetReg(CUI this, MC_Protocol_REG_t bRegID, int32_t wValue);

/**
  * @brief  It is used to execute a GetReg command coming from the user.
  * @param  this related object of class CUI.
  * @param  bRegID Code of register to be updated. Valid code is one of the 
  *         MC_PROTOCOL_REG_xxx values exported by UserInterfaceClass.
  * @retval int32_t is the current value of register bRegID.
  */
int32_t UI_GetReg(CUI this, MC_Protocol_REG_t bRegID);

/**
  * @brief  It is used to retrieve the current selected MC tuning object.
  * @param  this related object of class CUI.
  * @retval CMCT It returns the currently selected MC tuning object on which
  *         UI operates.
  */
CMCT UI_GetCurrentMCT(CUI this);

/**
  * @brief  It is used to execute a command coming from the user.
  * @param  this related object of class CUI.
  * @param  bCmdID Code of register to be updated. Valid code is one of the 
  *         MC_PROTOCOL_CMD_xxx define exported by UserInterfaceClass.
  * @retval bool It returns true if the command has been performed 
  *         succesfully otherwise returns false.
  */
bool UI_ExecCmd(CUI this, uint8_t bCmdID);

/**
  * @brief  It is used to execute a speed ramp command coming from the user.
  * @param  this related object of class CUI.
  * @param  wFinalMecSpeedRPM final speed value expressed in RPM.
  * @param  hDurationms the duration of the ramp expressed in milliseconds. It
  *         is possible to set 0 to perform an instantaneous change in the value.
  * @retval bool It returns true if the command has been performed 
  *         succesfully otherwise returns false.
  */
bool UI_ExecSpeedRamp(CUI this, int32_t wFinalMecSpeedRPM, uint16_t hDurationms);

/**
  * @brief  It is used to execute a torque ramp command coming from the user.
  * @param  this related object of class CUI.
  * @param  hTargetFinal final torque value. See MCI interface for more
            details.
  * @param  hDurationms the duration of the ramp expressed in milliseconds. It
  *         is possible to set 0 to perform an instantaneous change in the value.
  * @retval bool It returns true if the command has been performed 
  *         succesfully otherwise returns false.
  */
bool UI_ExecTorqueRamp(CUI this, int16_t hTargetFinal, uint16_t hDurationms);

/**
  * @brief  It is used to execute a get Revup data command coming from the user.
  * @param  this related object of class CUI.
  * @param  bStage is the rev up phase, zero based, to be read.
  * @param  pDurationms is the pointer to an uint16_t variable used to retrieve 
  *         the duration of the Revup stage.
  * @param  pFinalMecSpeed01Hz is the pointer to an int16_t variable used to 
  *         retrieve the mechanical speed at the end of that stage expressed in
  *         0.1Hz.
  * @param  pFinalTorque is the pointer to an int16_t variable used to 
  *         retrieve the value of motor torque at the end of that
  *         stage. This value represents actually the Iq current expressed in
  *         digit.
  * @retval bool It returns true if the command has been performed 
  *         succesfully otherwise returns false.
  */
bool UI_GetRevupData(CUI this, uint8_t bStage, uint16_t* pDurationms, 
                     int16_t* pFinalMecSpeed01Hz, int16_t* pFinalTorque );

/**
  * @brief  It is used to execute a set Revup data command coming from the user.
  * @param  this related object of class CUI.
  * @param  bStage is the rev up phase, zero based, to be modified.
  * @param  hDurationms is the new duration of the Revup stage.
  * @param  hFinalMecSpeed01Hz is the new mechanical speed at the end of that 
  *         stage expressed in 0.1Hz.
  * @param  hFinalTorque is the new value of motor torque at the end of that
  *         stage. This value represents actually the Iq current expressed in
  *         digit.
  * @retval bool It returns true if the command has been performed 
  *         succesfully otherwise returns false.
  */
bool UI_SetRevupData(CUI this, uint8_t bStage, uint16_t hDurationms, 
                     int16_t hFinalMecSpeed01Hz, int16_t hFinalTorque );

/**
  * @brief  It is used to execute a set current reference command coming from 
  *         the user.
  * @param  this related object of class CUI.
  * @param  hIqRef is the current Iq reference on qd reference frame. This value
  *         is expressed in digit. To convert current expressed in digit to 
  *         current expressed in Amps is possible to use the formula: 
  *         Current(Amp) = [Current(digit) * Vdd micro] / [65536 * Rshunt * Aop]
  * @param  hIdRef is the current Id reference on qd reference frame. This value
  *         is expressed in digit. See hIqRef param description.
  * @retval none.
  */
void UI_SetCurrentReferences(CUI this, int16_t hIqRef, int16_t hIdRef); 

/**
  * @brief  Hardware and software initialization of the DAC object. This is a 
  *         virtual function and is implemented by related object.
  * @param  this related object of class UI. It must be a DACx_UI object casted
  *         to CUI otherwise the DACInit method will have no effect.
  * @retval none.
  */
void UI_DACInit(CUI this);

/**
  * @brief  This method is used to update the DAC outputs. The selected 
  *         variables will be provided in the related output channels. This is a
  *         virtual function and is implemented by related object.
  * @param  this related object of class UI. It must be a DACx_UI object casted
  *         to CUI otherwise the DACInit method will have no effect.
  * @retval none.
  */
void UI_DACExec(CUI this);

/**
  * @brief  This method is used to set up the DAC outputs. The selected
  *         variables will be provided in the related output channels after next
  *         DACExec. This is a virtual function and is implemented by related 
  *         object.
  * @param  this related object of class UI. It must be a DACx_UI object casted
  *         to CUI otherwise the DACInit method will have no effect.
  * @param  bChannel the DAC channel to be programmed. It must be one of the 
  *         exported channels Ex. DAC_CH0.
  * @param  bVariable the variables to be provided in out through the selected
  *         channel. It must be one of the exported UI register Ex. 
  *         MC_PROTOCOL_REG_I_A.
  * @retval none.
  */
void UI_DACChannelConfig(CUI this, DAC_Channel_t bChannel, 
                         MC_Protocol_REG_t bVariable);

/**
  * @brief  This method is used to set the value of the "User DAC channel".
  * @param  this related object of class UI. It must be a DACx_UI object casted
  *         to CUI otherwise the DACInit method will have no effect.
  * @param  bUserChNumber the "User DAC channel" to be programmed.
  * @param  hValue the value to be put in output.
  * @retval none.
  */
void UI_DACSetUserChannelValue(CUI this, uint8_t bUserChNumber, int16_t hValue);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __USERINTERFACECLASS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
