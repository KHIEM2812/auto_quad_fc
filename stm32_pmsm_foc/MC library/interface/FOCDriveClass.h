/**
  ******************************************************************************
  * @file    FOCDriveClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of FOCDrive class      
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
#ifndef __FOCDRIVECLASS_H
#define __FOCDRIVECLASS_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"
#include "SpeednPosFdbkClass.h"
#include "PIRegulatorClass.h"
#include "SpeednPosFdbkClass.h"
#include "SpeednTorqCtrlClass.h"
#include "PWMnCurrFdbkClass.h"
#include "BusVoltageSensorClass.h"
/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */

/** @addtogroup FOCDrive
  * @{
  */
  
/** @defgroup FOCDrive_class_exported_types FOCDrive class exported types
* @{
*/

/** 
  * @brief  Public FOCDrive class definition 
  */
typedef struct CFOC_t *CFOC;

/** 
  * @brief  Current references source type, internal or external to FOCDriveClass 
  */
typedef enum
{
  INTERNAL, EXTERNAL
} CurrRefSource_t ;

/** 
  * @brief  FOC Drive internal objects initialization structure type;
  */
typedef struct
{
  CPWMC oCurrSensor;
  CSTC  oSpdTrqController;
  CVBS  oVbusSensor;
  CSPD  oSpeedSensor;
  CPI   oPI_q;
  CPI   oPI_d;
} FOCInitStruct_t;

/** 
  * @brief  FOCDrive class parameters definition  
  */
typedef const struct
{
  uint16_t hMaxModule;                 /*!< Circle limitation maximum allowed 
                                          module */
  uint16_t hCircle_limit_table[87];   /*!< Circle limitation table */
  uint8_t bStart_index;               /*!< Circle limitation table indexing 
                                           start */
  uint8_t bInstanceNumber;            /*!< FOC object instance number, only used
                                           for multiple motor control */
}FOCDriveParams_t, *pFOCDriveParams_t;
  
/**
* @}
*/

/** @defgroup FOCDrive_class_exported_methods FOCDrive class exported methods
  * @{
  */
/**
  * @brief Initializes all the object variables, usually it has to be called 
  *        once right after object creation.
  * @param this related object of class CFOC
  * @param FOCInitStruct Initialization structure containing the objects 
  *        necessary for FOCDrive class working
  * @param pDInitStruct pointer to derived class initialization structure
  * @retval none
  */
void FOC_Init(CFOC this, FOCInitStruct_t FOCInitStruct, void *pDInitStruct);

/**
  * @brief  It re-initializes the object current and voltage variables. Moreover
  *         it clears qd currents PI controllers, voltage sensor and SpeednTorque 
  *         controller, and performs the current reading network offset 
  *         calibration after having switched off the PWM. It must be called 
  *         before each motor restart. It does not clear speed sensor. 
  * @param  this related object of class CFOC
  * @retval none
  */
void FOC_Clear(CFOC this);

/**
  * @brief It sets in real time the speed sensor utilized by the FOC drive for 
  *        both reference frame transformation and - only in case of speed 
  *        control - speed regulation. This method must be called for instance 
  *        when moving from START to RUN states in case of sensor-less 
  * @param this related object of class CFOC
  * @param oSpeedSensor Speed sensor object 
  * @retval none
  */
void FOC_SetSpeedSensor(CFOC this, CSPD oSpeedSensor);

/**
  * @brief  It sets whether the Iqdref (current references on qd reference 
  *         frame) utilized by FOC algorithm must be computed internally or 
  *         provided from the outside through FOC_SetCurrRef method
  * @param  this related object of class CFOC.
  * @param  bCurrRefSource Source for Iqdref, it must be equal to EXTERNAL or 
  *         INTERNAL
  * @retval none
  */
void FOC_SetDriveInput(CFOC this, CurrRefSource_t CurrRefSource);

/**
  * @brief  It allows to provide from the outside the Iqdref (current references 
  *         on qd reference frame) utilized by FOC algorithm. If bCurrRefSource 
  *         is set to INTERNAL, the methos call is discarded 
  * @param  this related object of class CFOC
  * @param  Iqdref current references on qd reference frame in Curr_Components format
  * @retval none
  */
void FOC_SetIqdref(CFOC this,Curr_Components Iqdref);

/**
  * @brief  It computes the new values of Iqdref (current references on qd 
  *         reference frame) based on the required electrical torque information
  *         provided by oTSC object (internally clocked). 
  *         If implemented in the derived class it executes flux weakening and/or
  *         MTPA algorithm(s). It must be called with the periodicity specified  
  *         in oTSC parameters
  * @param  this related object of class CFOC 
  * @retval none
  */
void FOC_CalcCurrRef(CFOC this);

/**
  * @brief It executes the core of FOC drive that is the controllers for Iqd 
  *        currents regulation. Reference frame transformations are carried out 
  *        accordingly to the active speed sensor. It must be called periodically
  *        when new motor currents have been converted
  * @param this related object of class CFOC.
  * @retval uint16_t It returns MC_NO_FAULTS if the FOC has been ended before 
  *         next PWM Update event, MC_FOC_DURATION otherwise
  */
