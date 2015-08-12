/**
  ******************************************************************************
  * @file    DAC_UserInterfaceClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of DAC class      
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
#ifndef __DAC_USERINTERFACECLASS_H
#define __DAC_USERINTERFACECLASS_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */
  
/** @addtogroup DAC_UserInterface
  * @{
  */

/** @defgroup DAC_class_exported_types DAC class exported types
* @{
*/

/** 
  * @brief  Public DAC class definition
  */
typedef struct CDAC_UI_t *CDAC_UI;

/** 
  * @brief  DAC class parameters definition
  */
typedef const void DACParams_t, *pDACParams_t;
/**
  * @}
  */

/** @defgroup DAC_class_exported_methods DAC class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class DAC
  * @param  pUserInterfaceParams pointer to an UserInterface parameters structure
  * @param  pDACParams pointer to an DAC parameters structure
  * @retval CDAC_UI new instance of DAC object
  */
CDAC_UI DAC_NewObject(pUserInterfaceParams_t pUserInterfaceParams, pDACParams_t pDACParams);
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__DAC_USERINTERFACECLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
