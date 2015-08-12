/**
  ******************************************************************************
  * @file    OpenLoop_FOCDriveClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of OpenLoop class      
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
#ifndef __OPENLOOP_FOCDRIVECLASS_H
#define __OPENLOOP_FOCDRIVECLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup FOCDrive_OpenLoop
  * @{
  */

/** @defgroup OpenLoopFOC_class_exported_types Open Loop FOC class exported types
* @{
*/

/** 
  * @brief  Public Open Loop FOC class definition
  */
typedef struct COL_FOC_t *COL_FOC;

/** 
  * @brief  Open Loop FOC class parameters definition
  */
typedef const struct
{
  int16_t hDefaultVoltage; /*! Default Open loop voltage */
}OL_FOCParams_t, *pOL_FOCParams_t;

/**
  * @}
  */

/** @defgroup OpenLoopFOC_class_exported_methods Open Loop FOC class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class OpenLoop
  * @param  pFOCDriveParams pointer to an FOCDrive parameters structure
  * @param  pOpenLoopParams pointer to an OpenLoop parameters structure
  * @retval CSM_FOC new instance of OpenLoopFOC object
  */
COL_FOC OL_NewObject(pFOCDriveParams_t pFOCDriveParams, pOL_FOCParams_t pOpenLoopParams);


/**
  * @brief  It allows changing applied open loop phase voltage
  * @param  this related object of class COL_FOC
  * @param  pOpenLoopParams pointer to an OpenLoop parameters structure
  * @retval None
  */
void OL_UpdateVoltage(COL_FOC this, int16_t hNewVoltage);


/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__OPENLOOP_FOCDRIVECLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
