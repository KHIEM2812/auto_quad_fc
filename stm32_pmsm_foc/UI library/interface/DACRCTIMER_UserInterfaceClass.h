/**
  ******************************************************************************
  * @file    DACRCTIMER_UserInterfaceClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of DACRCTIMER class      
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
#ifndef __DACRCTIMER_USERINTERFACECLASS_H
#define __DACRCTIMER_USERINTERFACECLASS_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */
  
/** @addtogroup DAC_RC_TIMER_UserInterface
  * @{
  */

/** @defgroup DACRCTIMER_class_exported_types DACRCTIMER class exported types
* @{
*/

/** 
  * @brief  Public DACRCTIMER class definition
  */
typedef struct CDACT_UI_t *CDACT_UI;

/** 
  * @brief  DACRCTIMER class parameters definition
  */
typedef const void DACRCTIMERParams_t, *pDACRCTIMERParams_t;
/**
  * @}
  */

/** @defgroup DACRCTIMER_class_exported_methods DACRCTIMER class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class DACRCTIMER
  * @param  pUserInterfaceParams pointer to an UserInterface parameters structure
  * @param  pDACRCTIMERParams pointer to an DACRCTIMER parameters structure
  * @retval CDACT_UI new instance of DACRCTIMER object
  */
CDACT_UI DACT_NewObject(pUserInterfaceParams_t pUserInterfaceParams, pDACRCTIMERParams_t pDACRCTIMERParams);

/**
  * @brief  Example of public method of the class DACRCTIMER
  * @param  this related object of class CDACT_UI
  * @retval none
  */
void DACT_Func(CDACT_UI this);
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__DACRCTIMER_USERINTERFACECLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
