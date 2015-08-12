/**
  ******************************************************************************
  * @file    DigitalOutputClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of DigitalOutput class      
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
#ifndef __DIGITALOUTPUTCLASS_H
#define __DIGITALOUTPUTCLASS_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */

/** @addtogroup DigitalOutput
  * @{
  */
  
/** @defgroup DigitalOutput_class_exported_constants DigitalOutput class exported constants
* @{
*/
#define DOutputActiveHigh       1u
#define DOutputActiveLow        0u

/**
* @}
*/

/** @defgroup DigitalOutput_class_exported_types DigitalOutput class exported types
* @{
*/

/** 
  * @brief  Public DigitalOutput class definition 
  */
typedef struct CDOUT_t *CDOUT;

/** 
  * @brief  DigitalOutput class parameters definition  
  */
typedef const struct
{
  GPIO_TypeDef* hDOutputPort;       /*!< GPIO output port. It must be equal
										 to GPIOx x= A, B, ...*/
  uint16_t hDOutputPin;             /*!< GPIO output pin. It must be equal to
                                     	GPIO_Pin_x x= 0, 1, ...*/  
  uint8_t  bDOutputPolarity;        /*!< GPIO output polarity. It must be equal 
                                     	to DOutputActiveHigh or DOutputActiveLow */ 
}DigitalOutputParams_t, *pDigitalOutputParams_t;
  
/**
* @}
*/

/** @defgroup DigitalOutput_class_exported_methods DigitalOutput class exported methods
  * @{
  */

/**
  * @brief  Creates an object of the class DigitalOutput. 
  * @param  pDigitalOutputParams pointer to an DigitalOutput parameters structure
  * @retval CDOUT new instance of DigitalOutput object
  */
CDOUT DOUT_NewObject(pDigitalOutputParams_t pDigitalOutputParams);

/**
  * @brief  Initializes object variables, port and pin. It must be called only 
  *         after PWMnCurrFdbk object initialization and DigitalOutput object 
  *         creation. 
  * @param this related object of class CDOUT.
  * @retval none.
  */
void DOUT_Init(CDOUT this);

/**
  * @brief Accordingly with selected polarity, it sets to active or inactive the
  *        digital output
  * @param this related object of class CDOUT.
  * @param OutputState_t New requested state
  * @retval none
  */
void DOUT_SetOutputState(CDOUT this, DOutputState_t State);

/**
  * @brief It returns the state of the digital output
  * @param this object of class DOUT
  * @retval OutputState_t Digital output state (ACTIVE or INACTIVE)
  */
DOutputState_t DOUT_GetOutputState(CDOUT this); 

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __DIGITALOUTPUTCLASS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
