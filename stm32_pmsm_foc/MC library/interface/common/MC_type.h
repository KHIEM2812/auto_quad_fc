/**
  ******************************************************************************
  * @file    MC_type.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Standard lib MC class definition
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
#ifndef __MC_TYPE_H
#define __MC_TYPE_H

/* Includes ------------------------------------------------------------------*/
/** @defgroup MCLibraryConf_MISRACompliancy MC Classes MISRA Compliancy Test
* @{
*/

/** 
  * @brief Uncomment #define MISRA_C_2004_BUILD to build the library including 
  *        "stm32f10x_MisraCompliance.h" instead of "stm32f10x.h". 
  *        This will allow to build the library in 'strict ISO/ANSI C' and in 
  *        compliance with MISRA C 2004 rules (check project options)
  */
/* #define MISRA_C_2004_BUILD */

/**
  * @}
  */

#ifdef MISRA_C_2004_BUILD
#include "stm32f10x_MisraCompliance.h"
#else
#include "stm32f10x.h"
#endif

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */

/** @addtogroup MC_Type
  * @{
  */
  
/** @defgroup MCType_undefined_exported_types MCType undefined exported types
* @{
*/

#define MC_NULL    (uint16_t)(0x0000u)
#define MC_NO_ERROR         (uint16_t)(0x0000u)

#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-127)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32767)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483647)

/** 
  * @brief  Error codes for fault generation  
  */
#define MC_NO_FAULTS      (uint16_t)(0x0000u)
#define MC_FOC_DURATION   (uint16_t)(0x0001u)
#define MC_OVER_VOLT      (uint16_t)(0x0002u)
#define MC_UNDER_VOLT     (uint16_t)(0x0004u)
#define MC_OVER_TEMP      (uint16_t)(0x0008u)
#define MC_START_UP       (uint16_t)(0x0010u)
#define MC_SPEED_FDBK     (uint16_t)(0x0020u)
#define MC_BREAK_IN       (uint16_t)(0x0040u)
#define MC_SW_ERROR       (uint16_t)(0x0080u)

typedef struct 
{
  s16 qI_Component1;
  s16 qI_Component2;
} Curr_Components;

typedef struct 
{
  s16 qV_Component1;
  s16 qV_Component2;
} Volt_Components;


typedef struct
{ 
  uint8_t Channel;
  uint8_t SamplTime;
} ADConv_t;

typedef enum
{
REAL_SENSOR, VIRTUAL_SENSOR
} SensorType_t;

/** 
  * @brief  Public DOutputState type definition 
  */
typedef enum
{
 INACTIVE, ACTIVE
} DOutputState_t;

/** 
  * @brief  State_t enum type definition  
  */
typedef enum
{
IDLE,           /*!< Persistent state, following state can be IDLE_START if a 
                      start motor command has been given or IDLE_ALIGNMENT if a 
                      start alignment command has been given */
IDLE_ALIGNMENT, /*!<"Pass-through" state, the code to be executed only once 
                     between IDLE and ALIGNMENT states it’s intended to be here 
                     executed. Following state is normally  ALIGNMENT but it can
                     also be ANY_STOP if a stop motor command has been given */
ALIGNMENT,      /*!< Persistent state, following state can only be ANY_STOP */
IDLE_START,     /*!< "Pass-through" state, the code to be executed only once 
                     between IDLE and START states it’s intended to be here 
                     executed. Following state is normally  START but it can 
                     also be ANY_STOP if a stop motor command has been given */
START,          /*!< Persistent state where the motor start-up is intended to be
                     executed. The following state is normally START_RUN as soon
                     as first validated speed is detected. Another possible 
                     following state is ANY_STOP if a stop motor command has 
                     been executed */
START_RUN,      /*!< "Pass-through" state, the code to be executed only once 
                      between START and RUN states it’s intended to be here 
                      executed. Following state is normally  RUN but it can also
                      be ANY_STOP  if a stop motor command has been given */
RUN,             /*!< Persistent state with running motor. The following state 
                      is normally ANY_STOP when a stop motor command has been 
                      executed */
ANY_STOP,        /*!< "Pass-through" state, the code to be executed only once 
                       between any state and STOP it’s intended to be here 
                       executed. Following state is normally STOP */
STOP,            /*!< Persistent state. Following state is normally STOP_IDLE as
                      soon as conditions for moving state machine are detected */
STOP_IDLE,       /*!< "Pass-through" state, the code to be executed only once 
                      between STOP and IDLE it’s intended to be here executed. 
                      Following state is normally IDLE */
FAULT_NOW,       /*!< Persistent state, the state machine can be moved from any 
                      condition directly to this state by STM_FaultProcessing 
                      method. This method also manage the passage to the only 
                      allowed following state that is FAULT_OVER */
FAULT_OVER       /*!< Persistent state where the application is intended to stay
                      when the fault conditions disappeared. Following state is 
                      normally STOP_IDLE, state machine is moved as soon as the  
                      user has acknowledged the fault condition. */
} State_t;

/**
  * @}
  */

/** @defgroup MCType_SpeednTorqCtrlRelated_exported_types MCType SpeednTorqCtrl related exported types
* @{
*/

/** 
  * @brief  SpeednTorqCtrl modality 
  */
typedef enum
{
	STC_TORQUE_MODE, /*!<  Torque mode*/
	STC_SPEED_MODE   /*!<  Speed mode*/
} STC_Modality_t;

/**
  * @}
  */

/** @defgroup MCType_UserInterfaceRelated_exported_definitions MCType UserInterface related exported definitions
* @{
*/

#define OPT_NONE  0x00 /*!<No UI option selected.*/
#define OPT_LCD   0x01 /*!<Bit field indicating that the UI uses LCD manager.*/
#define OPT_COM   0x02 /*!<Bit field indicating that the UI uses serial communication.*/
#define OPT_DAC   0x04 /*!<Bit field indicating that the UI uses real DAC.*/
#define OPT_DACT  0x08 /*!<Bit field indicating that the UI uses RC Timer DAC.*/
#define OPT_DACS  0x10 /*!<Bit field indicating that the UI uses SPI communication.*/


#define MAIN_SCFG_POS (28)
#define AUX_SCFG_POS (24)

#define MAIN_SCFG_VALUE(x) (((x)>>MAIN_SCFG_POS)&0x0F)
#define AUX_SCFG_VALUE(x)  (((x)>>AUX_SCFG_POS)&0x0F)

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __MC_TYPE_H */
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
