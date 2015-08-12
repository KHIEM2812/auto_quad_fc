/**
  ******************************************************************************
  * @file    DACSPI_UserInterfaceClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of DACSPI class      
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
#ifndef __DACSPI_USERINTERFACECLASS_H
#define __DACSPI_USERINTERFACECLASS_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */
  
/** @addtogroup DAC_SPI_UserInterface
  * @{
  */

/** @defgroup DACSPI_class_exported_types DACSPI class exported types
* @{
*/

/** 
  * @brief  Public DACSPI class definition
  */
typedef struct CDACS_UI_t *CDACS_UI;

/** 
  * @brief  DACSPI class parameters definition
  */
typedef const void DACSPIParams_t, *pDACSPIParams_t;
/**
  * @}
  */

/** @defgroup DACSPI_class_exported_methods DACSPI class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class DACSPI
  * @param  pUserInterfaceParams pointer to an UserInterface parameters structure
  * @param  pDACSPIParams pointer to an DACSPI parameters structure
  * @retval CDACS_UI new instance of DACSPI object
  */
CDACS_UI DACS_NewObject(pUserInterfaceParams_t pUserInterfaceParams, pDACSPIParams_t pDACSPIParams);

/**
  * @brief  Example of public method of the class DACSPI
  * @param  this related object of class CDACS_UI
  * @retval none
  */
void DACS_Func(CDACS_UI this);
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__DACSPI_USERINTERFACECLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
