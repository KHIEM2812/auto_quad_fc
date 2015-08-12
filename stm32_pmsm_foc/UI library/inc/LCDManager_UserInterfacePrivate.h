/**
  ******************************************************************************
  * @file    LCDManager_UserInterfacePrivate.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains private definition of LCDManager class      
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
#ifndef __LCDMANAGER_USERINTERFACEPRIVATE_H
#define __LCDMANAGER_USERINTERFACEPRIVATE_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */
  
/** @addtogroup LCD_Manager_UserInterface
  * @{
  */

/** @defgroup LCDManager_private_types LCDManager private types
* @{
*/

/** 
  * @brief  Redefinition of parameter structure
  */
typedef LCDManagerParams_t DParams_t, *pDParams_t; 

/** 
  * @brief Private LCDManager class definition 
  */
typedef struct
{
	pDParams_t pDParams_str;	/*!< Derived class parameters container */
}_DCLCD_UI_t, *_DCLCD_UI;
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__LCDMANAGER_USERINTERFACEPRIVATE_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
