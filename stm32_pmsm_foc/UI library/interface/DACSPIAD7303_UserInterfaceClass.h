/**
  ******************************************************************************
  * @file    DACSPIAD7303_UserInterfaceClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of DACSPIAD7303 class      
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
#ifndef __DACSPIAD7303_USERINTERFACECLASS_H
#define __DACSPIAD7303_USERINTERFACECLASS_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */
  
/** @addtogroup DAC_SPI_AD7303_UserInterface
  * @{
  */

/** @defgroup DACSPIAD7303_class_exported_types DACSPIAD7303 class exported types
* @{
*/

/** 
  * @brief  Public DACSPIAD7303 class definition
  */
typedef struct CDACX_UI_t *CDACX_UI;

/** 
  * @brief  DACSPIAD7303 class parameters definition
  */
typedef const void DACSPIAD7303Params_t, *pDACSPIAD7303Params_t;
/**
  * @}
  */

/** @defgroup DACSPIAD7303_class_exported_methods DACSPIAD7303 class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class DACSPIAD7303
  * @param  pUserInterfaceParams pointer to an UserInterface parameters structure
  * @param  pDACSPIAD7303Params pointer to an DACSPIAD7303 parameters structure
  * @retval CDACX_UI new instance of DACSPIAD7303 object
  */
CDACX_UI DACX_NewObject(pUserInterfaceParams_t pUserInterfaceParams, pDACSPIAD7303Params_t pDACSPIAD7303Params);

/**
  * @brief  Example of public method of the class DACSPIAD7303
  * @param  this related object of class CDACX_UI
  * @retval none
  */
void DACX_Func(CDACX_UI this);
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__DACSPIAD7303_USERINTERFACECLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