uint16_t FOC_CurrController(CFOC this);

/**
  * @brief  It returns FOC object instance number, to be used only for multiple 
  *         motor control
  * @param  this related object of class CFOC
  * @retval uint8_t Instance number 
  */
uint8_t FOC_GetInstanceNumber(CFOC this);

/**
  * @brief  It returns speed sensor reliability with reference to the sensor 
  *         actually used for reference frame transformation
  * @param  this related object of class CFOC
  * @retval bool It returns TRUE if the speed sensor utilized for reference 
  *         frame transformation and (in speed control mode) for speed 
  *         regulation is reliable, FALSE otherwise
  */
bool FOC_GetSpdSensorReliability(CFOC this);

/**
  * @brief  It returns the last computed average mechanical speed, expressed in
  *         01Hz (tenth of Hertz) and related to the sensor actually used by FOC 
  *         algorithm
  * @param  this related object of class CSPD
  * @retval int16_t rotor average mechanical speed (01Hz)
  */
int16_t FOC_GetAvrgMecSpeed01Hz(CFOC this);

/**
  * @brief  Get the current mechanical rotor speed reference expressed in tenths
  *         of HZ. 
  * @param  this related object of class CFOC
  * @retval int16_t current mechanical rotor speed reference expressed in tenths
  *         of HZ. 
  */
int16_t FOC_GetMecSpeedRef01Hz(CFOC this);

/**
  * @brief  It returns stator current Iab in Curr_Components format
  * @param  this related object of class CFOC
  * @retval Curr_Components Stator current Iab
  */
Curr_Components FOC_GetIab(CFOC this);

/**
  * @brief  It returns stator current Ialphabeta in Curr_Components format
  * @param  this related object of class CFOC
  * @retval Curr_Components Stator current Ialphabeta
  */
Curr_Components FOC_GetIalphabeta(CFOC this);

/**
  * @brief  It returns stator current Iqd in Curr_Components format
  * @param  this related object of class CFOC
  * @retval Curr_Components Stator current Iqd
  */
Curr_Components FOC_GetIqd(CFOC this);

/**
  * @brief  It returns stator current Iqdref in Curr_Components format
  * @param  this related object of class CFOC
  * @retval Curr_Components Stator current Iqdref
  */
Curr_Components FOC_GetIqdref(CFOC this);

/**
  * @brief  It returns stator current Vqd in Volt_Components format
  * @param  this related object of class CFOC
  * @retval Curr_Components Stator current Vqd
  */
Volt_Components FOC_GetVqd(CFOC this);

/**
  * @brief  It returns stator current Valphabeta in Volt_Components format
  * @param  this related object of class CFOC
  * @retval Curr_Components Stator current Valphabeta
  */
Volt_Components FOC_GetValphabeta(CFOC this);

/**
  * @brief  It returns the rotor electrical angle actually used for reference  
  *         frame transformation
  * @param  this related object of class CFOC
  * @retval int16_t Rotor electrical angle in dpp format
  */
int16_t FOC_GetElAngledpp(CFOC this);

/**
  * @brief  It returns the reference eletrical torque, fed to derived class for
  *         Iqref and Idref computation
  * @param  this related object of class CFOC
  * @retval int16_t Teref 
  */
int16_t FOC_GetTeref(CFOC this);


/**
  * @brief  It returns the motor phase current amplitude (0-to-peak) in s16A
  *         To convert s16A into Ampere following formula must be used: 
  *         Current(Amp) = [Current(s16A) * Vdd micro] / [65536 * Rshunt * Aop]
  * @param  this related object of class CFOC
  * @retval int16_t Motor phase current (0-to-peak) in s16A
  */
int16_t FOC_GetPhaseCurrentAmplitude(CFOC this);

/**
  * @brief  It returns the applied motor phase voltage amplitude (0-to-peak) in 
  *         s16V. 
  * @param  this related object of class CFOC
  * @retval int16_t Motor phase voltage (0-to-peak) in s16V. To convert s16V 
  *         into Volts following formula must be used: 
  *         PhaseVoltage(V) = [PhaseVoltage(s16A) * Vbus(V)] /[sqrt(3) *32767]
  *         N.B. A more precise estimation is obtained subtracting from Vbus the
  *              voltage drop on switches
  */
int16_t FOC_GetPhaseVoltageAmplitude(CFOC this);


/**
  * @brief  When bDriveInput is set to INTERNAL, Idref should is normally managed
  *         by FOC_CalcCurrRef. Neverthless, this method allows forcing changing 
  *         Idref value. Method call has no effect when either flux weakening 
  *         region is entered or MTPA is enabled
  * @param  this related object of class CFOC
  * @param  int16_t New target Id value
  * @retval none
  */
void FOC_SetIdref(CFOC this, int16_t hNewIdref);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __FOCDRIVECLASS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
